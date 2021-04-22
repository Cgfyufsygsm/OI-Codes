#include <cstdio>
#include <cstring>
#define YES puts("YES")
#define NO puts("NO")

const int maxn = 105;
char s[maxn];
int n, k;

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d %d", &n, &k);
        scanf("%s", s + 1);
        if (k == 0)
        {
            YES;
            continue;
        }
        int cnt = 0;
        for (int i = 1, j = n; i <= (n - 0.1) / 2; ++i, --j)
        {
            if (s[i] == s[j])
                ++cnt;
            else break;
        }
        if (cnt >= k)
            YES;
        else NO;
    }
    return 0;
}