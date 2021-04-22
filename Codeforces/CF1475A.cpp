#include <cstdio>
#include <cctype>

typedef long long ll;

inline ll read()
{
    char c = getchar();
    ll s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

int main()
{
    int T = read();
    while (T--)
    {
        ll n = read();
        bool flag = 1;
        for (ll i = 2; i <= n; i <<= 1LL)
            if (i == n)
            {
                flag = 0;
                break;
            }
        if (flag)
            printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}