CC = gcc
CFLAGS = -Werror -Wall -ansi -pedantic -g -Wl,--stack,10485760
OBJ = main.o conversion.o file.o permutation.o encrypt.o ffunc.o
EXEC = main

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c conversion.h header.h file.h
	$(CC) $(CFLAGS) -c main.c

conversion.o : conversion.c conversion.h header.h
	$(CC) $(CFLAGS) -c conversion.c

file.o : file.c header.h conversion.h file.h permutation.h encrypt.h
	$(CC) $(CFLAGS) -c file.c

permutation.o : permutation.c permutation.h file.h header.h encrypt.h
	$(CC) $(CFLAGS) -c permutation.c

encrypt.o : encrypt.c header.h encrypt.h file.h permutation.h ffunc.h conversion.h
	$(CC) $(CFLAGS) -c encrypt.c

ffunc.o : ffunc.c ffunc.h file.h encrypt.h conversion.h header.h
	$(CC) $(CFLAGS) -c ffunc.c

clean: 
	rm -f $(OBJ) $(EXEC)
