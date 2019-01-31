CC = gcc
CFLAGS  = -g -Wall
TARGET = C2html
all: C2html
C2html: C2html.c
	$(CC) $(CFLAGS) -o C2html C2html.c
test: C2html
	./C2html < input.txt > output.txt
clean:
	$(RM) C2html
