#include <cstdio>
#include <cctype>
#include <cmath>

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
        int x = -1, y = 1;
        int dx = 2021, dy = 2020;
        x *= n, y *= n;
        if (((int)ceil((double)y/(double)dy)) - ((int)floor((double)(-x)/(double)dx)) > 1 || (((double)y/(double)dy) > (double)(-x)/(double)dx) && (y % dy == 0 || x % dx == 0))
            printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}