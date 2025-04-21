CC = gcc
CFLAGS = -Wall -std=c99

TARGET = airline-routes
SOURCES = main.c route-records.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = route-records.h

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)