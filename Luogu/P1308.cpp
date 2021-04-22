#include <iostream>
#include <string>
using namespace std;
int main()
{
    string word, text;
    getline(cin, word);
    getline(cin, text);
    text = ' ' + text + ' ';
    word = ' ' + word + ' ';
    for (int i = 0; i < word.length(); ++i)
    {
        word[i] = tolower(word[i]);
    }
    for (int i = 0; i < text.length(); ++i)
    {
        text[i] = tolower(text[i]);
    }
    if (text.find(word) == string::npos)
    {
        cout << -1 << endl;
    }
    else
    {
        int loc = text.find(word);
        int count = 0;
        int loc2=text.find(word);
        while(loc2!=string::npos)
        {
            count++;
            loc2=text.find(word,loc2+1);
        }
        cout<<count<<" "<<loc<<endl;
    }
    return 0;
}
