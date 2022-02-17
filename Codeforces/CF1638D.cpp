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
template<typename T> il T chkmax(T &a, const T &b) {return a = (b > a ? b : a);}
template<typename T> il T chkmin(T &a, const T &b) {return a = (b < a ? b : a);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

using pii = pair<int, int>;
const int maxn = 1e3 + 5;
int a[maxn][maxn], n, m, vis[maxn][maxn];

struct node {
    int x, y, c;
    node(int _x = 0, int _y = 0, int _c = 0) : x(_x), y(_y), c(_c) {}
};
vector<node> ans;

const int fx[] = {1, 1, 1, 0, 0, -1, -1, -1};
const int fy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

bool check(int x, int y) {return x > 0 && x < n && y > 0 && y < m;}

int main() {
    read(n, m);
    FOR(i, 1, n) FOR(j, 1, m) read(a[i][j]);
    queue<pii> q;
    FOR(i, 1, n - 1) FOR(j, 1, m - 1) {
        if (a[i][j] == a[i + 1][j + 1] && a[i][j] == a[i + 1][j] && a[i][j] == a[i][j + 1]) {
            ans.push_back(node(i, j, a[i][j]));
            q.push({i, j});
            FOR(x, i, i + 1) FOR(y, j, j + 1) vis[x][y] = 1;
            break;
        }
    }
    while(!q.empty())
    {
        pii now = q.front(); q.pop();
        FOR(k, 0, 7) {
            int x = now.first + fx[k], y = now.second + fy[k];
            if (!check(x, y)) continue;
            int col = 0, flag = 1;
            FOR(tx, x, x + 1) {
                FOR(ty, y, y + 1) {
                    if (vis[tx][ty]) continue;
                    if (!col) col = a[tx][ty];
                    if (col != a[tx][ty]) {
                        flag = 0;
                        goto out;
                    }
                }
            }
            out:
            if (!flag || !col) continue;
            FOR(tx, x, x + 1) FOR(ty, y, y + 1) vis[tx][ty] = 1;
            q.push({x, y}), ans.push_back(node(x, y, col));
        }
    }
    bool flg = 1;
    FOR(i, 1, n) FOR(j, 1, m) flg &= vis[i][j];
    if (!flg) print(-1);
    else {
        print(ans.size());
        reverse(ans.begin(), ans.end());
        for (auto &p : ans)
            print(p.x, p.y, p.c);
    }
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}