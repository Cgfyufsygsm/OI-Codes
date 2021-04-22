#include <iostream>
using namespace std;

unsigned a[100010], n;

void qsort(int left, int right)
{
    unsigned i = left, j = right, t, k = a[left];
    if (i >= j)
        return;
    while (i < j)
    {
        while ((i < j) && a[j] >= k)
            j--;
        while (i<j&&a[i]<=k)
            i++;
        t=a[i];
        a[i]=a[j];
        a[j]=t;
    }
    a[left]=a[i];
    a[i]=k;
    qsort(left,i-1);
    qsort(i+1,right);
    return;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    qsort(0, n - 1);
    for (int i = 0; i < n - 1; i++)
        cout << a[i] << " ";
    cout << a[n - 1] << endl;
    return 0;
}