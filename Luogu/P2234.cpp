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
    while (!isdigit(c) && !isalpha(c)) c = getchar();
    while (isalpha(c) || isdigit(c)) s[p++] = c, c = getchar();
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

const int maxn = 1 << 15 | 500;

struct node {
    int size, ch[2], val, key;
} t[maxn];

#define ls(k) t[k].ch[0]
#define rs(k) t[k].ch[1]

int a[maxn], root, n, cnt;

int newnode(int val) {
    t[++cnt].size = 1;
    t[cnt].key = rand();
    t[cnt].val = val;
    ls(cnt) = rs(cnt) = 0;
    return cnt;
}

il void pushup(int k) {
    t[k].size = t[ls(k)].size + t[rs(k)].size + 1;
    return;
}

void split(int val, int k, int &x, int &y) {
    if (!k) return x = y = 0, void();
    if (t[k].val <= val) {
        x = k;
        split(val, rs(k), rs(k), y);
    } else {
        y = k;
        split(val, ls(k), x, ls(k));
    }
    return pushup(k), void();
}

int merge(int k1, int k2) {
    if (!k1 || !k2) return k1 | k2;
    if (t[k1].key < t[k2].key)
        return rs(k1) = merge(rs(k1), k2), pushup(k1), k1;
    else return ls(k2) = merge(k1, ls(k2)), pushup(k2), k2;
}

void insert(int val) {
    int x, y = newnode(val), z;
    split(val, root, x, z);
    root = merge(merge(x, y), z);
    return;
}

int kth(int k, int rnk) {
    if (rnk <= t[ls(k)].size) return kth(ls(k), rnk);
    else if (rnk == t[ls(k)].size + 1) return k;
    else return kth(rs(k), rnk - t[ls(k)].size - 1);
}

int pre(int val) {
    int x, y;
    split(val, root, x, y);
    int u = kth(x, t[x].size);
    root = merge(x, y);
    return t[u].val;
}

int suc(int val) {
    int x, y;
    split(val - 1, root, x, y);
    int u = kth(y, 1);
    root = merge(x, y);
    return t[u].val;
}

int main() {
    srand(20041031);
    read(n);
    FOR(i, 1, n) read(a[i]);
    int ans = a[1];
    insert(-2e9), insert(2e9), insert(a[1]);
    FOR(i, 2, n) {
        ans += min(a[i] - pre(a[i]), suc(a[i]) - a[i]);
        insert(a[i]);
    }
    print(ans);
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}