#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
using std::sort;

int main()
{
    int N;
    cin >> N;
    int n[N];
    int ans[N], count = 1;
    for (int i = 0; i < N; i++)
    {
        cin >> n[i];
        ans[i] = 0;
    }
    sort(n, n + N);
    ans[0]=n[0];
    for (int i = 1; i < N; i++)
    {
        if (n[i] != n[i - 1])
        {
            count++;
            ans[i] = n[i];
        }
    }
    cout << count << endl;
    for (int i = 0; i < N; i++)
    {
        if (ans[i])
            cout << ans[i] << " ";
    }
    return 0;
}