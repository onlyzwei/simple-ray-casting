CC = gcc
CFLAGS = -Iinclude -Isrc/libs -Wall -Wextra
LDFLAGS = -Lsrc/libs/lib -lmingw32 -lSDL2main -lSDL2
TARGET = build/main.exe

SRC = src/main.c src/draw.c src/rays.c src/circle.c
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))

all: build $(TARGET)

build:
	if not exist build mkdir build

$(TARGET): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	if exist build rmdir /s /q build

run: $(TARGET)
	$(TARGET)

.PHONY: all clean run build
