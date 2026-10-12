CC = gcc
CFLAGS = -Wall -Wextra
CS50_DIR = ..
FILE_NAME = plurality

$(FILE_NAME): $(FILE_NAME).c $(CS50_DIR)/cs50.c $(CS50_DIR)/cs50.h
	$(CC) $(CFLAGS) -I$(CS50_DIR) $(FILE_NAME).c $(CS50_DIR)/cs50.c -o $(FILE_NAME)

clean:
	rm -f $(FILE_NAME)

.PHONY: clean