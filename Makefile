
CC=gcc
CFLAGS=-Wall 

make_font: make_font.c
	$(CC) $(CFLAGS) make_font.c -o make_font

font: make_font font_16x16.txt
	./make_font font_16x16.txt font_data.c

