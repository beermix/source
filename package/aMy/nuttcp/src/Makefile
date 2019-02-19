all: nuttcp

nuttcp:
	$(CC) $(TARGET_CFLAGS) $(TARGET_LDFLAGS) -Wall nuttcp-6.1.2.c -o $@ $^

clean:
	rm -f nuttcp
