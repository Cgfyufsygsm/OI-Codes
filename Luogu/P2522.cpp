#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 5e4 + 7;

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

int mu[maxn], prime[maxn], tot, vis[maxn];

void getmu()
{
    mu[1] = 1;
    for (int i = 2; i <= maxn - 5; ++i)
    {
        if (!vis[i])
        {
            mu[i] = -1;
            prime[++tot] = i;
        }
        for (int j = 1; j <= tot && i * prime[j] <= maxn - 5; ++j)
        {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0)
            {
                mu[i * prime[j]] = 0;
                break;
            }
            else
                mu[i * prime[j]] = -mu[i];
        }
    }
    FOR(i, 1, maxn - 5)
        mu[i] += mu[i - 1];
    return;
}

inline int min(int a, int b) {return a < b ? a : b;}

int calc(int a, int b, int d)
{
    a /= d, b /= d;
    int top = min(a, b), ans = 0;
    for (int l = 1, r = 0; l <= top && r <= top; l = r + 1)
    {
        r = min(top, min(a / (a / l), b / (b / l)));
        ans += (a / l) * (b / l) * (mu[r] - mu[l - 1]);
    }
    return ans;
}

int main()
{
    getmu();
    int T = read();
    while (T--)
    {
        int a = read(), b = read(), c = read(), d = read(), k = read();
        printf("%d\n", calc(b, d, k) - calc(a - 1, d, k) - calc(b, c - 1, k) + calc(a - 1, c - 1, k));
    }
    return 0;
}