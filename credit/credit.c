#include <cs50.h>
#include <math.h>
#include <stdio.h>

long integer_length(long n);
long ask_user_card_number(void);
bool luhn_algorithm(long card_n);
void check_card_company(long number);

int main(void)
{
    long stored_number = ask_user_card_number();

    if (luhn_algorithm(stored_number))
    {
        check_card_company(stored_number);
    }
    else
    {
        printf("INVALID\n");
    }
}

bool luhn_algorithm(long card_n)
{
    int sum = 0;
    do
    {
        sum += (card_n % 10);           // sums last number
        card_n = card_n / 10;           // deletes last number
        int digit = (card_n % 10) * 2;  // stores second to last number *2
        sum += digit / 10 + digit % 10; // sums last and first digit
        card_n = card_n / 10;
    }
    while (card_n > 0);

    if (sum % 10 == 0)
    {

        return true;
    }
    else
    {
        return false;
    }
}

long ask_user_card_number(void)
{
    long n;
    n = get_long("Insert your cards number: ");
    return n;
}

void check_card_company(long number)
{
    int length = integer_length(number);

    int nn = number / (pow(10, length - 2));
    int n_visa = nn / 10;
    if ((nn == 34 || nn == 37) && length == 15)
    {
        printf("AMEX\n");
    }
    else if ((nn == 51 || nn == 52 || nn == 53 || nn == 54 || nn == 55) && length == 16)
    {
        printf("MASTERCARD\n");
    }
    else if ((n_visa == 4) && (length == 13 || length == 16))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
long integer_length(long n)
{

    int count = 0;
    do
    {
        count++;
        n = n / 10;
    }
    while (n > 0);
    return count;
}

/*
    1. Multiply every other digit by 2, starting with the number’s second-to-last digit, and then
   add those products’ digits together.
    2. Add the sum to the sum of the digits that weren’t multiplied by 2.
    3. If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to
   0), the number is valid!

    Print the cards company. Rules:
    All American Express numbers start with 34 or 37; most MasterCard numbers start with 51, 52, 53,
    54, or 55; and all Visa numbers start with 4
*/
