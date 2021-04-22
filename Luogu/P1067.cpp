#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    short xishu[n + 1];
    for (int i = n; i >= 0; i--)
        cin >> xishu[i];
    int flag = 0;

    for (int i = n; i >= 0; i--)
    {
        if (!xishu[i])
            continue;
        else
        {
            flag = i;
            break;
        }
    }

    for (int i = flag; i >= 0; i--)
    {
        if (xishu[i])
        {
            if (i > 1)
            {
                if (i == flag)
                {
                    if (xishu[i] == 1)
                        cout << "x^" << i;
                    else if (xishu[i] == -1)
                        cout << "-x^" << i;
                    else
                        cout << xishu[i] << "x^" << i;
                    continue;
                }
                if (xishu[i] > 0)
                    if (xishu[i] == 1)
                        cout << "+"
                             << "x^" << i;
                    else
                        cout << "+" << xishu[i] << "x^" << i;
                else if (xishu[i] == -1)
                    cout << "-"
                         << "x^" << i;
                else
                    cout << xishu[i] << "x^" << i;
            }
            else if (i == 1)
            {
                if (xishu[i] != 1 && xishu[i] != -1)
                    if (xishu[i] > 0)
                        cout << "+" << xishu[i] << "x";
                    else
                        cout << xishu[i] << "x";
                else if (xishu[i] > 0)
                    cout << "+x";
                else
                    cout << "-x";
            }
            else
            {
                if (xishu[i] > 0)
                    cout << "+" << xishu[i];
                if (xishu[i] < 0)
                    cout << xishu[i];
            }
        }
    }
    return 0;
}