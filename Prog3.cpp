
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

int main()
{
    string sentence;
    vector<string> words;

    cout << "Enter a sentence: ";
    getline(cin, sentence);

    /* Remove the final full stop */
    if (!sentence.empty() && sentence.back() == '.')
        sentence.pop_back();

    /* Extract words */
    string word;
    for (char &ch : sentence)
        ch = static_cast<char>(
            tolower(static_cast<unsigned char>(ch)));

    size_t pos = 0;

    while (pos < sentence.size())
    {
        while (pos < sentence.size() &&
               isspace(static_cast<unsigned char>(sentence[pos])))
            pos++;

        size_t start = pos;

        while (pos < sentence.size() &&
               !isspace(static_cast<unsigned char>(sentence[pos])))
            pos++;

        if (start < pos)
            words.push_back(sentence.substr(start, pos - start));
    }

    /* Stable sort by increasing word length */
    stable_sort(words.begin(), words.end(),
        [](const string &a, const string &b)
        {
            return a.length() < b.length();
        });

    /* Capitalize the first letter */
    if (!words.empty())
        words[0][0] = static_cast<char>(
            toupper(static_cast<unsigned char>(words[0][0])));

    /* Print result */
    for (size_t i = 0; i < words.size(); i++)
    {
        if (i > 0)
            cout << " ";

        cout << words[i];
    }

    cout << "." << endl;

    return 0;
}
