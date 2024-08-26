CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -D _POSIX_C_SOURCE=200809L -D _GNU_SOURCE_ -D _GNU_SOURCE

SOURCES = s21_cat.c 
OBJECTS = $(SOURCES:.c=.o)
TARGETS = s21_cat 

all: $(TARGETS)

s21_cat: s21_cat.o
	$(CC) $(CFLAGS) $^ -o $@
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
