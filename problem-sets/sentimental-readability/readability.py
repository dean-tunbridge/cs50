from cs50 import get_string

text = get_string("Text: ")

def count_letters(text):
    letters = 0

    for i in range(len(text)):
        if text[i].isalpha():
            letters += 1

    return letters


def count_words(text):
    return len(text.split())


def count_sentences(text):
    sentences = 0

    for i in range(len(text)):
        if text[i] == '.' or text[i] == '!' or text[i] == '?':
            sentences += 1

    return sentences


letters = count_letters(text)
words = count_words(text)
sentences = count_sentences(text)


letters_per_100 = (letters / words) * 100
sentences_per_100 = (sentences / words) * 100

grade = round(0.0588 * letters_per_100 - 0.296 * sentences_per_100 - 15.8)

if grade < 1:
    print("Before Grade 1")
elif grade >= 16:
    print("Grade 16+")
else:
    print(f"Grade {grade}")
