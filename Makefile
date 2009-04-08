CC = gcc
CFLAGS = -g -Wall
EXEC = a4

$(EXEC): 
	$(CC) $(CFLAGS) -o $(EXEC) a4.c heap.c process.c
clean:
	-rm $(EXEC)
	-rm *.exe
test:
	$(CC) $(CFLAGS) -o test test.c heap.c
cleantest:
	-rm test
	-rm *.exe
