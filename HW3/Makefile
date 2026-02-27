CC = gcc
CFLAGS = -Wall -Wextra -O2 -g -Iinclude
TARGET1 = demo_dequeue
TARGET2 = demo_rando
SRC1 = demo_dequeue/demo_dequeue.c src/dequeue.c 
SRC2 = demo_rando/demo_rando_queue.c src/rando_queue.c


dequeue: 
	$(CC) $(CFLAGS) -o $(TARGET1) $(SRC1)

rando: 
	$(CC) $(CFLAGS) -o $(TARGET2) $(SRC2)

all: dequeue rando

deq_clean:
	del $(TARGET1).exe 

rando_clean:
	del $(TARGET2).exe 

clean: deq_clean rando_clean

