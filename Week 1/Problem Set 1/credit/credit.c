#include <cs50.h>
#include <stdio.h>


// define functions called in main
long get_user_card(void);
bool checksum(long card_number);
void print_card_type(long card_number);



// main gets the user's card, and applies the checksum. If the checksum is true, the type of card is printed,
// else INVALID is printed to the terminal.
int main(void)
{
    long card_number = get_user_card();


    if (checksum(card_number))
    {
        print_card_type(card_number);
    }
    else
    {
        printf("INVALID\n");
    }

}




//get_user_card gets the user's input, provided the number inputted is positive.
long get_user_card(void)
{
    long input;
    do
    {
        input = get_long("Number: ");
    }
    while (input < 0);
    return input;
}




// checksum applies Luhn's Algorithm to check if the card is valid. It returns a boolean to main.
bool checksum(long card_number)
{
    long total = 0;
    long number1 = 0;
    long number2 = 0;
    long number2_d1 = 0;
    long number2_d2 = 0;


    while (card_number > 0)
    {
        number1 = card_number % 10;
        total += number1;
        card_number = card_number / 10;

        number2 = card_number % 10;
        number2 *= 2;
        number2_d1 = number2 % 10;
        number2_d2 = number2 / 10;
        card_number = card_number / 10;
        total += (number2_d1 + number2_d2);

    }

    if ((total % 10) == 0)
    {
        return true;
    }

    else
    {
        return false;
    }

}




//print_card_type prints the card type, provided the card is valid.
void print_card_type(long card_number)
{
    if (((card_number > 339999999999999) && (card_number < 350000000000000)) || ((card_number > 369999999999999)
            && (card_number < 380000000000000)))
    {
        printf("AMEX\n");
    }

    else if ((card_number > 5099999999999999) && (card_number < 5600000000000000))
    {
        printf("MASTERCARD\n");
    }

    else if (((card_number > 3999999999999) && (card_number < 5000000000000)) || ((card_number > 3999999999999999)
             && (card_number < 5000000000000000)))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}



