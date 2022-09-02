#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


bool valid_key(string key);


int main(int argc, string argv[])
{
    if (argc == 2)
    {
        if (valid_key(argv[1]) == true)
        {
            string key = argv[1];
            int len_key = strlen(key);
            string alphabets = "abcdefghijklmnopqrstuvwxyz";
            string pl_text = get_string("plaintext: ");
            int len_pl = strlen(pl_text);
            char cip_text[len_pl];

            for (int i = 0; i < len_pl; i++)
            {
                if (isupper(pl_text[i]) != 0)
                {
                    for (int j = 0; j < 26; j++)
                    {
                        if (alphabets[j] == tolower(pl_text[i]))
                        {
                            cip_text[i] = toupper(key[j]);
                            break;
                        }
                    }
                }
                else if (islower(pl_text[i]) != 0)
                {
                    for (int j = 0; j < 26; j++)
                    {
                        if (alphabets[j] == pl_text[i])
                        {
                            cip_text[i] = tolower(key[j]);
                            break;
                        }
                    }
                }
                else
                {
                    cip_text[i] = pl_text[i];
                }
            }
            printf("ciphertext: %s\n", cip_text);
            return 0;
        }
        else
        {
            printf("ERROR: Key must be a permutation of 26, non-repeating, alphabets only.\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }
}





bool valid_key(string key)
{
    int m = 0;
    int len = strlen(key);

    if(len == 26)
    {
        for (char c = 'a'; c <= 'z'; c++)
        {
            for (int i = 0; i < len; i++)
            {
                if(tolower(key[i]) == c)
                {
                    m++;
                    break;
                }
            }
        }
        if (m == 26)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}