CC = clang
CFLAGS = -O3 -Wall -Wextra -Wpedantic
CFLAGS += -lcurl

SRC = $(wildcard src/*.c src/**/*.c)
BIN = caoc

all:
	$(CC) $(CFLAGS) -o $(BIN) $(SRC)

clean:
	rm -f $(BIN)
