CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

TARGET = bin/shellforge
SRC = src/main.c src/parser.c

all: $(TARGET)

$(TARGET): $(SRC)
	 gcc $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	 rm -f $(TARGET)

run: $(TARGET)
	 ./$(TARGET)
