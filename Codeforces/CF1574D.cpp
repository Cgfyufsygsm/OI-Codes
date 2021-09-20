#include <cstdio>
#include <cctype>
#include <vector>
#include <set>
#include <utility>
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
template<typename T> void print(T x) {
    if (x < 0) putchar('-'), print(-x);
    else {
        if (x > 9) print(x / 10);
        putchar(x % 10 + '0');
    }
    return;
}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

const int maxn = 2e5 + 5;
int n, m, c[12];
using ll = long long;
using node = std::pair<ll, std::vector<int> >;

ll a[12][maxn];
std::set<node> ban, s;

int main() {
    read(n);
    FOR(i, 1, n) {
        read(c[i]);
        FOR(j, 1, c[i])
            read(a[i][j]);
    }
    read(m);
    FOR(i, 1, m) {
        node tmp;
        tmp.first = 0, tmp.second.clear(), tmp.second.resize(n + 1);
        FOR(j, 1, n) {
            read(tmp.second[j]);
            tmp.first += a[j][tmp.second[j]];
        }
        ban.insert(tmp);
    }
    node init;
    init.first = 0, init.second.clear(), init.second.resize(n + 1);
    FOR(i, 1, n) init.first += a[i][c[i]], init.second[i] = c[i];
    s.insert(init);
    while (true) {
        auto now = *std::prev(s.end());
        s.erase(std::prev(s.end()));
        if (!ban.count(now)) {
            FOR(i, 1, n) print(now.second[i]), putchar(' ');
            break;
        }
        FOR(i, 1, n) {
            if (now.second[i] > 1) {
                ll delta = a[i][now.second[i]] - a[i][now.second[i] - 1];
                --now.second[i], now.first -= delta;
                s.insert(now);
                ++now.second[i], now.first += delta;
            }
        }
    }
    return output(), 0;
}