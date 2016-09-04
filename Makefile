CC=g++
CFLAGS=-Werror -Wall -g -Og --std=c99

all: shell.c token.c check.c
	$(CC) -o my_shell shell.c token.c check.c
	
	
