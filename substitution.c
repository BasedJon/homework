#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string Encipher(string text);
int Validate(string text, int length);
int Alphabetical(string text);

string cipher;

int main(int argc, string argv[])
{
    int validOrNot = Validate(argv[1], argc);
    switch (validOrNot)
    {

        case 1:
            printf("Usage: ./substitution key\n");
            return 1;
        case 2:
            printf("Key must contain 26 characters.\n");
            return 1;
        case 3:
            printf("Key must only contain alphabetical characters.\n");
            return 1;
        case 4:
            printf("Key must not contain repeated characters.\n");
            return 1;
    }
    string text = get_string("plaintext: ");
    printf("ciphertext: %s\n", Encipher(text));
}

int Validate(string text, int length)
{
    if (length != 2)
        return 1;
    int strlen = 0;
    int duplicateCounter[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (int i = 0; text[i] != 0; i++)
    {
        if (i > 25)
            return 2;
        text[i] = tolower(text[i]);
        if (text[i] >= 97 && text[i] <= 122)
        {
            strlen++;
            duplicateCounter[text[i] - 97]++;
        }
        else
            return 3;
    }

    if (strlen < 26)
        return 2;

    for (int i = 0; i < 26; i++)
    {
        int x = duplicateCounter[i];
        // printf("Duplicate array at %i is = %i\n", i, x);
        if (duplicateCounter[i] > 1)
        {
            return 4;
        }
    }
    cipher = text;

    // for (int i = 0; i < 26; i++)
    // {
    //     printf("Cipher at %i is = %c\n", i, cipher[i]);
    // }
    return 0;
}

string Encipher(string text)
{
    for (int i = 0; text[i] != 0; i++)
    {
        if (text[i] >= 97 && text[i] <= 122)
        {
            text[i] = cipher[text[i] - 97];
        }
        else if (text[i] >= 65 && text[i] <= 90)
        {
            text[i] = cipher[text[i] + 32 - 97] - 32;
        }
    }
    return text;
}
