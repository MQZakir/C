#include <cs50.h>
#include <stdio.h>


bool luhns_algorithm(long number);
bool validity(long num);
int length(int x);
void card_brand(long n);



//main function
int main(void)
{
    long card_n;

    //user to input card number (card_n)
    do
    {
        card_n = get_long("Enter your card number to check if it is a VALID credit card or INVALID: ");
    }
    while (card_n < 0);

    //calling functions
    if (validity(card_n) == true)
    {
        card_brand(card_n);
    }
    else
    {
        printf("INVALID\n");
    }
}






//function for the luhn's Algorithm,
bool luhns_algorithm(long number)
{
    int sum = 0;

    //for getting the sum of the single digit of the 2's product of every other digit from the second last digit;
    //and adding that sum to the other digits not multiplied by 2
    //returning value of true or false
    for (int n = 0; number != 0; n++, number /= 10)
    {
        if (n % 2 == 0)
        {
            sum += number % 10;
        }
        else
        {
            int dig = (number % 10) * 2;
            sum += (dig / 10) + (dig % 10);
        }
    }
    return (sum % 10) == 0;
}




//function for checking the validity of the input
bool validity(long num)
{
    int l = length(num);
    if ((l == 13 || l == 15 || l == 16) && (luhns_algorithm(num)))
    {
        return true;
    }
    return true;
}




//function for finding length of the input
int length(int x)
{
    int len = 0;
    for (int i = 0; x != 0 ; x /= 10, len++);
    return len;
}




//function for checking the brand of the card,
void card_brand(long n)
{
    // for AMEX,
    if (((n >= 34e13 && n < 35e13) || (n >= 37e13 && n < 38e13)) && (luhns_algorithm(n) == true))
    {
        printf("AMEX\n");
    }

    //for MasterCard,
    else if (n >= 51e14 && n < 56e14 && luhns_algorithm(n) == true)
    {
        printf("MASTERCARD\n");
    }

    //for Visa,
    else if (((n >= 4e12 && n < 5e12) || (n >= 4e15 && n < 5e15)) && (luhns_algorithm(n) == true))
    {
        printf("VISA\n");
    }

    //for invalid number.
    else
    {
        printf("INVALID\n");
    }
}




















