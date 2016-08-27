CC=gcc
CFLAGS=-Werror -Wall -g -Og --std=c99

all: shell.c
	$(CC) -o my_shell shell.c
	
	
