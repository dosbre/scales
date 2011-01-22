CC	= gcc
CFLAGS	= -Wall -pedantic -std=c89

scales: scales.o
	$(CC) $^ -o $@

scales.o: scales.c scales.h
	$(CC) $(CFLAGS) -c $<

clean:
	@echo cleaning
	@rm -f scales *.o

.PHONY: clean

