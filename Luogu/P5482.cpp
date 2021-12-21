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
    while (!isspace(c)) s[p++] = c, c = getchar();
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

using db = double;
const int maxn = 1e5 + 5;

struct tree {
    struct node {
        int val, key;
        int ch[2], size;
    } t[maxn];
    int cnt, root;

#define ls(k) t[k].ch[0]
#define rs(k) t[k].ch[1]

    int newnode(int val) {
        t[++cnt].val = val, t[cnt].key = rand();
        t[cnt].size = 1, ls(cnt) = rs(cnt) = 0;
        return cnt;
    }

    void pushup(int u) {
        t[u].size = 1 + t[ls(u)].size + t[rs(u)].size;
        return;
    }

    void split(int u, int v, int &x, int &y) {
        if (!u) return x = y = 0, void();
        if (t[u].val <= v)
            x = u, split(rs(u), v, rs(u), y);
        else y = u, split(ls(u), v, x, ls(u));
        return pushup(u), void();
    }

    int merge(int x, int y) {
        if (!x || !y) return x + y;
        if (t[x].key < t[y].key)
            return t[x].ch[1] = merge(t[x].ch[1], y), pushup(x), x;
        else return t[y].ch[0] = merge(x, t[y].ch[0]), pushup(y), y;
    }

    void insert(int val) {
        int k = newnode(val), x, y;
        split(root, val, x, y);
        root = merge(x, merge(k, y));
        return;
    }

    void del(int val) {
        int x, y, z;
        split(root, val - 1, x, y);
        split(y, val, y, z);
        y = merge(ls(y), rs(y));
        root = merge(x, merge(y, z));
        return;
    }

    int rank1(int u, int val) {
        if (!u) return 0;
        if (t[u].val == val) return t[ls(u)].size + 1;
        else if (t[u].val < val) return t[ls(u)].size + 1 + rank1(rs(u), val);
        else return rank1(ls(u), val);
    }

    int rank2(int u, int val) {
        if (!u) return 0;
        if (t[u].val == val) return t[rs(u)].size + 1;
        else if (t[u].val > val) return t[rs(u)].size + 1 + rank2(ls(u), val);
        else return rank2(rs(u), val);
    }

    int rank(int val, bool op) {
        if (!op) return rank1(root, val);
        else return rank2(root, val);
    }

#undef ls
#undef rs
} t1, t2;

int n, del[maxn], type[maxn], val[maxn], tmp, cnt;

int main() {
    read(n);
    while (n--) {
        char s[10];
        read(s);
        if (s[0] == 'A') {
            ++cnt;
            int a, b, c; read(a, b, c);
            if (!a) {
                val[cnt] = (b > c), type[cnt] = 0;
                tmp += (b > c);
            } else {
                if (a > 0) {
                    val[cnt] = (int)floor(1.0 * (c - b) / a) + 1;
                    type[cnt] = 1;
                    t1.insert(val[cnt]);
                } else {
                    val[cnt] = (int)ceil(1.0 * (c - b) / a) - 1;
                    type[cnt] = -1;
                    t2.insert(val[cnt]);
                }
            }
        } else if (s[0] == 'D') {
            int i; read(i);
            if (del[i]) continue;
            del[i] = 1;
            if (!type[i]) tmp -= val[i];
            else if (type[i] > 0) t1.del(val[i]);
            else t2.del(val[i]);
        } else if (s[0] == 'Q') {
            int x; read(x);
            print(tmp + t1.rank(x, 0) + t2.rank(x, 1));
        }
    }
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}