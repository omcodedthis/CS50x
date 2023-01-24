// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// function prototyping
bool valid(string password);
bool check_for_upper(string password);
bool check_for_lower(string password);
bool check_for_symbol(string password);
bool check_for_number(string password);


// main prompts the user for a password. If the password is valid, "Your password is valid!" is printed.
// Else, an error text is shown.
int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// valid checks that the password has at least one upper, lower & symbol. If all of these are present, true is
// returned to main. Else, false is returned.
bool valid(string password)
{
    bool checkupper = check_for_upper(password);
    bool checklower = check_for_lower(password);
    bool checksymbol = check_for_symbol(password);
    bool checknumber = check_for_number(password);

    if ((checkupper == true) && (checklower == true) && (checksymbol == true) && (checknumber == true))
    {
        return true;
    }
    else
    {
        return false;
    }
}


// check_for_upper/lower/symbol checks all the characters in the password using a for-loop. If the specified character is present,
// true is returned to valid. Else, false is returned.
bool check_for_upper(string password)
{
    int length = strlen(password);

    for (int i = 0; i < length; i++)
    {
        if (isupper(password[i]))
        {
            return true;
        }
    }
    return false;

}




bool check_for_lower(string password)
{
    int length = strlen(password);

    for (int i = 0; i < length; i++)
    {
        if (islower(password[i]))
        {
            return true;
        }
    }
    return false;

}



bool check_for_number(string password)
{
    int length = strlen(password);

    for (int i = 0; i < length; i++)
    {
        if (isdigit(password[i]))
        {
            return true;
        }
    }
    return false;

}




bool check_for_symbol(string password)
{
    int length = strlen(password);
    for (int i = 0; i < length; i++)
    {
        if (!(isalnum(password[i])))
        {
            return true;
        }
    }
    return false;

}