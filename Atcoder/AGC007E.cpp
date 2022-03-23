#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;

namespace YangTY {
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
    while (isspace(c)) c = getchar();
    while (~c && !isspace(c)) s[p++] = c, c = getchar();
    return;
}
template<typename T1, typename... T2> void read(T1 &a, T2&... x) {
    read(a), read(x...);
    return;
}
char obuf[maxc], *__pO = obuf;
il void putchar(char c) {*__pO++ = c;}
template<typename T> void print(T x, char c = '\n') {
    static char stk[50];
    int top = 0;
    if (x < 0) putchar('-'), x = -x;
    if (x) {
        for (; x; x /= 10) stk[++top] = x % 10 + '0';
        while (top) putchar(stk[top--]);
    } else putchar('0');
    putchar(c);
    return;
}
void print(char *s, char c = '\n') {
    for (int i = 0; s[i]; ++i) putchar(s[i]);
    putchar(c);
    return;
}
void print(const char *s, char c = '\n') {
    for (int i = 0; s[i]; ++i) putchar(s[i]);
    putchar(c);
    return;
}
template<typename T1, typename... T2> il void print(T1 a, T2... x) {
    if (!sizeof...(x)) print(a);
    else print(a, ' '), print(x...);
    return;
}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}
template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T, typename...Args> il T max(const T &a, const Args&... args) {
    T res = max(args...);
    return max(a, res);
}
template<typename T, typename...Args> il T min(const T &a, const Args&... args) {
    T res = min(args...);
    return min(a, res);
}
template<typename T> il T chkmax(T &a, const T &b) {return a = (b > a ? b : a);}
template<typename T> il T chkmin(T &a, const T &b) {return a = (b < a ? b : a);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

using ll = long long;
const int maxn = (1 << 17) | 500;
int fa[maxn], ch[maxn][2], len[maxn][2], n;

using pll = pair<ll, ll>;
vector<pll> S[maxn], Sl[maxn], Sr[maxn];

#define fi first
#define se second

bool check(ll mid) {
    DEC(u, n, 1) {
        S[u].clear(), Sl[u].clear(), Sr[u].clear();
        if (!ch[u][0]) {
            S[u].emplace_back(pll(0ll, 0ll));
            continue;
        }
        ll w = mid - len[u][0] - len[u][1];
        vector<pll> &L = S[ch[u][0]], &R = S[ch[u][1]], &lres = Sl[u], &rres = Sr[u], &res = S[u];
        if (L.empty() || R.empty()) return false;
        
        for (auto itL = L.begin(), itR = R.begin(); itL != L.end(); ++itL) {
            while (next(itR) != R.end() && next(itR)->fi + itL->se <= w) ++itR;
            if (itR->fi + itL->se > w) continue;
            lres.emplace_back(pll(itL->fi + len[u][0], itR->se + len[u][1]));
        }
        for (auto itL = L.begin(), itR = R.begin(); itR != R.end(); ++itR) {
            while (next(itL) != L.end() && next(itL)->fi + itR->se <= w) ++itL;
            if (itL->fi + itR->se > w) continue;
            rres.emplace_back(pll(itR->fi + len[u][1], itL->se + len[u][0]));
        }
        for (auto itL = lres.begin(), itR = rres.begin(); itL != lres.end() || itR != rres.end();) {
            if (itR == rres.end() || (itL != lres.end() && itL->fi <= itR->fi)) {
                while (!res.empty() && res.back().fi == itL->fi && res.back().se >= itL->se) res.pop_back();
                if (res.empty() || res.back().se > itL->se) res.emplace_back(*itL);
                ++itL;
            } else {
                while (!res.empty() && res.back().fi == itR->fi && res.back().se >= itR->se) res.pop_back();
                if (res.empty() || res.back().se > itR->se) res.emplace_back(*itR);
                ++itR;
            }
        }
    }
    return !S[1].empty();
}

int main() {
    read(n);
    if (n == 1) {
        print(0);
        return output(), 0;
    }
    FOR(i, 2, n) {
        int p, l; read(p, l);
        if (ch[p][0]) ch[p][1] = i, len[p][1] = l;
        else ch[p][0] = i, len[p][0] = l;
        fa[i] = p;
    }
    ll l = 0, r = (1ll << 17) * 2 * n + 1, ans = r;
    while (l < r) {
        ll mid = (l + r >> 1);
        if (check(mid)) ans = mid, r = mid;
        else l = mid + 1;
    }
    print(ans);
    return output(), 0;
}
} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}