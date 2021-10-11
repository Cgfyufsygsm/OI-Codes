#include <cstdio>
#include <cctype>
#include <map>
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

using ll = long long;
using db = double;

const int maxn = 2e5 + 5;
int n, a[maxn];
std::map<int, int> mp;

int main() {
    int T; read(T);
    while (T--) {
        read(n);
        ll sum = 0;
        mp.clear();
        FOR(i, 1, n) read(a[i]), sum += a[i], ++mp[a[i]];
        bool flag = (sum * 2 % n == 0 || sum % n == 0);
        ll ans = 0;
        if (flag) {
            int tmp = sum * 2 / n;
            FOR(i, 1, n) {
                --mp[a[i]];
                ans += mp[tmp - a[i]];
            }
        }
        print(ans, '\n');
    }
    return output(), 0;
}