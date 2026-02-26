CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBS = -lssl -lcrypto

all:
	$(CC) $(CFLAGS) main.c crypto.c -o veracli $(LIBS)

clean:
	rm -f veracli
