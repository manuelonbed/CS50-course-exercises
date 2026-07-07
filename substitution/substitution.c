#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_user_input(int nArguments, char *arguments[], string key);
void encrypt_message(string key, string message, char encrypted_message[]);

int main(int argc, char *argv[])
{

    if (check_user_input(argc, argv, argv[1]) == 0) // check key input
    {
        string message = get_string("plaintext:  "); // ask user for text input
        char encrypted_message[strlen(message)]; // initiate empty array with same length as message
        encrypted_message[strlen(message)] = '\0'; // last arrays character to null

        string key = argv[1]; // equal key to user key input

        encrypt_message(key, message,
                        encrypted_message); // encrypts message and stores it in the array

        int a = 0;
        printf("ciphertext: ");
        do // iterate through the array
        {
            printf("%c", encrypted_message[a]); // prints the encrypted message
            a++;
        }
        while (encrypted_message[a]);
        printf("\n");
    }
    else
    {
        printf("Usage: ./substitution key (26 characters long)\n");
        return 1; // exits program in case inputs are incorrect
    }
}

int check_user_input(int nArguments, char *arguments[], string key)
{

    if (nArguments == 2 && strlen(key) == 26 &&
        arguments[1] !=
            NULL) // checks if the user input is a single command argument, 26 characters long and
    // whether it stars with NULL
    {

        // check double characters in key

        for (int j = 0; key[j] != '\0'; j++)
        {
            for (int k = 0; key[k] != '\0'; k++)
            {
                if (j != k)
                {
                    if (toupper(key[j]) == toupper(key[k]))
                    {
                        return 1;
                    }
                }
            }
        }

        int i = 0;
        do // iterate through the string
        {
            if (isalpha(key[i])) // check if position in key[i] is a char
            {
                i++;
            }
            else
            {
                return 1;
            }
        }
        while (key[i]);
        return 0;
    }
    else
    {
        return 1;
    }
}

void encrypt_message(string key, string message, char encrypted_message[])
{
    int i = 0;
    while (message[i])
    {
        if (message[i] >= 'A' && message[i] <= 'Z')
        {
            encrypted_message[i] = toupper((key[message[i] % 65]));
        }
        else if (message[i] >= 'a' && message[i] <= 'z')
        {
            encrypted_message[i] = tolower((key[message[i] % 97]));
        }
        else
        {
            encrypted_message[i] = (message[i]);
        }
        i++;
    }
}
