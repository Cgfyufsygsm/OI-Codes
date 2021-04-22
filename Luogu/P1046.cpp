#include <iostream>
using std::cin;
using std::cout;
using std::endl;
int main()
{
    int a[10], l, count,i;
    for (i = 0; i <= 9; i++)
    {
        cin >> a[i];
    }
    cin >> l;
    for (i = 0; i <= 9; i++)
    {
        if (l >= a[i])
            count++;
        else if (l + 30 >= a[i])
            count++;
    }
    cout<<count<<endl;
}