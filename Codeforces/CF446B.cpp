#include <cstdio>
#include <cctype>
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

typedef long long ll;
const int maxn = 1005, maxk = 1e6 + 5;
int n, m;
int a[maxn][maxn];
ll sumr[maxk], sumc[maxk], k, p;

int main() {
    read(n), read(m), read(k), read(p);
    FOR(i, 1, n) FOR(j, 1, m) read(a[i][j]), sumr[i] += a[i][j], sumc[j] += a[i][j];
    std::priority_queue<ll> qr, qc;
    FOR(i, 1, n) qr.push(sumr[i]);
    FOR(j, 1, m) qc.push(sumc[j]);
    FOR(i, 1, k) {
        ll tmp = qr.top();
        qr.pop();
        sumr[i] = sumr[i - 1] + tmp;
        qr.push(tmp - m * p);
        tmp = qc.top();
        qc.pop();
        sumc[i] = sumc[i - 1] + tmp;
        qc.push(tmp - n * p);
    }
    ll ans = -1e18;
    FOR(i, 0, k) ans = max(ans, sumr[i] + sumc[k - i] - p * i * (k - i));
    print(ans, '\n');
    return output(), 0;
}