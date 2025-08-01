CC = gcc
CFLAGS = -Wall -Iinclude
LDFLAGS = -lreadline

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
TARGET = hikio

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: test

test: all
	./test/test.sh
