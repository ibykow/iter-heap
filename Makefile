INC_FLAGS = -I./
CFLAGS = -Weverything $(INC_FLAGS)
CC ?= cc
PROG_NAME = test

all:
	$(CC) *.c $(CFLAGS) -O3 -o $(PROG_NAME)

clean:
	rm -f ./$(PROG_NAME)

debug:
	$(CC) *.c $(CFLAGS) -O0 -g -o $(PROG_NAME)
