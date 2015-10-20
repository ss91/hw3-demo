CC := arm-none-linux-gnueabi-gcc
LD := arm-none-linux-gnueabi-gcc
CFLAGS := -g -Wall -Werror -static
LDFLAGS := -static

OBJECTS := test.o wait.o signal.o destroy.o create.o

all: test wait signal destroy create

: $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f test test.o
	rm -f wait wait.o
	rm -f signal signal.o
	rm -f destroy destroy.o
	rm -f create create.o
.PHONY: clean
