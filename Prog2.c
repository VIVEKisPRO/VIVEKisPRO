#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 500
#define MAX_WORDS 100

int main(void)
{
    char sentence[MAX_LEN];
    char words[MAX_WORDS][MAX_LEN];
    int lengths[MAX_WORDS];
    int count = 0;

    if (!fgets(sentence, sizeof(sentence), stdin))
        return 1;

    sentence[strcspn(sentence, "\n")] = '\0';

    size_t len = strlen(sentence);
    if (len > 0 && sentence[len - 1] == '.')
        sentence[len - 1] = '\0';

    /* Tokenize and preprocess */
    for (char *token = strtok(sentence, " \t");
         token && count < MAX_WORDS;
         token = strtok(NULL, " \t"))
    {
        for (char *p = token; *p; ++p)
            *p = (char)tolower((unsigned char)*p);

        strcpy(words[count], token);
        lengths[count] = (int)strlen(token);
        ++count;
    }

    /* Stable insertion sort */
    for (int i = 1; i < count; ++i)
    {
        char keyWord[MAX_LEN];
        int keyLen = lengths[i];

        strcpy(keyWord, words[i]);

        int j = i - 1;

        while (j >= 0 && lengths[j] > keyLen)
        {
            strcpy(words[j + 1], words[j]);
            lengths[j + 1] = lengths[j];
            --j;
        }

        strcpy(words[j + 1], keyWord);
        lengths[j + 1] = keyLen;
    }

    if (count > 0)
        words[0][0] = (char)toupper((unsigned char)words[0][0]);

    for (int i = 0; i < count; ++i)
        printf("%s%s", i ? " " : "", words[i]);

    puts(".");

    return 0;
}
