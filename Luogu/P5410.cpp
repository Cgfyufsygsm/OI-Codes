#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 2e7 + 5;
int z[maxn], p[maxn];
char s[maxn], t[maxn];

inline int min(int a, int b) {return a < b ? a : b;}

void get_z(char *s, int n)
{
    z[1] = n;
    for (int i = 2, l = 0, r = 0; i <= n; ++i)
    {
        if (i <= r) z[i] = min(z[i - l + 1], r - i + 1);
        while (i + z[i] <= n && s[i + z[i]] == s[1 + z[i]]) ++z[i];
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return;
}

void exkmp(char *s, int n, char *t, int m)
{
    get_z(t, m);
    for (int i = 1, l = 0, r = 0; i <= n; ++i)
    {
        if (i <= r) p[i] = min(z[i - l + 1], r - i + 1);
        while (i + p[i] <= n && s[i + p[i]] == t[1 + p[i]]) ++p[i];
        if (i + p[i] - 1 > r) l = i, r = i + p[i] - 1;
    }
    return;
}

int main()
{
    scanf("%s", s + 1);
    scanf("%s", t + 1);
    int n = strlen(s + 1), m = strlen(t + 1);
    exkmp(s, n, t, m);
    long long ans = 0;
    FOR(i, 1, m)
        ans ^= ((z[i] + 1ll) * i);
    printf("%lld\n", ans);
    ans = 0;
    FOR(i, 1, n)
        ans ^= ((p[i] + 1ll) * i);
    printf("%lld\n", ans);
    return 0;
}