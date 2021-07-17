#include <cstdio>
#include <cctype>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

namespace fastIO {
    const int maxc = 1e7 + 5;
    char buf[maxc], *p1 = buf, *p2 = buf;
    il char getchar() {return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, maxc, stdin), p1 == p2) ? EOF : *p1++;}
    int read() {
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
typedef long long ll;

const int maxm = 1e5 + 5;

int n, m;

il int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}

struct node
{
    ll a, c, g;
    il bool operator<(const node &b) const {return c < b.c;}
} op[maxm];

ll ans = 0;

int main() {
    n = read(), m = read();
    FOR(i, 1, m)
        op[i].a = read(), op[i].c = read();
    std::sort(op + 1, op + m + 1);
    FOR(i, 1, m) {
        int g = gcd(n, op[i].a);
        ans += 1ll * op[i].c * (n - g);
        n = g;
    }
    printf("%lld\n", n == 1 ? ans : -1);
    return 0;
}