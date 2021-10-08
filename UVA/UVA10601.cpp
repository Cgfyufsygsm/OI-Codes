#include <cstdio>
#include <cctype>
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

typedef long long ll;
const ll fac[13] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600};

int buc[7];

ll calc(int x, int sz) {
    ll res = fac[sz / x];
    FOR(i, 1, 6) {
        if (!(buc[i] % x)) res /= fac[buc[i] / x];
        else return 0;
    }
    return res;
}

int main() {
    int T; read(T);
    while (T--) {
        FOR(i, 1, 6) buc[i] = 0;
        FOR(i, 1, 12) {
            int tmp; read(tmp);
            ++buc[tmp];
        }
        ll ans = calc(1, 12) + 6 * calc(4, 12) + 3 * calc(2, 12) + 8 * calc(3, 12);
        FOR(i, 1, 6) {
            if (!buc[i]) continue;
            --buc[i];
            FOR(j, 1, 6) {
                if (!buc[j]) continue;
                --buc[j];
                ans += 6 * calc(2, 10);
                ++buc[j];
            }
            ++buc[i];
        }
        print(ans / 24, '\n');
    }
    return output(), 0;
}