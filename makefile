CC = gcc
CFLAGS = -Werror -Wall -ansi -pedantic -g
OBJ = main.o conversion.o
EXEC = main

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c conversion.h
	$(CC) $(CFLAGS) -c main.c

conversion.o : conversion.c conversion.h
	$(CC) $(CFLAGS) -c conversion.c

clean: 
	rm -f $(OBJ) $(EXEC)
