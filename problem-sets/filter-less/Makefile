FILE_NAME = filter

$(FILE_NAME): $(FILE_NAME).c helpers.c helpers.h ../cs50.c ../cs50.h
	gcc -Wall -Wextra -I.. $(FILE_NAME).c helpers.c ../cs50.c -o $(FILE_NAME) -lm

clean:
	rm -f $(FILE_NAME)

.PHONY: clean