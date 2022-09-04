#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>



int count_letters(string t);
int count_words(string t);
int count_sentences(string t);



int main(void)
{
    string text = get_string("Text: ");

    float index = 0;
    int sent = count_sentences(text);
    int words = count_words(text);
    int letters = count_letters(text);

    index = 0.0588 * (100 * (float) letters / (float) words) - 0.296 * (100 * (float) sent / (float) words) - 15.8;

    if (index < 16 && index >= 0)
    {
        printf("Grade %i\n", (int) round(index));
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Before Grade 1\n");
    }
}




int count_letters(string t)
{
    int letters = 0;
    //loop for counting total number of letters in the input string,
    for (int i = 0; i < strlen(t); i++)
    {
        if (isupper(t[i]) || islower(t[i])) //check for lowercase or uppercase
        {
            letters++;
        }
    }
    return letters;
}



int count_words(string t)
{
    int words = 1;

    //loop for counting the number of words in the input string,
    for (int i = 0; i < strlen(t); i++)
    {
        if (t[i] == ' ')
        {
            words++;
        }
    }
    return words;
}



int count_sentences(string t)
{
    int sent = 0;

    //loops for counting the number of sentences in the input strings,
    for (int i = 0; i < strlen(t); i++)
    {
        if (t[i] == '.' || t[i] == '!' || t[i] == '?')
        {
            sent++;
        }
    }
    return sent;
}