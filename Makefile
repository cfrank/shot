TARGET = shot
LIBS =
CC = gcc
CFLAGS = -g -O2 -Wall -Werror -fno-inline -Wold-style-definition -Wdeclaration-after-statement
SRC = src/
OUTPUT = bin/

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard $(SRC)*.c))
HEADERS = $(wildcard $(SRC)*.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) $(LIBS) -o $(OUTPUT)$@

clean:
	@echo "Cleaning up"
	-rm -f $(SRC)*.o
	-rm -f $(OUTPUT)$(TARGET)