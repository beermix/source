CC ?= gcc
SRC_FILES = *.c

all: musl-iconv

musl-iconv: $(SRC_FILES)
	$(CC) $(TARGET_CFLAGS) -o $@ $^ $(TARGET_LDFLAGS)

clean:
	rm -f musl-iconv *.o
