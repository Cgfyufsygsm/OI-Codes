#include <cstdio>
#include <algorithm>
using namespace std;
short p[30002];
int main()
{
    int w, n;
    scanf("%d%d", &w, &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &p[i]);
    sort(p, p + n);
    int l = 0, r = n - 1;
    int ans = 0;
    while (l <= r)
    {
        if (p[l] + p[r] <= w)
        {
            l++;
            r--;
            ans++;
        }
        else
        {
            r--;
            ans++;
        }
    }
    printf("%d\n", ans);
    return 0;
}