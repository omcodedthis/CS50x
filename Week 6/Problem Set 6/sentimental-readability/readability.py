from cs50 import get_string


# main() gets the text from the user & checks Grade Level of the text using the Coleman-Liau
# formula.
def main():

    user_text = get_string("Text: ")

    total_letters = find_total_letters(user_text)
    total_words = find_total_words(user_text)
    total_sentences = find_total_sentences(user_text)

    l = (total_letters / total_words) * 100
    s = (total_sentences / total_words) * 100

    cl_index = (0.0588 * l - 0.296 * s - 15.8) + 0.5

    print_grade(cl_index)


# find_total_letters() counts the total number of letters in the entire text.
def find_total_letters(text):

    length = len(text)
    total = 0
    for i in range(length):

        if (text[i].isalpha()):

            total += 1

    return total


# find_total_words() counts the total number of words in the entire text by counting
# the number of spaces and returning the total + 1 (fencepost problem).
def find_total_words(text):

    length = len(text)
    total = 0
    for i in range(length):

        if (text[i] == " "):

            total += 1

    return total + 1


# find_total_sentences() counts the total number of sentences in the entire text by
# counting the number of ".", "!" or "?".
def find_total_sentences(text):

    length = len(text)
    total = 0
    for i in range(length):

        if ((text[i] == ".") or (text[i] == "!") or (text[i] == "?")):

            total += 1

    return total


# print_grade() prints the respective Grade Level to the terminal.
def print_grade(cl_index):

    if (cl_index >= 16):

        print("Grade 16+\n")

    elif (cl_index <= 1):
        print("Before Grade 1\n")

    else:
        print("Grade " + str(cl_index))


main()