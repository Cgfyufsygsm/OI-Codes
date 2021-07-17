#include <cstdio>
#include <cctype>
#include <map>
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

il int max(int a, int b) {return a > b ? a : b;}

const int maxn = 3e5 + 5;

int c[maxn], k, n;

std::map<int, int> m;

int main() {
    n = read(), k = read();
    int ans = 0;
    FOR(i, 1, n) c[i] = read();
    FOR(i, 1, n) {
        ++m[c[i]];
        if (i - k > 0) --m[c[i - k]];
        if (i - k > 0 && !m[c[i - k]]) m.erase(c[i - k]);
        ans = max(ans, m.size());
    }
    printf("%d\n", ans);
    return 0;
}