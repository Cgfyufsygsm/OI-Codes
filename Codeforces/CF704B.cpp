#include <cstdio>
#include <cctype>
#include <queue>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

namespace fastIO
{
    const int maxc = 1e7 + 5;
    char buf[maxc], *p1 = buf, *p2 = buf;
    il char getchar() {return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, maxc, stdin), p1 == p2) ? EOF : *p1++;}
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
}

using namespace fastIO;

const int maxn = 5e3 + 5;
typedef long long ll;

ll x[maxn], a[maxn], b[maxn], c[maxn], d[maxn], n, s, e, ans;

std::priority_queue<ll, std::vector<ll>, std::greater<ll> > heap;

ll calc(int i, int j)
{
    if (i < j) return x[j] - x[i] + d[i] + a[j];
    return x[i] - x[j] + c[i] + b[j];
}

int main()
{
    n = read(), s = read(), e = read();
    FOR(i, 1, n) x[i] = read();
    FOR(i, 1, n) a[i] = read();
    FOR(i, 1, n) b[i] = read();
    FOR(i, 1, n) c[i] = read();
    FOR(i, 1, n) d[i] = read();
    if (s == 1 || e == 1) ans = calc(s, e);
    else ans = calc(s, 1) + calc(1, e);
    FOR(i, 2, n)
    {
        ll A = x[i] + a[i], B = -x[i] + b[i], C = x[i] + c[i], D = -x[i] + d[i];
        if (i == s) heap.push(D - C);
        else if (i == e) heap.push(B - A);
        else
        {
            ans += A + C;
            if (i < s) heap.push(B - A);
            if (i < e) heap.push(D - C);
            ans += heap.top(), heap.pop();
            if (i > s) heap.push(B - A);
            if (i > e) heap.push(D - C);
        }
    }
    printf("%lld\n", ans);
    return 0;
}