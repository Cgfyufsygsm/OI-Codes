#include <bits/stdc++.h>
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
using namespace std;

template<typename T> il T chkmax(T &a, const T &b) {return a = max(a, b);}
template<typename T> il T chkmin(T &a, const T &b) {return a = min(a, b);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}


const int maxn = 3e5 + 5;
int a[maxn], b[maxn], n, vis[maxn], pre[maxn], add[maxn];
set<int> S;
vector<int> ans;
queue<int> q;

int main() {
    read(n);
    FOR(i, 1, n) read(a[i]);
    FOR(i, 1, n) read(b[i]);

    FOR(i, 1, n) S.insert(i - 1), vis[i - 1] = -1;
    q.push(n), vis[n] = 0;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        auto r = S.upper_bound(u), l = S.lower_bound(u - a[u]);
        for (auto it = l; it != r; ++it) {
            int v = *it;
            if (vis[v + b[v]] == -1) vis[v + b[v]] = vis[u] + 1, pre[v + b[v]] = u, add[v + b[v]] = b[v], q.push(v + b[v]);
        }
        S.erase(l, r);
    }

    if (~vis[0]) {
        print(vis[0], '\n');
        int now = 0;
        while (now != n) {
            ans.push_back(now);
            now = pre[now];
        }
        reverse(ans.begin(), ans.end());
        for (auto u : ans) print(u - add[u], ' ');
    } else print(-1, '\n');
    return output(), 0;
}