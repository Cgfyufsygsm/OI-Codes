#include <cstdio>
#include <cctype>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

namespace fastIO {
const int maxc = 1 << 23;
char ibuf[maxc], *__p1 = ibuf, *__p2 = ibuf;
il char getchar() {return __p1 == __p2 && (__p2 = (__p1 = ibuf) + fread(ibuf, 1, maxc, stdin), __p1 == __p2) ? EOF : *__p1++;}
template<typename T> void read(T &n) {
    int x = 0; n = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        n = n * 10 + c - '0', c = getchar();
    n = x ? -n : n;
}
void read(char *s) {
    int p = 0;
    char c = getchar();
    while (!isdigit(c) && !isalpha(c)) c = getchar();
    while (isalpha(c) || isdigit(c)) s[p++] = c, c = getchar();
    return;
}
char obuf[maxc], *__pO = obuf;
il void putchar(char c) {*__pO++ = c;}
template<typename T> void print(T x) {
    if (x < 0) putchar('-'), print(-x);
    else {
        if (x > 9) print(x / 10);
        putchar(x % 10 + '0');
    }
    return;
}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

const int maxn = 2e5 + 5;
int n, m;

std::vector<int> e[maxn];

il int max(int a, int b) {return a > b ? a : b;}

int t[maxn << 2];

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

void modify(int i, int j, int k, int x, int val) {
    if (i == j) {
        t[k] = val;
        return;
    }
    if (x <= M) modify(i, M, L, x, val);
    else modify(M + 1, j, R, x, val);
    t[k] = max(t[L], t[R]);
    return;
}

int query(int i, int j, int k, int x, int y) {
    if (x > y) return 0;
    if (x <= i && y >= j) return t[k];
    int ret = 0;
    if (x <= M) ret = max(ret, query(i, M, L, x, y));
    if (y > M) ret = max(ret, query(M + 1, j, R, x, y));
    return ret;
}

int main() {
    read(n), read(m);
    FOR(i, 1, m) {
        int x, y; read(x), read(y);
        e[x].push_back(y);
    }
    FOR(i, 1, n) std::sort(e[i].begin(), e[i].end());
    int ans = 0;
    FOR(a, 1, n) {
        std::vector<std::pair<int, int> > tmp;
        for (auto b : e[a]) {
            int v = query(1, n, 1, 1, b - 1) + 1;
            ans = max(ans, v);
            tmp.push_back(std::make_pair(b, v));
        }
        for (auto x : tmp) modify(1, n, 1, x.first, x.second);
    }
    print(ans);
    return output(), 0;
}