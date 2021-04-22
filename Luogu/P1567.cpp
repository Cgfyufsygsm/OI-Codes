#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    int n;
    cin >> n;
    int count = 0;
    long t[n];
    int max[n];
    for (int i = 0; i < n; i++)
    {
        cin >> t[i];
        max[i] = 0;
    }
    for (int i = 1; i < n; i++)
    {
        if (t[i] > t[i - 1])
            count++;
        else
        {
            max[i]=count;
            count = 0;
        }
    }
    int maxmax=0;
    for (int i = 0; i < n; i++)
    {
        if(max[i]>maxmax)
            maxmax=max[i];
    }
    cout << maxmax+1 << endl;
    return 0;
}