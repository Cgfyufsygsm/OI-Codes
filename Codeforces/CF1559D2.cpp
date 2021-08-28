#include <cstdio>
#include <cctype>
#include <set>
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

const int maxn = 1e5 + 5;
int n, m1, m2;
int fa1[maxn], fa2[maxn];
int ans, ansx[maxn], ansy[maxn];

int find(int *fa, int u) {return u == fa[u] ? u : fa[u] = find(fa, fa[u]);}

void merge(int *fa, int u, int v) {
    u = find(fa, u), v = find(fa, v);
    if (u == v) return;
    fa[v] = u;
    return;
}

il bool query(int *fa, int u, int v) {return find(fa, u) == find(fa, v);}

int main() {
    read(n), read(m1), read(m2);
    FOR(i, 1, n) fa1[i] = fa2[i] = i;
    FOR(i, 1, m1) {
        int u, v; read(u), read(v);
        merge(fa1, u, v);
    }
    FOR(i, 1, m2) {
        int u, v; read(u), read(v);
        merge(fa2, u, v);
    }
    FOR(i, 2, n)
        if (!query(fa1, 1, i) && !query(fa2, 1, i))
            ++ans, ansx[ans] = 1, ansy[ans] = i, merge(fa1, 1, i), merge(fa2, 1, i);
    std::set<int> A, B;
    FOR(i, 2, n) {
        bool flag1 = query(fa1, 1, i), flag2 = query(fa2, 1, i);
        if (!flag1) A.insert(find(fa1, i));
        else if (!flag2) B.insert(find(fa2, i));
    }
    for (std::set<int>::iterator i = A.begin(), j = B.begin(); i != A.end() && j != B.end(); ++i, ++j) {
        int u = *i, v = *j;
        merge(fa1, u, v), merge(fa2, u, v);
        ++ans, ansx[ans] = u, ansy[ans] = v;
    }
    print(ans), putchar('\n');
    FOR(i, 1, ans) print(ansx[i]), putchar(' '), print(ansy[i]), putchar('\n');
    return output(), 0;
}