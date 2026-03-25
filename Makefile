CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -g -Iinclude
TARGET  = minizip
SRCS    = main.c src/io.c src/rle.c
OBJS    = $(SRCS:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)
