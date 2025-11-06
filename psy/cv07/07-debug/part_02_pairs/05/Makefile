CC = clang
CFLAGS = -std=c11 -g -O0 -Wall -Wextra
ASAN_FLAGS = -fsanitize=address -fno-omit-frame-pointer
VALGRIND_FLAGS = --leak-check=full --track-origins=yes
TARGET = main

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) $< -o $@

run: $(TARGET)
	./$(TARGET)

asan: main.c
	$(CC) $(CFLAGS) $(ASAN_FLAGS) $< -o $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind $(VALGRIND_FLAGS) ./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all asan valgrind clean
