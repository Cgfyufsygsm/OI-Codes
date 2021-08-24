#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define VEC(i, v) for (int i = 0; i < (int)v.size(); ++i)

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
int n;

il int max(int a, int b) {return a > b ? a : b;}

struct cave {
    int need, size;
    il bool operator<(const cave &b) {return need < b.need;}
} a[maxn];

bool check(int now) {
    FOR(i, 1, n) {
        if (now < a[i].need) return false;
        now += a[i].size;
    }
    return true;
}

int main() {
    int T; read(T);
    while (T--) {
        read(n);
        FOR(i, 1, n) {
            int tmp; read(a[i].size);
            a[i].need = 0;
            FOR(j, 1, a[i].size) read(tmp), a[i].need = max(a[i].need, tmp - j + 2);
        }
        std::sort(a + 1, a + n + 1);
        int l = 0, r = 1e9 + 100, ret = 1e9;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (check(mid)) ret = mid, r = mid;
            else l = mid;
        }
        print(ret), putchar('\n');
    }
    return output(), 0;
}