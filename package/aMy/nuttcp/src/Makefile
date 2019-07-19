all: nuttcp

nuttcp:
	$(CC) $(TARGET_CFLAGS) $(TARGET_LDFLAGS) -Wall nuttcp-8.1.4.c -o $@ $^

clean:
	rm -f nuttcp
