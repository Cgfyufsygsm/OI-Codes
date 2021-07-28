#include <cstdio>
#include <cctype>
#include <vector>
#include <set>
#include <unordered_map>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

namespace fastIO {
    const int maxc = 1 << 21;
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
}

using namespace fastIO;

const int maxn = 2005;
int n, a[maxn], b[maxn];

std::unordered_map<int, int> mb, t;
std::set<int> s;

int main() {
    read(n);
    FOR(i, 1, n) read(a[i]);
    FOR(i, 1, n) read(b[i]), mb[b[i]]++;
    FOR(i, 1, n) {
        bool flag = 1;
        t = mb;
        --t[b[i]];
        FOR(j, 2, n) {
            if (!t[a[1] ^ b[i] ^ a[j]]) {
                flag = 0;
                break;
            } else --t[a[1] ^ b[i] ^ a[j]];
        }
        if (flag) s.insert(a[1] ^ b[i]);
    }
    print(s.size()), putchar('\n');
    for (auto x : s) print(x), putchar('\n');
    return output(), 0;
}