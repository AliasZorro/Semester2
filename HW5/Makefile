CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LIBS = -lm
TARGET = convex_hull
OBJ = main.o sorts.o convexhull.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LIBS)


%.o: %.c point.h
	$(CC) $(CFLAGS) -c $<


clean:
	rm -f $(OBJ) $(TARGET)