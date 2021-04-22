#include <iostream>
#include <string>
using namespace std;
int main()
{
    int N;
    cin >> N;
    for (int kase = 1; kase <= N; kase++)
    {
        int n;
        cin >> n;
        string s = "1";
        for (int i = 2; i <= n; i++)
        {
            s = s + to_string(i);
        }
        //cout<<s<<endl;
        int count[10];
        for (int i = 0; i < 10; i++)
            count[i] = 0;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == '0')
                count[0]++;
            if (s[i] == '1')
                count[1]++;
            if (s[i] == '2')
                count[2]++;
            if (s[i] == '3')
                count[3]++;
            if (s[i] == '4')
                count[4]++;
            if (s[i] == '5')
                count[5]++;
            if (s[i] == '6')
                count[6]++;
            if (s[i] == '7')
                count[7]++;
            if (s[i] == '8')
                count[8]++;
            if (s[i] == '9')
                count[9]++;
        }
        for (int i = 0; i < 9; i++)
            cout << count[i] << " ";
        cout << count[9] << endl;
    }
    return 0;
}