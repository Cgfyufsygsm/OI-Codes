#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;

namespace YangTY {
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
    while (isspace(c)) c = getchar();
    while (~c && !isspace(c)) s[p++] = c, c = getchar();
    return;
}
template<typename T1, typename... T2> void read(T1 &a, T2&... x) {
    read(a), read(x...);
    return;
}
char obuf[maxc], *__pO = obuf;
il void putchar(char c) {*__pO++ = c;}
template<typename T> void print(T x, char c = '\n') {
    static char stk[50];
    int top = 0;
    if (x < 0) putchar('-'), x = -x;
    if (x) {
        for (; x; x /= 10) stk[++top] = x % 10 + '0';
        while (top) putchar(stk[top--]);
    } else putchar('0');
    putchar(c);
    return;
}
void print(char *s, char c = '\n') {
    for (int i = 0; s[i]; ++i) putchar(s[i]);
    putchar(c);
    return;
}
void print(const char *s, char c = '\n') {
    for (int i = 0; s[i]; ++i) putchar(s[i]);
    putchar(c);
    return;
}
template<typename T1, typename... T2> il void print(T1 a, T2... x) {
    if (!sizeof...(x)) print(a);
    else print(a, ' '), print(x...);
    return;
}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}
template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T, typename...Args> il T max(const T &a, const Args&... args) {
    T res = max(args...);
    return max(a, res);
}
template<typename T, typename...Args> il T min(const T &a, const Args&... args) {
    T res = min(args...);
    return min(a, res);
}
template<typename T> il T chkmax(T &a, const T &b) {return a = max(a, b);}
template<typename T> il T chkmin(T &a, const T &b) {return a = min(a, b);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

using uint = unsigned;
const int LG = 31;
const int maxn = 5e5 + 5;
uint s[maxn];
int n, K;

struct node {
    int ch[2], latest;
    node() {ch[0] = ch[1] = 0, latest = -1;}
} t[maxn * 60];
int tot, root[maxn];

int clone(int u) {
    t[++tot] = t[u];
    return tot;
}

int insert(int u, uint val, int k, int id) {
    u = clone(u);
    if (k < 0) return t[u].latest = id, u;
    int c = (val >> (uint)k) & 1;
    t[u].ch[c] = insert(t[u].ch[c], val, k - 1, id);
    t[u].latest = max(t[t[u].ch[0]].latest, t[t[u].ch[1]].latest);
    return u;
}

int query(int u, int l, uint val, int k) {
    if (k < 0) return t[u].latest;
    int c = (val >> (uint)k) & 1;
    return query(t[u].ch[c ^ (t[t[u].ch[c ^ 1]].latest >= l)], l, val, k - 1);
}

struct node2 {
    uint val;
    int l, r, pos1, pos2;
    node2(uint v, int _l, int _r, int p1, int p2) : val(v), l(_l), r(_r), pos1(p1), pos2(p2) {}
};

il bool operator<(const node2 &a, const node2 &b) {return a.val < b.val;}

int main() {
    read(n, K);
    FOR(i, 1, n) read(s[i]), s[i] ^= s[i - 1];
    FOR(i, 0, n) root[i] = insert(i ? root[i - 1] : 0, s[i], LG, i);
    priority_queue<node2> q;
    FOR(i, 1, n) {
        int j = query(root[i], 0, s[i], LG);
        q.push(node2(s[i] ^ s[j], 0, i - 1, j, i));
    }
    long long ans = 0;
    FOR(iii, 1, K) {
        node2 now = q.top(); q.pop();
        ans += now.val;
        int p = now.pos1, i = now.pos2;
        if (p != now.r) {
            int j = query(root[now.r], p + 1, s[i], LG);
            q.push(node2(s[i] ^ s[j], p + 1, now.r, j, i));
        }
        if (p != now.l) {
            int j = query(root[p - 1], now.l, s[i], LG);
            q.push(node2(s[i] ^ s[j], now.l, p - 1, j, i));
        }
    }
    print(ans);
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}