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

using namespace std;
using namespace fastIO;
using pii = pair<int, int>;

const int maxa = 1e6 + 7, maxn = 1.5e5 + 5, N = 1e6 + 5;
int n, q, a[maxn], buc[maxa], fa[maxn], d[maxn];
int pri[maxa], col[maxa];
vector<pii> vec;

int find(int u) {return fa[u] == u ? u : fa[u] = find(fa[u]);}

int main() {
    read(n), read(q);
    FOR(i, 1, n) read(a[i]), buc[a[i]] = i, fa[i] = i;
    FOR(i, 2, N) {
        if (pri[i]) continue;
        for (int j = i, pre = -1; j <= N; j += i) {
            if (buc[j]) {
                if (pre == -1) col[i] = find(buc[j]);
                else fa[find(pre)] = find(buc[j]);
                pre = buc[j];
            }
            pri[j] = i;
        }
    }
    FOR(i, 2, N) if (pri[i] == i) col[i] = find(col[i]);
    FOR(i, 1, n) {
        int p = a[i] + 1, c = 0;
        d[++c] = find(i);
        while (p > 1) d[++c] = col[pri[p]], p /= pri[p];
        sort(d + 1, d + c + 1), c = unique(d + 1, d + c + 1) - d - 1;
        FOR(i, 1, c)
            FOR(j, i +1, c)
                vec.push_back(pii(d[i], d[j]));
    }
    sort(vec.begin(), vec.end());
    while (q--) {
        int s, t; read(s), read(t);
        s = find(s), t = find(t);
        if (s == t) print(0, '\n');
        else {
            pii p = pii(min(s, t), max(s, t));
            auto it = lower_bound(vec.begin(), vec.end(), p);
            if (*it == p) print(1, '\n');
            else print(2, '\n');
        }
    }
    return output(), 0;
}