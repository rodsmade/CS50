#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

int what_grade_is_this(string input);
int count_letters_in(string input);
int count_words_in(string input);
int count_sentences_in(string input);

int main(void)
{
    // TODO: Prompt input string
    string input = get_string("Text: ");
    int readability_index = what_grade_is_this(input);
    if (readability_index > 15)
    {
        printf("Grade 16+\n");
    }
    else if (readability_index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", readability_index);
    }
    return (0);
}

int what_grade_is_this(string input)
{
    int words = count_words_in(input);
    // L is the average number of letters per 100 words in the text.
    float L = count_letters_in(input) / (float) words * 100;
    // S is the average number of sentences per 100 words in the text.
    float S = count_sentences_in(input) / (float) words * 100;
    // Calculate Coleman-Liau's index of readability:
    return ((int) round(0.0588 * L - 0.296 * S - 15.8));
}

int count_letters_in(string input)
{
    int count = 0, i = 0;
    // fancy way of waying "while (input[i] != '\0')" - iterate over whole array
    while (input[i])
    {
        if (isalpha(input[i]))
        {
            count++;
        }
        i++;
    }
    return (count);
}

int count_words_in(string input)
{
    // count stats in 1 bc last word'll end in a period not a space
    int count = 1, i = 0;
    while (input[i])
    {
        if (input[i] == ' ')
        {
            count++;
        }
        i++;
    }
    return (count);
}

int count_sentences_in(string input)
{
    int count = 0, i = 0;
    // For simplicity a sentence is considered to end in either three of the following characters
    // (E.g.: even sentences with "Mr." or "Ms." would be split when the '.' character is found)
    while (input[i])
    {
        if (input[i] == '.' || input[i] == '?' || input[i] == '!')
        {
            count++;
        }
        i++;
    }
    return (count);
}
