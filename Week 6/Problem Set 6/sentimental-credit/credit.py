# main() gets the card number from the user and checks whether it is a valid card.
def main():
    card_number = get_user_card()

    if (checksum(card_number)):

        print_card_type(card_number)

    else:

        print("INVALID")


# get_user_card() gets the card number from the user and returns it to main() once the user
# enters an int.
def get_user_card():
    while True:
        try:
            card = int(input("Number:"))
            if card > 0:
                return card

        except ValueError:
            print("Not an integer!")


# checksum() checks the card number to see if it is a valid number, returning True if it valid
# & False if it is not.
def checksum(card_number):
    total = 0
    number1 = 0
    number2 = 0
    number2_d1 = 0
    number2_d2 = 0

    while card_number > 0:
        number1 = int(card_number % 10)
        total += number1
        card_number = int(card_number / 10)

        number2 = int(card_number % 10)
        number2 *= 2
        number2_d1 = int(number2 % 10)
        number2_d2 = int(number2 / 10)
        card_number = int(card_number / 10)
        total += (number2_d1 + number2_d2)

    if ((total % 10) == 0):
        return True

    else:
        return False


# print_card_type() prints the type of card, provided it matches the restrictions of the first
# few digits of each card type.
def print_card_type(card_number):

    if (((card_number > 339999999999999) and (card_number < 350000000000000)) or ((card_number > 369999999999999) and (card_number < 380000000000000))):
        print("AMEX")

    elif ((card_number > 5099999999999999) and (card_number < 5600000000000000)):
        print("MASTERCARD")

    elif (((card_number > 3999999999999) and (card_number < 5000000000000)) or ((card_number > 3999999999999999) and (card_number < 5000000000000000))):
        print("VISA")

    else:
        print("INVALID")


main()