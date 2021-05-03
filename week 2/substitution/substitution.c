#include <cs50.h>       // get_string()
#include <ctype.h>      // isalpha(), isupper(), islower(), toupper(), tolower()
#include <stdio.h>      // printf()
#include <string.h>      // strlen()

int     input_is_alphabetic(string input);
string  string_to_upper(string s);
string  string_to_lower(string s);
int     key_is_valid(string key);
string  substitution(string plaintext, string key);

int     main(int argc, string argv[])
{
    string key = argv[1];
    if (argc != 2 || !key_is_valid(key))
    {
        printf("Usage:  ./substitution key\n");
        printf("Usage:  Do not input any more than one argument.\n");
        printf("Usage:  Do not input any more than 26 letters.\n");
        printf("Usage:  There must be no repetition of letters.\n");
        printf("Info:   Input is case-insensitive.\n");
        return (1);
    }
    // Gets plaintext:
    string plaintext = get_string("plaintext: ");
    string ciphertext = plaintext;
    // Encrypts message:
    ciphertext = substitution(plaintext, key);
    // Returns ciphered message:
    printf("ciphertext: %s\n", ciphertext);
    return (0);
}

// Sweeps an array to check if its content is only letters, case-insensitive (lower or upper)
int     input_is_alphabetic(string input)
{
    for (int i = 0; input[i]; i++)
    {
        if (!isalpha(input[i]))
        {
            return (0);
        }
    }
    return (1);
}

string  string_to_upper(string s)
{
    int length = strlen(s);
    for (int i = 0; i < length; i++)
    {
        if (islower(s[i]))
        {
            s[i] = toupper(s[i]);
        }
    }
    return (s);
}

string  string_to_lower(string s)
{
    int length = strlen(s);
    for (int i = 0; i < length; i++)
    {
        if (isupper(s[i]))
        {
            s[i] = tolower(s[i]);
        }
    }
    return (s);
}

int     key_is_valid(string key)
{
    // TODO: see if there's only 26 characters
    int length = strlen(key);
    if (length != 26)
    {
        return (0);
    }
    // Checksum is the sum from 65 ('A') through 90 ('Z') and is the same regardless of the order the letters come in;
    // Internal sum is the sum of the integer value of every character in the key. It's meant to match checksum if every letter does appear only once;
    int checksum = 0, internal_sum = 0;
    for (int i = 0; i < 26; i++)
    {
        // Checks if it's only letters, otherwise returns false (0):
        if (!isalpha(key[i]))
        {
            return (0);
        }
        // For the sake of simplicity, changing every character to uppercase for the internal sum:
        internal_sum += toupper(key[i]);
        checksum += 'A' + i;
    }
    // Compares checksum with the internal sum, thus the unicity of each letter in the key;
    // Not being the same means there's at least one repeated byte in the key (given the length has already been checked to be 26), thus returns false (0):
    if (internal_sum != checksum)
    {
        return (0);
    }
    return (1);
}

// Substitutes the string!
string  substitution(string plaintext, string key)
{
    int length = strlen(plaintext);
    // TODO: acho que esse for tá errado o 26, n seria length of plaintext?
    for (int i = 0; i < length; i++)
    {
        // if char is not alphabetic, skips substitution and proceeds to next char.
        if (isalpha(plaintext[i]))
        {
            if (islower(plaintext[i]))
            {
                plaintext[i] = tolower(key[plaintext[i] - 'a']);
            }
            else
            {
                plaintext[i] = toupper(key[plaintext[i] - 'A']);
            }
        }
    }
    return (plaintext);
}
