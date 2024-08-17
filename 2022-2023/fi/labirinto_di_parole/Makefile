CC = gcc
CFLAGS =
CFLAGS += -Wall -Wextra -Wpedantic
CFLAGS += -ansi

DBGFLAGS =
DBGFLAGS += -g -O0
DBGFLAGS += -fsanitize=address,undefined
DBGFLAGS += -DDEBUG

RLSFLAGS =
RLSFLAGS += -O3
RLSFLAGS += -static
RLSFLAGS += -march=native

SRC = $(wildcard *.c)
HDR = $(wildcard *.h)
OBJ = $(SRC:.c=.o)

default : debug

release: $(SRC) $(HDR)
	$(CC) $(CFLAGS) $(RLSFLAGS) -o $@.out $(SRC)

debug: $(OBJ) $(HDR)
	$(CC) $(CFLAGS) $(DBGFLAGS) -o $@.out $(OBJ)
	./debug.out

clean:
	rm -f debug release *.o

%.o: %.c
	$(CC) $(CFLAGS) $(DBGFLAGS) -c -o $@ $<
