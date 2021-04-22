#include <iostream>
#include <string>
using namespace std;

int main()
{
    int T;
    cin >> T;
    for (int kase = 1; kase <= T; kase++)
    {
        string s;
        cin >> s;
        int count = 0, score = 0;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == 'O')
            {

                count++;
                score += count;
            }
            if (s[i] == 'X')
            {
                count = 0;
            }
        }
        cout << score << endl;
    }
    return 0;
}