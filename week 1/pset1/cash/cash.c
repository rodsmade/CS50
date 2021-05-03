#include <cs50.h>
#include <math.h>
#include <stdio.h>

float prompt_change_owed(void);

int main(void)
{
    // Transforms dollar value to cents so as to avoid floating point operations imprecision
    int change_in_cents = round(prompt_change_owed() * 100);
    int total_coins_back = 0;
    // starting at 25c, chips away at total change owed by 25 cents at a time,
    // and counts that as one coin returned as change.
    while (change_in_cents >= 25)
    {
        total_coins_back++;
        change_in_cents -= 25;
    }
    while (change_in_cents >= 10)
    {
        total_coins_back++;
        change_in_cents -= 10;
    }
    while (change_in_cents >= 5)
    {
        total_coins_back++;
        change_in_cents -= 5;
    }
    while (change_in_cents >= 1)
    {
        total_coins_back++;
        change_in_cents -= 1;
    }
    printf("%i\n", total_coins_back);
}

// Prompts amount of change owed
float prompt_change_owed(void)
{
    float input;
    // Does not accept negative values
    do
    {
        input = get_float("Change owed: ");
    }
    while (input < 0);
    return input;
}