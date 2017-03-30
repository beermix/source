/*
 * Copyright (C) 2017 Rafał Miłecki <rafal@milecki.pl>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mount.h>
#include <unistd.h>

#if 0
#include <dirent.h>
static int ls(const char *path)
{
	DIR *dir;
	struct dirent *dp;

	dir = opendir(path);
	if (!dir)
		return errno;

	printf("Listing %s\n", path);
	while ((dp = readdir(dir))) {
		struct stat fileStat;

		if (stat(dp->d_name, &fileStat)) {
			fprintf(stderr, "Failed to stat %s\n", dp->d_name);
			continue;
		}
		printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
		printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
		printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
		printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
		printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
		printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
		printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
		printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
		printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
		printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
		printf("\t%s\n", dp->d_name);
	}

	closedir(dir);

	return 0;
}

static int cat(const char *path)
{
	FILE *fp;
	char line[64];

	fp = fopen(path, "r");
	if (!fp)
		return -EIO;

	printf("Content of %s:\n", path);
	while (fgets(line, sizeof(line), fp)) {
		printf("%s", line);
	}
	printf("\n");

	fclose(fp);

	return 0;
}
#endif

static int mount_basics()
{
	if (mount("proc", "/proc", "proc", MS_NOATIME | MS_NODEV | MS_NOEXEC | MS_NOSUID, 0))
		return errno;

	if (mount("sysfs", "/sys", "sysfs", MS_NOATIME | MS_NODEV | MS_NOEXEC | MS_NOSUID, 0))
		return errno;

	if (mount("devtmpfs", "/dev", "devtmpfs", MS_NOATIME | MS_NOSUID, "mode=0755,size=512K"))
		return errno;

	return 0;
}

static int find_block_mtd(char *name, char *mtdblock, size_t size)
{
	FILE *fp;
	char line[64];
	int index = -ENOENT;

	fp = fopen("/proc/mtd", "r");
	if (!fp)
		return -EIO;

	while (fgets(line, sizeof(line), fp)) {
		char dev[8];
		int i;

		if (sscanf(line, "mtd%d: %*x %*x \"%7[^\"]", &i, dev) == 2) {
			if (!strcmp(dev, name)) {
				index = i;
				if (mtdblock)
					snprintf(mtdblock, size, "/dev/mtdblock%d", index);
				break;
			}
		}
	}

	fclose(fp);

	return index;
}

static int mount_rootfs()
{
	char mtdblock[32];
	int index;

	index = find_block_mtd("rootfs", mtdblock, sizeof(mtdblock));
	if (index < 0) {
		fprintf(stderr, "Failed to find rootfs: %d\n", index);
		return index;
	}

	if (mount(mtdblock, "/mnt", "squashfs", MS_RDONLY, 0))
		return errno;

	return 0;
}

static int switch_root()
{
	if (mount("/proc", "/mnt/proc", NULL, MS_NOATIME | MS_MOVE, NULL))
		return errno;

	if (mount("/sys", "/mnt/sys", NULL, MS_NOATIME | MS_MOVE, NULL))
		return errno;

	if (mount("/dev", "/mnt/dev", NULL, MS_NOATIME | MS_MOVE, NULL))
		return errno;

	if (chdir("/mnt"))
		return errno;

	if (mount(".", "/", NULL, MS_MOVE, NULL))
		return errno;

	if (chroot("."))
		return errno;

	if (chdir("/"))
		return errno;

	return 0;
}

int main(int argc, char **argv)
{
	int err;

	err = mount_basics();
	if (err) {
		fprintf(stderr, "Failed to mount basic points: %d\n", err);
		return err;
	}

	err = mount_rootfs();
	if (err) {
		fprintf(stderr, "Failed to mount rootfs: %d\n", err);
		return err;
	}

	err = switch_root();
	if (err) {
		fprintf(stderr, "Failed to switch to the new root: %d\n", err);
		return err;
	}

	printf("Successfully switched to the mounted rootfs\n");

	execl("/sbin/init", "/sbin/init", (char *)NULL);

	return 0;
}
