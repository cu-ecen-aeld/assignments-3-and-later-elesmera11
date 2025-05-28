CC=$(CROSS_COMPILE)gcc
all: writer

writer: writer.o
	$(CC) -o writer writer.o -lm

writer.o: writer.c
	$(CC) -c writer.c

clean:	
	rm -f writer.o writer
