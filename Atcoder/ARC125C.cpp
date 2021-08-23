#include <cstdio>
#include <cctype>
#include <deque>
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
int n, k;
int a[maxn], vis[maxn];
std::deque<int> v;

int main() {
    read(n), read(k);
    FOR(i, 1, k) read(a[i]), vis[a[i]] = 1;
    FOR(i, 1, n) if (i == a[k] || !vis[i]) v.push_back(i);
    if (n == k) {
        FOR(i, 1, k) print(a[i]), putchar(' ');
        return output(), 0;
    }
    FOR(i, 1, k - 1) {
        print(a[i]), putchar(' ');
        if (!v.empty()) {
            int tmp = v.front();
            if (tmp < a[i] && tmp < a[i + 1]) print(tmp), putchar(' '), v.pop_front();
        }
    }
    while (!v.empty()) print(v.back()), putchar(' '), v.pop_back();
    return output(), 0;
}