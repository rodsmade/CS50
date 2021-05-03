#include <cs50.h>
#include <stdio.h>

int prompt_start_size(int i);
int prompt_end_size(int i);

int main(void)
{
    // Prompt for start size (must be greater than or equal to 9)
    int start_size = prompt_start_size(9);
    // Prompt for end size (must be greater than or equal to start size)
    int end_size = prompt_end_size(start_size);
    // Calculate number of years until we reach threshold
    int result = 0;
    for (; start_size < end_size; result++)
    {
        start_size = start_size + (start_size / 3) - (start_size / 4);
    }
    // Print number of years
    printf("Years: %i\n", result);
    return (0);
}

int prompt_start_size(int i)
{
    int input;
    do
    {
        input = get_int("Start size: ");
    }
    while (input < i);
    return input;
}

int prompt_end_size(int i)
{
    int input;
    do
    {
        input = get_int("End size: ");
    }
    while (input < i);
    return input;
}
