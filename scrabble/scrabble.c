#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void string_to_upper(string word, char word_to_upper[]);
int word_score(char array[]);

int main(void)
{
    string a = "manuel";
    string first_word = get_string("Enter the first word: "); // get input from user for first word
    string second_word =
        get_string("Enter the second word: ");          // get input from user for second word
    char first_word_array[strlen(first_word) + 1] = {}; // initiate array with size of the string
    char second_word_array[strlen(second_word) + 1] = {};
    string_to_upper(first_word, first_word_array); // store the first string in upper case in array
    string_to_upper(second_word,
                    second_word_array); // store the second string in upper case in array

    int first_score = word_score(first_word_array);
    int second_score = word_score(second_word_array);
    if (first_score > second_score)
    {
        printf("Player 1 wins! \n");
    }
    else if (first_score == second_score)
    {
        printf("Tie! \n");
    }
    else
    {
        printf("Player 2 wins! \n");
    }
}

void string_to_upper(string word, char word_to_upper[])
{
    int i = 0;
    do
    {
        word_to_upper[i] = toupper(word[i]);
        i++;
    }
    while (word[i]);
}

int word_score(char array[])
{
    int i = 0;
    int score = 0;
    int letter_scores[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                           1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

    do
    {
        if (array[i] >= 'A' && array[i] <= 'Z')
        {
            score += letter_scores[array[i] - 65];
        }

        i++;
    }
    while (array[i]);
    return score;
}
