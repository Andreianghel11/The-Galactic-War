CC=gcc
CFLAGS=-Wall -Wextra -std=c99
DEBUG=-g

build: main CircularDoublyLinkedList PlanetFunctions ShieldFunctions
	$(CC) $(CFLAGS) $(DEBUG) main.o CircularDoublyLinkedList.o PlanetFunctions.o ShieldFunctions.o -o main

CircularDoublyLinkedList: CircularDoublyLinkedList.h CircularDoublyLinkedList.c
	$(CC) $(CFLAGS) $(DEBUG) CircularDoublyLinkedList.c -c -o CircularDoublyLinkedList.o

PlanetFunctions: PlanetFunctions.h PlanetFunctions.c
	$(CC) $(CFLAGS) $(DEBUG) PlanetFunctions.c -c -o PlanetFunctions.o

ShieldFunctions: ShieldFunctions.h ShieldFunctions.c
	$(CC) $(CFLAGS) $(DEBUG) ShieldFunctions.c -c -o ShieldFunctions.o

main: main.c
	$(CC) $(CFLAGS) $(DEBUG) main.c -c -o main.o

clean:
	rm *.o
	rm main