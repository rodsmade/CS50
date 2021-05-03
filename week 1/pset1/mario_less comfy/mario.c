#include <stdio.h>
#include <cs50.h>

int prompt_pyramid_size(void);

int main(void)
{
    int height = prompt_pyramid_size();
    // Main loop for each line that should be printed
    for (int linha = 0; linha < height; linha++)
    {
        // first half of the line, left side of pyramid
        for (int i = 0; i < height; i++)
        {
            if (i < height - linha -  1)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
    return (0);
}

// Limits permitted range for height
int prompt_pyramid_size(void)
{
    int input;
    do
    {
        input = get_int("Height: ");
    }
    while (input < 1 || input > 8);
    return input;
}