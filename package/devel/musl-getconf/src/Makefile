CC ?= gcc
SRC_FILES = *.c

all: musl-getconf

musl-getconf: $(SRC_FILES)
	$(CC) $(TARGET_CFLAGS) -o $@ $^ $(TARGET_LDFLAGS)

clean:
	rm -f musl-getconf *.o
