#include <iostream>
using namespace std;

bool lie[30] = {0}, zs[30] = {0}, ys[30] = {0};
int n, tot = 0, ans[25] = {0};

void print()
{
    for (int i = 1; i < n; i++)
        cout << ans[i] << " ";
    cout << ans[n] << endl;
    return;
}

void dfs(int i)
{
    if (i == n + 1)
    {
        tot++;
        if (tot <= 3)
            print();
        return;
    }
    else
    {
        for (int j = 1; j <= n; j++)
        {
            if ((!lie[j]) && (!zs[i + j]) && (!ys[i - j + n]))
            {
                ans[i] = j;
                lie[j] = 1;
                zs[i + j] = 1;
                ys[i - j + n] = 1;
                dfs(i + 1);
                lie[j] = 0;
                zs[i + j] = 0;
                ys[i - j + n] = 0;
            }
        }
    }
    return;
}
int main()
{
    cin >> n;
    dfs(1);
    //print();
    cout << tot << endl;
    return 0;
}