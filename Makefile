CC = gcc
CFLAGS = -g -Wall
EXEC = a4

$(EXEC): 
	$(CC) $(CFLAGS) -o $(EXEC) a4.c process.c frameentry.c frametable.c fifo.c
clean:
	-rm $(EXEC)
	-rm *.exe
test:
	$(CC) $(CFLAGS) -o test test.c process.c frameentry.c frametable.c fifo.c
cleantest:
	-rm test
	-rm *.exe
