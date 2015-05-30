
CC=gcc
CFLAGS=-Wall 

make_font: make_font.c
	$(CC) $(CFLAGS) make_font.c -o make_font
