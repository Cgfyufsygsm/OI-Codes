#include <iostream>
#include <string>
using namespace std;

int main()
{
    string text;
    int n;
    cin >> n >> text;
    for (int i = 0; i < text.size(); i++)
    {
        if (text[i] + n <= 'z')
            text[i] += n;
        else
        {
            text[i] = text[i] + n - 26;
        }
    }
    cout << text << endl;
}
