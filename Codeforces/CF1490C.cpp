#include <cstdio>
#include <cctype>
#include <set>
#define int long long
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define YES printf("YES\n")
#define NO printf("NO\n")

inline int read()
{
    char c = getchar();
    int s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

std::set<int> cube;

signed main()
{
    int T = read();
    FOR(i, 1, 10000)
        cube.insert(i * i * i);
    while (T--)
    {
        int x = read();
        bool flag = 0;
        FOR(i, 1, 10000)
            if (cube.count(x - i * i * i))
            {
                flag = 1;
                break;
            }
        if (flag) YES;
        else NO;
    }
    return 0;
}