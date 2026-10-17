CC = gcc
CFLAGS = -Wall -Wextra
CS50_DIR = ..
FILE_NAME = readability

$(FILE_NAME): $(FILE_NAME).c ../cs50.c ../cs50.h
	gcc -Wall -Wextra -I.. $(FILE_NAME).c ../cs50.c -o $(FILE_NAME)

clean:
	rm -f $(FILE_NAME)

.PHONY: clean