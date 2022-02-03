# Makefile for Pi
# Vikman Fernandez-Castro
# February 9, 2018

CC      = gcc
CFLAGS  = -pipe -O2 -Wall -Wextra -pthread
LIBS    = -lm -lmpfr
TARGET  = pi
RM_FILE = rm -rf

SOURCES	= $(wildcard *.c)
OBJECTS	= $(SOURCES:.c=.o)
HEADERS = $(wildcard *.h)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJECTS): $(HEADERS)

clean:
	$(RM_FILE) $(TARGET) $(OBJECTS)
