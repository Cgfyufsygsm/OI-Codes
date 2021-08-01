#include <cstdio>
#include <cctype>
#include <vector>
#include <utility>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

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
}

using namespace fastIO;
using namespace std;

const int maxn = 5005, mod = 998244353;

int n, m, k;
int b[2][maxn];
vector<pair<int, int> > v;

int main() {
    read(n), read(m), read(k);
    FOR(i, 1, m) {
        int _u, _v; read(_u), read(_v);
        v.push_back(make_pair(_u, _v));
        v.push_back(make_pair(_v, _u));
    }
    FOR(i, 1, n) v.push_back(make_pair(i, i));
    b[0][1] = 1;
    FOR(i, 1, k) {
        int B = 0;
        FOR(j, 1, n) B = (B + b[(i - 1) & 1][j]) % mod;
        FOR(j, 1, n) b[i & 1][j] = B;
        for (auto p : v)//b(1, k) = b(1, j) * a(j, k)
            b[i & 1][p.second] = (b[i & 1][p.second] - b[(i - 1) & 1][p.first] + mod) % mod;
    }
    printf("%d\n", b[k & 1][1]);
    return 0;
}