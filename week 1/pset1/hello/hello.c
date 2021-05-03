#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Retrieves user's name
    string name = get_string("What's your name? ");
    // Greets user
    printf("hello, %s\n", name);
    return (0);
}