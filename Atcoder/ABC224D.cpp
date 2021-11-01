#include <cstdio>
#include <cctype>
#include <map>
#include <queue>
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
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

const int maxn = 35;
int m, powten[15];
std::map<int, int> mp;
std::vector<int> G[10];

void bfs(int st) {
    std::queue<int> q;
    q.push(st);
    mp[st] = 0;
    while (!q.empty()) {
        int now = q.front(); q.pop();
        int tmp = now, u;
        FOR(i, 1, 9) {
            if (!(tmp % 10)) {
                u = i;
                break;
            }
            tmp /= 10;
        }
        for (auto v : G[u]) {
            int to = now;
            int tmp = now / powten[v - 1] % 10;
            to -= tmp * powten[v - 1];
            to += tmp * powten[u - 1];
            if (!mp.count(to)) mp[to] = mp[now] + 1, q.push(to);
        }
    }
}

int main() {
    read(m);
    powten[0] = 1;
    FOR(i, 1, 9) powten[i] = 10 * powten[i - 1];
    FOR(i, 1, m) {
        int u, v; read(u), read(v);
        G[u].push_back(v), G[v].push_back(u);
    }
    int msk = 0;
    FOR(i, 1, 8) {
        int x; read(x);
        msk += powten[x - 1] * i;
    }
    bfs(msk);
    if (mp.count(87654321)) print(mp[87654321], '\n');
    else print(-1, '\n');
    return output(), 0;
}