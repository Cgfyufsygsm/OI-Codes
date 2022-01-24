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

const int maxn = 3e5 + 5;
int n, K, a[maxn], up;
int ch[maxn * 30][2], val[maxn * 30], tot, root;

void insert(int &u, int id, int x, int k) {
    if (!u) u = ++tot;
    if (k < 0) return val[u] = id, void();
    int c = (x >> k) & 1;
    insert(ch[u][c], id, x, k - 1);
    return;
}

vector<int> getval(int u, int k) {
    if (!u) return vector<int>();
    if (k < 0) return vector<int>{val[u]};
    auto r1 = getval(ch[u][0], k - 1), r2 = getval(ch[u][1], k - 1);
    for (auto xx : r2) r1.push_back(xx);
    return r1;
}

int query(int u, int k, int x) {
    if (k < 0) return val[u];
    int c = ((x >> k) & 1) ^ 1;
    if (!ch[u][c]) return query(ch[u][c ^ 1], k - 1, x);
    else return query(ch[u][c], k - 1, x);
}

vector<int> solve(int u, int k) {
    if (k < up || !u) return vector<int>();
    if (k > up) {
        auto r1 = solve(ch[u][0], k - 1), r2 = solve(ch[u][1], k - 1);
        for (auto xx : r2) r1.push_back(xx);
        return r1;
    } else if (k == up) {
        vector<int> vec1 = getval(ch[u][1], k - 1), vec2 = getval(ch[u][0], k - 1), ans;
        if (!vec1.size()) {
            ans.push_back(vec2.back());
            return ans;
        }
        if (!vec2.size()) {
            ans.push_back(vec1.back());
            return ans;
        }
        bool flag = 0;
        for (auto x1 : vec1) {
            int x2 = query(ch[u][0], k - 1, a[x1]);
            if ((a[x1] ^ a[x2]) >= K) {
                flag = 1;
                ans.push_back(x1), ans.push_back(x2);
                break;
            }
        }
        if (!flag) {
            ans.push_back(vec1.back());
        }
        return ans;
    }
}

int main() {
    read(n, K);
    DEC(i, 30, 0) if ((K >> i) & 1) {
        up = i;
        break;
    }
    if (K == 0) {
        print(n);
        FOR(i, 1, n) print(i, ' ');
        return output(), 0;
    }
    FOR(i, 1, n) read(a[i]), insert(root, i, a[i], 30);
    auto ans = solve(root, 30);
    if (ans.size() <= 1) print(-1);
    else {
        print(ans.size());
        for (auto x : ans) print(x, ' ');
    }
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}