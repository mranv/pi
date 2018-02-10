# Makefile for Pi
# Vikman Fernandez-Castro
# February 9, 2018

CC      = gcc
CFLAGS  = -pipe -O2
LIBS    = -lm
TARGET  = pi
RM_FILE = rm -rf

.PHONY: all clean

all: $(TARGET)

$(TARGET): pi.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	$(RM_FILE) $(TARGET)
