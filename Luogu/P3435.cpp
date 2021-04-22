#include <cstdio>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 1e6 + 5;
char s[maxn];
int n, fail[maxn], go[maxn];

long long ans = 0;

int main()
{
    scanf("%d", &n);
    scanf("%s", s + 1);
    fail[1] = 0;
    for (int i = 2, j = 0; i <= n; ++i)
    {
        while (j && s[j + 1] != s[i])
            j = fail[j];
        if (s[j + 1] == s[i])
            ++j;
        fail[i] = j;
    }
    go[1] = 1;
    for (int i = 1; i <= n; ++i)
    {
        if (!fail[i]) go[i] = i;
        else go[i] = go[fail[i]];
        ans += i - go[i];
    }
    printf("%lld\n", ans);
    return 0;
}