CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -D _POSIX_C_SOURCE=200809L -D _GNU_SOURCE_ -D _GNU_SOURCE

SOURCES = s21_grep.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = s21_grep


all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@