#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void caesar_cipher(string sentence, int key, char array[]);

int main(int argc, char *argv[])
{

    if (argc == 2)
    {
        string key = argv[1];
        int i = 0;
        do
        {
            if (isdigit(key[i]))
            {
                i++;
            }
            else
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
        while (key[i]);

        string sentence = get_string("plaintext:  ");
        char array[strlen(sentence)];
        array[strlen(sentence)] = '\0';
        caesar_cipher(sentence, atoi(key), array);

        int a = 0;
        printf("ciphertext: ");
        do
        {
            printf("%c", array[a]);
            a++;
        }
        while (array[a]);
        printf("\n");
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

void caesar_cipher(string sentence, int key, char array[])
{
    int i = 0;
    do
    {
        if (sentence[i] >= 'A' && sentence[i] <= 'Z')
        {
            array[i] = (sentence[i] + key - 65) % 26 + 65;
        }
        else if (sentence[i] >= 'a' && sentence[i] <= 'z')
        {
            array[i] = (sentence[i] + key - 97) % 26 + 97;
        }
        else
        {
            array[i] = (sentence[i]);
        }

        i++;
    }

    while (sentence[i]);
}
