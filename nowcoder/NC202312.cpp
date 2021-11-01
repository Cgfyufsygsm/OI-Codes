#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
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
template<typename T> void print(const T &x) {
    if (x < 0) putchar('-'), print(-x);
    else {
        if (x > 9) print(x / 10);
        putchar(x % 10 + '0');
    }
    return;
}
template<typename T> il void print(const T &x, const char &c) {print(x), putchar(c);}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}
template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T> il T chkmax(T &a, const T &b) {return a = max(a, b);}
template<typename T> il T chkmin(T &a, const T &b) {return a = min(a, b);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

using ll = long long;
const int maxn = 1e5 + 5;
int head[maxn], to[maxn << 1], nxt[maxn << 1], cnte;
int n, k;
ll val[maxn], sum[maxn];
std::vector<ll> vec;

il void add(int u, int v) {
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

int cnt, flag;

void dfs(int u, int fa, ll mid) {
    sum[u] = val[u];
    if (sum[u] > mid || flag) return flag = true, void();
    for (int i = head[u]; i; i = nxt[i]) {
        int &v = to[i];
        if (v == fa) continue;
        dfs(v, u, mid);
        sum[u] += sum[v];
    }
    if (sum[u] > mid) {
        vec.clear();
        for (int i = head[u]; i; i = nxt[i]) if (to[i] != fa) vec.push_back(sum[to[i]]);
        std::sort(vec.begin(), vec.end());
        while (sum[u] > mid) ++cnt, sum[u] -= vec.back(), vec.pop_back();
    }
    return flag |= (cnt >= k), void();
}

bool check(ll mid) {
    cnt = flag = 0;
    dfs(1, 0, mid);
    return flag ^ 1;
}

int main() {
    int T; read(T);
    FOR(kase, 1, T) {
        read(n), read(k);
        cnte = 0, memset(head, 0, sizeof head);
        FOR(i, 1, n - 1) {
            int u, v; read(u), read(v);
            add(u, v), add(v, u);
        }
        FOR(i, 1, n) read(val[i]);
        ll l = 1, r = 1e16, ans;
        while (l < r) {
            ll mid = (l + r) >> 1;
            if (check(mid)) ans = mid, r = mid;
            else l = mid + 1;
        }
        printf("Case #%d: %lld\n", kase, ans);
    }
    return output(), 0;
}