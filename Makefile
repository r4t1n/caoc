CC = clang
CFLAGS = -lcurl
SRC = src/main.c
TARGET = caoc

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)