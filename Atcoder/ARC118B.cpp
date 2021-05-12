#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define int long long

const int maxn = 1e5 + 5;

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

int k, a[maxn], n, m;
int L[maxn], R[maxn], suml, sumr;

inline int max(int a, int b) {return a > b ? a : b;}
inline int min(int a, int b) {return a < b ? a : b;}

bool check(int x)
{
    memset(L, 0, sizeof L), memset(R, 0, sizeof R);
    suml = sumr = 0;
    FOR(i, 1, k)
    {
        L[i] = max(0, (m * a[i] - x + n - 1) / n);
        R[i] = (m * a[i] + x) / n;
        suml += L[i], sumr += R[i];
    }
    return suml <= m && m <= sumr;
}

signed main()
{
    k = read(), n = read(), m = read();
    FOR(i, 1, k) a[i] = read();
    int l = 0, r = n * m, x;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid)) x = mid, r = mid - 1;
        else l = mid + 1;
    }
    check(x);
    int sumb = suml;
    FOR(i, 1, k)
    {
        int x = min(R[i] - L[i], m - sumb);
        sumb += x;
        printf("%d ", x + L[i]);
    }
    return 0;
}