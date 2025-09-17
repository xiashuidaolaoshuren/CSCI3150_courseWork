# Makefile to build lab1 from main.c, foo/foo.c and bar/bar.c

CC := gcc
CFLAGS := -Wall -Wextra -g -I.
LDFLAGS :=

TARGET := lab1
OBJS := main.o foo/foo.o bar/bar.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

# Generic rule: build object files from C sources (works for files in subdirs)
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJS)