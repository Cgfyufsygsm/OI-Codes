#include <iostream>
#include <string>
using namespace std;

void guess(string a, string b)
{
    int chance = 7;
    bool used[256] = {0}, guessed[256] = {0};
    int left = 0;
    for (int i = 0; i < a.length(); i++)
    {
        if (!used[a[i]])
            left++;
        used[a[i]] = true;
    }
    //cout << left <<" " <<chance<<endl;
    for (int i = 0; i < b.length() && chance > 0 && left > 0; i++)
    {
        if (used[b[i]] && (!guessed[b[i]]))
        {
            guessed[b[i]] = true;
            left--;
            //cout<<i<<" "<<"left"<<left<<"chance "<<chance;
            continue;
        }
        if ((!used[b[i]]) || guessed[b[i]])
        {
            chance--;
            //cout<<i<<" "<<"left"<<left<<"chance "<<chance;
            continue;
        }
        
    }
    if (left == 0)
    {
        cout << "You win." << endl;
        return;
    }
    if (chance == 0)
    {
        cout << "You lose." << endl;
        return;
    }
    cout << "You chickened out." << endl;
    return;
}

int main()
{
    string a, b;
    int rnd;
    for (;;)
    {
        cin >> rnd;
        if (rnd == -1)
            break;
        cin >> a >> b;
        cout << "Round " << rnd << endl;
        guess(a, b);
    }
    return 0;
}