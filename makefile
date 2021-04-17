
CC=clang
CFLAGS=-g
OBJS=main.o stack.o

brainfuck: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf *.o
	rm -rf brainfuck
