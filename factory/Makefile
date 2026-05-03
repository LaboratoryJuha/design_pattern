# Makefile for simple factory example
CC = gcc
CFLAGS = -I. -Wall -Wextra -Werror -g
SRCS = circle.c ractangle.c libfactory.c main.c
OBJS = $(SRCS:.c=.o)
TARGET = main

.PHONY: all clean run

all: run

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
