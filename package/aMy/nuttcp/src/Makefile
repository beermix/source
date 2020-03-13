CC ?= gcc
CFLAGS += -s -O3
LIBS = 
SRC_FILES = nuttcp-8.1.4.c

all: nuttcp

nuttcp: $(SRC_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)
