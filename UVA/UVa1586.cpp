#include <iostream>
#include <string>
#include <cstdio>
using namespace std;
int tenpower(int n);

int main()
{
    int n;
    cin >> n;
    for (int j = 1; j <= n; j++)
    {
        string s;
        cin >> s;
        s = s + '\\';
        double c = 0, h = 0, o = 0, n = 0, sum = 0;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == 'C') //????C???????
            {
                c += 12.01;
                int count0 = 0;
                for (int k = i + 1; k < s.length(); k++)
                {
                    if (s[k] >= '0' && s[k] <= '9')
                        count0++;
                    else
                        break;
                }
                int count = count0, num = 0;
                for (int k = i + 1; k <= i + count0; k++)
                {
                    if (count != 0)
                        num = num + ((s[k] - '0') * tenpower(count));
                    count--;
                }
                num /= 10;
                if (num != 0)
                    c += (num - 1) * 12.01;
                //cout << num << endl;
            }
            if (s[i] == 'H') //????H???????
            {
                h += 1.008;
                int count0 = 0;
                for (int k = i + 1; k < s.length(); k++)
                {
                    if (s[k] >= '0' && s[k] <= '9')
                        count0++;
                    else
                        break;
                }
                int count = count0, num = 0;
                for (int k = i + 1; k <= i + count0; k++)
                {
                    if (count != 0)
                        num = num + ((s[k] - '0') * tenpower(count));
                    count--;
                }
                num /= 10;
                if (num != 0)
                    h += (num - 1) * 1.008;
                //cout << num << endl;
            }
            if (s[i] == 'O') //????O???????
            {
                o += 16;
                int count0 = 0;
                for (int k = i + 1; k < s.length(); k++)
                {
                    if (s[k] >= '0' && s[k] <= '9')
                        count0++;
                    else
                        break;
                }
                int count = count0, num = 0;
                for (int k = i + 1; k <= i + count0; k++)
                {
                    if (count != 0)
                        num = num + ((s[k] - '0') * tenpower(count));
                    count--;
                }
                num /= 10;
                if (num != 0)
                    o += (num - 1) * 16;
                //cout << num << endl;
            }
            if (s[i] == 'N') //????N???????
            {
                n += 14.01;
                int count0 = 0;
                for (int k = i + 1; k < s.length(); k++)
                {
                    if (s[k] >= '0' && s[k] <= '9')
                        count0++;
                    else
                        break;
                }
                int count = count0, num = 0;
                for (int k = i + 1; k <= i + count0; k++)
                {
                    if (count != 0)
                        num = num + ((s[k] - '0') * tenpower(count));
                    count--;
                }
                num /= 10;
                if (num != 0)
                    n += (num - 1) * 14.01;
                //cout << num << endl;
            }
        }
        sum = c + o + n + h;
        printf("%.3f\n", sum);
    }
    return 0;
}

int tenpower(int n)
{
    int sum = 1;
    for (int i = 1; i <= n; i++)
        sum *= 10;
    return sum;
}
