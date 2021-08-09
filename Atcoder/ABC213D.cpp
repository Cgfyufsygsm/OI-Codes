#include <cstdio>
#include <cctype>
#include <vector>
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
}

using namespace fastIO;

const int maxn = 2e5 + 5;

std::vector<int> G[maxn];
int n;

il void add(int u, int v) {
    G[u].push_back(v), G[v].push_back(u);
    return;
}

void dfs(int u, int fa) {
    std::sort(G[u].begin(), G[u].end());
    print(u), putchar(' ');
    for (auto v : G[u]) {
        if (v == fa) continue;
        dfs(v, u);
        print(u), putchar(' ');
    }
    return;
}

int main() {
    read(n);
    FOR(i, 1, n - 1) {
        int u, v; read(u), read(v);
        add(u, v);
    }
    dfs(1, 0);
    return output(), 0;
}