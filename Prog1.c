/******************************************************************************

Description :Sort the words by increasing word length
Author : Vivek Ranjan
Date : 15:03,22/10/2026
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 500
#define MAX_WORDS 100

int main(void)
{
    char sentence[MAX_LEN];
    char words[MAX_WORDS][MAX_LEN];
    int count = 0;

    printf("Enter a sentence: ");

    if (fgets(sentence, sizeof(sentence), stdin) == NULL)
        return 1;

    /* Remove newline */
    sentence[strcspn(sentence, "\n")] = '\0';

    /* Remove the final full stop, if present */
    int len = strlen(sentence);
    if (len > 0 && sentence[len - 1] == '.')
        sentence[len - 1] = '\0';

    /* Split sentence into words */
    char *token = strtok(sentence, " \t");

    while (token != NULL && count < MAX_WORDS)
    {
        /* Convert every word to lowercase */
        for (int i = 0; token[i] != '\0'; i++)
            token[i] = (char)tolower((unsigned char)token[i]);

        strcpy(words[count], token);
        count++;

        token = strtok(NULL, " \t");
    }

    /* Stable insertion sort by word length */
    for (int i = 1; i < count; i++)
    {
        char key[MAX_LEN];
        strcpy(key, words[i]);

        int j = i - 1;

        while (j >= 0 &&
               strlen(words[j]) > strlen(key))
        {
            strcpy(words[j + 1], words[j]);
            j--;
        }

        strcpy(words[j + 1], key);
    }

    /* Print output */
    if (count > 0)
        words[0][0] =
            (char)toupper((unsigned char)words[0][0]);

    for (int i = 0; i < count; i++)
    {
        if (i > 0)
            printf(" ");

        printf("%s", words[i]);
    }

    printf(".\n");

    return 0;
}
