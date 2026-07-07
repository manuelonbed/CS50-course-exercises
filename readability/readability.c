#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

void count_lws(string text, int nArray[]);
float Coleman_Liau_index(int nLetters, int nWords, int nSentences);

int main(void)
{
    string text = get_string("Enter your text here: ");
    int nArray[3];
    count_lws(text, nArray);
    int nLetters = nArray[0];
    int nWords = nArray[1];
    int nSentences = nArray[2];
    float index = Coleman_Liau_index(nLetters, nWords, nSentences);
    int grade = (int) index;

    //  If the grade level is 16 or higher (equivalent to or greater than a senior undergraduate
    //  reading level),
    // your program should output “Grade 16+” instead of giving the exact index number.
    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    // If the grade level is less than 1, your program should output “Before Grade 1”.
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

// count the number of letters, words and sentences

void count_lws(string text, int nArray[])
{
    int nLetters = 0;
    int nWords = 1;
    int nSentences = 0;

    int i = 0;
    do
    {
        // check if char is a space (' ')
        if (text[i] == ' ')
        {
            nWords++;
        }
        // check if char is a point (.)
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            nSentences++;
        }
        // check if char is a letter
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            nLetters++;
        }
        i++;
    }
    while (text[i]);

    nArray[0] = nLetters;
    nArray[1] = nWords;
    nArray[2] = nSentences;
}

// Coleman-Liau index.
// index = 0.0588 * L - 0.296 * S - 15.8
// where L is the average number of letters per 100 words in the text,
// and S is the average number of sentences per 100 words in the text.

float Coleman_Liau_index(int nLetters, int nWords, int nSentences)
{

    float average_letters = (float) nLetters * 100 / nWords;
    float average_sentences = (float) nSentences * 100 / nWords;
    float index = 0.0588 * average_letters - 0.296 * average_sentences - 15.8;
    return round(index);
}
