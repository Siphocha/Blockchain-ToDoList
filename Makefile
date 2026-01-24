CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = todo_blockchain
SRCS = main.c blockchain.c auth.c sha256.c todo.c storage.c utils.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) blockchain.dat users.dat

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run