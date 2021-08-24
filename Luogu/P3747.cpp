#include <cstdio>
#include <cctype>
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

const int maxn = 5e4 + 5, maxp = 1e4 + 5;
int n, m, mod, c, a[maxn];

struct node {
    int sum;
    int tag;
    node() {sum = 0, tag = 1e9;}
} t[maxn << 2];

il int min(int a, int b) {return a < b ? a : b;}

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

il void pushup(int k) {
    t[k].sum = (t[L].sum + t[R].sum) % mod;
    t[k].tag = min(t[L].tag, t[R].tag);
    return;
}

void build(int i, int j, int k) {
    if (i == j) {
        read(a[i]), t[k].sum = a[i];
        t[k].tag = 0;
        return;
    }
    build(i, M, L);
    build(M + 1, j, R);
    pushup(k);
    return;
}

const int logmod = 105, sqrtmod = 1e4 + 5;

int phi[maxn], cntphi;
int pow1[logmod][sqrtmod], pow2[logmod][sqrtmod], sz;
bool flag1[logmod][sqrtmod], flag2[logmod][sqrtmod];

int getPhi(int x) {
    int res = x;
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            res = res / i * (i - 1);
            while (x % i == 0) x /= i;
        }
    }
    if (x > 1) res = res / x * (x - 1);
    return res;
}

void initPhi() {
    phi[cntphi = 0] = mod;
    while (phi[cntphi] != 1)
        phi[cntphi + 1] = getPhi(phi[cntphi]), ++cntphi;
    phi[++cntphi] = 1;
    return;
}

void initPow() {
    sz = 10000;
    FOR(i, 0, cntphi) {
        pow1[i][0] = 1;
        FOR(j, 1, sz) {
            long long tmp = 1ll * c * pow1[i][j - 1];
            if (tmp >= phi[i]) flag1[i][j] = 1, pow1[i][j] = tmp % phi[i];
            else flag1[i][j] = flag1[i][j - 1], pow1[i][j] = tmp;
        }
        pow2[i][0] = 1;
        flag2[i][1] = flag1[i][sz];
        FOR(j, 1, sz) {
            long long tmp = 1ll * pow1[i][sz] * pow2[i][j - 1];
            if (tmp >= phi[i]) flag2[i][j] = 1, pow2[i][j] = tmp % phi[i];
            else flag2[i][j] = flag2[i][j - 1], pow2[i][j] = tmp;
        }
    }
    return;
}

bool flag;

int getPow(int idx, int modid) {
    flag = flag1[modid][idx % sz] || flag2[modid][idx / sz];
    long long tmp = 1ll * pow1[modid][idx % sz] * pow2[modid][idx / sz];
    if (tmp >= phi[modid]) flag = true;
    return tmp % phi[modid];
}

int dfs(int res, int p, int now) {
    flag = 0;
    if (p == now) {
        if (res >= phi[now]) flag = 1, res %= phi[now];
        return res;
    }
    int tmp = dfs(res, p, now + 1);
    return getPow(flag ? tmp + phi[now + 1] : tmp, now);
}

void modify(int i, int j, int k, int x, int y) {
    if (t[k].tag >= cntphi) return;
    if (i == j) {
        t[k].sum = dfs(a[i], ++t[k].tag, 0);
        return;
    }
    if (x <= M) modify(i, M, L, x, y);
    if (y > M) modify(M + 1, j, R, x, y);
    pushup(k);
    return;
}

int query(int i, int j, int k, int x, int y) {
    if (x <= i && y >= j) return t[k].sum;
    int ret = 0;
    if (x <= M) ret += query(i, M, L, x, y);
    if (y > M) ret = (ret + query(M + 1, j, R, x, y)) % mod;
    return ret;
}

int main() {
    read(n), read(m), read(mod), read(c);
    initPhi();
    initPow();
    build(1, n, 1);
    while (m--) {
        int op, l, r;
        read(op), read(l), read(r);
        if (!op) modify(1, n, 1, l, r);
        else print(query(1, n, 1, l, r)), putchar('\n');
    }
    return output(), 0;
}
