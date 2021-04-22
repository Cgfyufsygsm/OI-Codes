#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    int n;
    cin >> n;
    int a[n], b[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        b[i] = 0;
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                if (a[i] == a[j] + a[k] && a[i] != a[j] && a[j] != a[k])
                    b[i] = 1;
    int count = 0;
    /* for (int i = 0; i < n; i++)
    {
        cout << b[i] << " ";
    }*/
    for (int i = 0; i < n; i++)
    {
        if (b[i] == 1)
            count++;
    }
    cout << count << endl;
    return 0;
}