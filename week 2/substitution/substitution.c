#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

int input_is_numeric(char input[]);
string caesar_cipher(string plaintext, int key);

int main(int argc, string argv[])
{
    /*Your program must accept a single command-line argument, the key to use for the substitution. The key itself should be case-insensitive, 
    so whether any character in the key is uppercase or lowercase should not affect the behavior of your program.
    If your program is executed without any command-line arguments or with more than one command-line argument, 
    your program should print an error message of your choice (with printf) and return from main a value of 1 (which tends to signify an error) immediately.
    If the key is invalid (as by not containing 26 characters, containing any character that is not an alphabetic character, 
    or not containing each letter exactly once), your program should print an error message of your choice (with printf) and return from main a value of 1 immediately.
    */
    // Program accepts a single command-line argument, a non-negative integer. Otherwise, returns error message:
    if (argc != 2 || argv[1] < 0 || !input_is_numeric(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return (1);
    }
    // Converts string to integer and normalises key so as it's less than or equal to 26:
    int key = atoi(argv[1]) % 26;
    // Gets plaintext:
    string plaintext = get_string("plaintext: ");
    string ciphertext = plaintext;
    // Encrypts message:
    ciphertext = caesar_cipher(plaintext, key);
    // Returns ciphered message:
    printf("ciphertext: %s\n", ciphertext);
    return (0);
}

// Sweeps an array to check if it's content is numeric
int input_is_numeric(char input[])
{
    for (int i = 0; input[i]; i++)
    {
        if (!isdigit(input[i]))
        {
            return (0);
        }
    }
    return (1);
}

// Caesar-cipher the string!
string caesar_cipher(string plaintext, int key)
{
    int complement = 26 - key;
    for (int i = 0; plaintext[i]; i++)
    {
        // Checks if current char is alphabetic, otherwise goes to the next
        if (isalpha(plaintext[i]))
        {
            if (plaintext[i] >= 'a' && plaintext [i] <= 'z')
            {
                // Normalises char with 'a' if char is lowercase
                // 'a' - 'a' = 0 so we need the offset of 1 to operate properly (i.e. 'a' = 1, 'b' = 2 ... z = '26')
                if (plaintext[i] + 1 - 'a' + key <= 26)
                {
                    plaintext[i] += key;
                }
                else
                {
                    plaintext[i] -= complement;
                }
            }
            else
            {
                // Otherwise normalises char with 'A' instead
                if (plaintext[i] + 1 - 'A' + 1 + key <= 26)
                {
                    plaintext[i] += key;
                }
                else
                {
                    plaintext[i] -= complement;
                }
            }
        }
    }
    return (plaintext);
}
