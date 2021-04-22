#include <iostream>
using std::cin;
using std::cout;
using std::endl;
int main()
{
    int n;
    cin >> n;
    int a[n - 1];
    for (int i = 0; i <= n - 1; i++)
    {
        cin >> a[i];
    }
    cout << "0 ";
    for (int i = 1; i < n; i++)
    {
        int count = 0;
        for (int j = 0; j < i; j++)
        {
            if (a[j] < a[i])
                count++;
        }
        cout << count << " ";
    }
    cout << endl;
    return 0;
}