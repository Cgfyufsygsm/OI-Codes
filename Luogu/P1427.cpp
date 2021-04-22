#include <iostream>
using std::cin;
using std::cout;
using std::endl;
int main()
{
    int i, a[100];
    for (i = 0;; i++)
    {
        cin >> a[i];
        if (a[i] == 0)
            break;
    }
    for (int j = i - 1; j >= 0; j--)
    {
        cout << a[j] << " ";
    }
    cout << endl;
    return 0;
}
