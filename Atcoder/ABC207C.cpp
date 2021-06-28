#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

int read()
{
    int s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
    return x ? -s : s;
}

inline void swap(int &i, int &j)
{
    int t = i;
    i = j, j = t;
}

const int maxn = 2005;
int n;
int t[maxn], l[maxn], r[maxn];

bool check(int i, int j)
{
    if (r[i] > r[j]) swap(i, j);
    int t1 = t[i], t2 = t[j], l1 = l[i], r1 = r[i], l2 = l[j], r2 = r[j];
    if (t1 == 2 || t1 == 4)
        return r1 > l2;
    else
        return r1 > l2 || (r1 == l2 && (t2 == 1 || t2 == 2));
}

int main()
{
    n = read();
    FOR(i, 1, n)
        t[i] = read(), l[i] = read(), r[i] = read();
    int ans = 0;
    FOR(i, 1, n)
        FOR(j, i + 1, n)
            ans += check(i, j);
    printf("%d\n", ans);
    return 0;
}