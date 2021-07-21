#include <cstdio>
#include <cctype>
#include <cmath>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

namespace fastIO {
    const int maxc = 1e7 + 5;
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

typedef long long ll;

il ll gcd(ll a, ll b) {return !b ? a : gcd(b, a % b);}

const int maxn = 50000 + 5;
int n, m, c[maxn], block, cnt[maxn];
ll nowAns;

struct node {
    int l, r, id;
    il bool operator<(const node &b) const {return (l / block) ^ (b.l / block) ? l < b.l : (((l / block) & 1) ? r < b.r : r > b.r);}
} q[maxn];

struct ans {
    ll nume, deno;
    void out() {
        if (!nume) deno = 1;
        else {
            int g = gcd(nume, deno);
            nume /= g, deno /= g;
        }
        print(nume), putchar('/'), print(deno), putchar('\n');
        return;
    }
} A[maxn];

il void add(int x) {nowAns += cnt[c[x]]++;}

il void del(int x) {nowAns -= --cnt[c[x]];}

int main() {
    read(n), read(m);
    block = ceil(sqrt(n));
    FOR(i, 1, n) read(c[i]);
    FOR(i, 1, m) {
        read(q[i].l), read(q[i].r), q[i].id = i;
    }
    std::sort(q + 1, q + m + 1);
    int l = 1, r = 0;
    FOR(i, 1, m) {
        if (q[i].l == q[i].r) {
            A[q[i].id].nume = 0;
            continue;
        }
        while (l > q[i].l) add(--l);
        while (r < q[i].r) add(++r);
        while (l < q[i].l) del(l++);
        while (r > q[i].r) del(r--);

        A[q[i].id].nume = nowAns, A[q[i].id].deno = 1ll * (r - l + 1) * (r - l) / 2;
    }
    FOR(i, 1, m) A[i].out();
    return output(), 0;
}