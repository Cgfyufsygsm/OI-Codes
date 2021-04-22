#include <cstdio>
#include <cctype>
#include <map>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define it std::map<int, long long>::iterator

inline int read()
{
    char c = getchar();
    int s = 0;
    bool x = 0;
    while (!isdigit(c))
        x = x | (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

const int maxn = 2e5 + 5;
std::map<int, long long> m;

int n, c;

int main()
{
    n = read(), c = read();
    FOR(i, 1, n)
        ++m[read()];
    long long ans = 0;
    for (it a = m.begin(), b = m.begin(); b != m.end(); ++a)
    {
        while (b != m.end() && (*b).first - (*a).first < c) ++b;
        if ((*b).first - (*a).first == c)
            ans += (*a).second * (*b).second;
    }
    printf("%lld\n", ans);
    return 0;
}