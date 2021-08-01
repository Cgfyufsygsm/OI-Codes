#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

namespace fastIO {
    const int maxc = 1 << 21;
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
using namespace std;

const int maxn = 1e5 + 5;

int n, m, q;

struct node {
    int from, to, s, t, id;
    node() {}
    node(int a, int b, int c, int d, int e) : from(a), to(b), s(c), t(d), id(e) {}
    il bool operator<(const node &b) const {return s < b.s;}
} bus[maxn];

il bool cmp(const node &a, const int &t) {return t > a.s;}

vector<node> busv[maxn];
vector<int> G[maxn];
int ind[maxn], fa[maxn][22];

void dfs(int u, int f) {
    fa[u][0] = f;
    FOR(i, 1, 20) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (auto v : G[u]) dfs(v, u);
    return;
}

int main() {
    read(n), read(m), read(q);
    FOR(i, 1, m) {
        int a, b, s, t;
        read(a), read(b), read(s), read(t);
        busv[a].push_back(bus[i] = node(a, b, s, t, i));
    }
    FOR(i, 1, n) 
        sort(busv[i].begin(), busv[i].end());
    FOR(u, 1, n) {
        for (auto now : busv[u]) {
            auto to = lower_bound(busv[now.to].begin(), busv[now.to].end(), now.t, cmp);
            if (to == busv[now.to].end()) continue;
            G[to->id].push_back(now.id);
            ++ind[now.id];
        }
    }

    FOR(u, 1, m) if (!ind[u]) dfs(u, 0);

    while (q--) {
        int s, u, t; read(s), read(u), read(t);
        auto p = lower_bound(busv[u].begin(), busv[u].end(), s, cmp);
        if (p == busv[u].end()) {
            print(u), putchar('\n');
            continue;
        }
        auto S = *p;
        if (S.s >= t) {
            print(u), putchar('\n');
            continue;
        }
        DEC(j, 20, 0) {
            if (!fa[S.id][j]) continue;
            if (bus[fa[S.id][j]].s < t) S = bus[fa[S.id][j]];
        }
        if (S.t >= t)
            print(S.from), putchar(' '), print(S.to), putchar('\n');
        else print(S.to), putchar('\n');
    }

    return output(), 0;
}