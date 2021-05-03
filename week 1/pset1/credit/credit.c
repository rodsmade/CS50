#include <stdio.h>
#include <cs50.h>

long int prompt_card_number(void);
int number_is_valid(long int number);

int main(void)
{
    // Prompts for input and discards whatever's less than 4000000000000 (VISA's lowest interval)
    long int number = prompt_card_number();
    // Sieves for obviously invalid numbers (out of stipulated ranges)
    if (number < 4000000000000
        || (number > 4999999999999      && number < 340000000000000)
        || (number > 349999999999999     && number < 370000000000000)
        || (number > 379999999999999     && number < 4000000000000000)
        || (number > 4999999999999999    && number < 5100000000000000)
        ||  number > 5599999999999999)
    {
        printf("INVALID\n");
    }
    // if number is valid, decides which company the card belongs to
    else if (number_is_valid(number))
    {
        if (number >= 5100000000000000 && number <= 5599999999999999)
        {
            printf("MASTERCARD\n");
        }
        else if ((number >= 4000000000000 && number <= 4999999999999)
                 || (number >= 4000000000000000 && number <= 4999999999999999))
        {
            printf("VISA\n");
        }
        else
        {
            printf("AMEX\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
    return (0);
}

long int prompt_card_number(void)
{
    long int input;
    do
    {
        input = get_long("Number: ");
    }
    while (input < 0 || input > 9999999999999999);
    return input;
}

// does the maths and returns 1 if valid, 0 otherwise!
int number_is_valid(long int number)
{
    int odd_sum = 0;
    int even_sum = 0;
    int digit = 0;
    for (int i = 0; i < 16; i++)
    {
        // sifts for rightmost digit
        digit = number % 10;
        // decides whether said digit belongs to the simple sum (odd_sum - beginning in the last digit)
        // or the tricky one (even_sum - beginning in the second but last digit)
        if (i % 2 == 0)
        {
            odd_sum += digit;
        }
        else
        {
            if (2 * digit < 10)
            {
                even_sum += 2 * digit;
            }
            else
            {
                // 2*digit overflows unitary value, hence sums each digit individually
                even_sum += (2 * digit) / 10 + (2 * digit) % 10;
            }
        }
        number = number / 10;
    }
    if ((odd_sum + even_sum) % 10 == 0)
    {
        return (1);    // card number is valid!
    }
    else
    {
        return (0);    // card number is not valid!
    }
}
