#include <iostream>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

typedef unsigned long long ull;

const int maxn = 25, mod = 2520;
int num[maxn];

int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}
int lcm(int a, int b) {return a / gcd(a, b) * b;}

int id[2600], cnt;
ull f[maxn][2600][50];

ull dfs(int pos, int cur, bool lim, int _lcm)
{
    if (!pos) return cur % _lcm == 0;
    if (!lim && ~f[pos][cur][id[_lcm]]) return f[pos][cur][id[_lcm]];
    ull ret = 0;
    FOR(i, 0, 9)
    {
        if (lim && i > num[pos]) break;
        ret += dfs(pos - 1, (cur * 10 + i) % mod, lim && i == num[pos], i ? lcm(_lcm, i) : _lcm);
    }
    if (!lim) f[pos][cur][id[_lcm]] = ret;
    return ret;
}

ull solve(ull n)
{
    int len = 0;
    while (n) num[++len] = n % 10, n /= 10;
    return dfs(len, 0, 1, 1);
}

int main()
{
    memset(f, -1, sizeof f);
    FOR(i, 1, mod)
        if (mod % i == 0)
            id[i] = ++cnt;
    ull l, r, t;
    std::cin >> t;
    while (t--)
    {
        std::cin >> l >> r;
        std::cout << solve(r) - solve(l - 1) << std::endl;
    }
    return 0;
}