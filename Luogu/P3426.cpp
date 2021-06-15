#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 5e5 + 5;
char s[maxn];
int n, fail[maxn], f[maxn], h[maxn];

int main()
{
    scanf("%s", s + 1);
    n = strlen(s + 1);
    fail[1] = 0;
    for (int i = 2, j = 0; i <= n; ++i)
    {
        while (j && s[j + 1] != s[i]) j = fail[j];
        if (s[j + 1] == s[i]) ++j;
        fail[i] = j;
    }
    f[1] = 1, h[1] = 1;
    FOR(i, 2, n)
    {
        f[i] = i;
        if (h[f[fail[i]]] >= i - fail[i]) f[i] = f[fail[i]];
        h[f[i]] = i;
    }
    printf("%d\n", f[n]);
    return 0;
}