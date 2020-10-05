CC ?= gcc
SRC_FILES = *.c

all: musl-getent

musl-getent: $(SRC_FILES)
	$(CC) $(TARGET_CFLAGS) -o $@ $^ $(TARGET_LDFLAGS)

clean:
	rm -f musl-getent *.o
