CC=gcc
CFLAGS=-Wfatal-errors -std=gnu11 -Wall -g

vigenere.elf: vigenere.h vigenere.c
	$(CC) $(CFLAGS) -o $@ $^
