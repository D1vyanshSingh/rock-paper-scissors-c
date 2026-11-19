CC = gcc
CFLAGS = -Wall

all: librps.so rps

librps.so: rps.c rps.h
	$(CC) $(CFLAGS) -fPIC -shared rps.c -o librps.so

rps: main.c rps.h librps.so
	$(CC) $(CFLAGS) main.c -L. -lrps -Wl,-rpath,'$$ORIGIN' -o rps

clean:
	rm -f librps.so rps
