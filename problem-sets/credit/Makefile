CC = gcc
CFLAGS = -Wall -Wextra
CS50_DIR = ..
FILE_NAME = credit

$(FILE_NAME): $(FILE_NAME).c ../cs50.c ../cs50.h
	$(CC) $(CFLAGS) -I.. $(FILE_NAME).c ../cs50.c -o $(FILE_NAME)

clean:
	rm -f $(FILE_NAME)

.PHONY: clean