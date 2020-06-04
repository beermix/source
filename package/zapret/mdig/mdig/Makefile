CC ?= gcc
CFLAGS += -march=bonnell -std=c99 -s -O3
LIBS = -lpthread
SRC_FILES = *.c

all: mdig

mdig: $(SRC_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

clean:
	rm -f mdig *.o
