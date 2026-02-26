CC = gcc
CFLAGS = -Wall -Wextra -O2 -g -Iinclude
TARGET = demo
SRC = demo/demo_usage.c src/dequeue.c src/rando_queue.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	del $(TARGET).exe 