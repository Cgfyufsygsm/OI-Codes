#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

const int mod = 1e9 + 7;

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
}

using namespace fastIO;
using namespace std;

template<typename T> il T chkmax(T &a, const T &b) {return a = max(a, b);}
template<typename T> il T chkmin(T &a, const T &b) {return a = min(a, b);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

const int maxn = 1e5 + 5;
int k, n, m, a[maxn];

using ll = long long;
using db = double;
using pii = pair<int, int>;
using pdi = pair<db, int>;
pii op1[maxn];
vector<pii> op2[maxn];
vector<pdi> op3;
vector<int> ans;
int ops[maxn][3];

int main() {
    read(k), read(n), read(m);
    FOR(i, 1, k) read(a[i]);
    FOR(i, 1, n) {
        int op, id, b;
        read(op), read(id), read(b);
        ops[i][0] = op, ops[i][1] = id, ops[i][2] = b;
        if (op == 1) op1[id] = max(op1[id], pii(b, i));
        else if (op == 2) op2[id].emplace_back(pii(b, i));
        else op3.emplace_back(pdi(b, i));
    }
    FOR(i, 1, k) if (op1[i].first > a[i]) op2[i].emplace_back(op1[i].first - a[i], op1[i].second);
    FOR(i, 1, k) {
        sort(op2[i].begin(), op2[i].end(), greater<pii>());
        ll num = a[i];
        for (auto p : op2[i]) {
            op3.emplace_back(1.0 * (num + p.first) / num, p.second);
            num += p.first;
        }
    }
    sort(op3.begin(), op3.end(), greater<pdi>());
    m = min(m, (int)op3.size());
    FOR(i, 0, m - 1) ans.emplace_back(op3[i].second);
    sort(ans.begin(), ans.end(), [](const int &a, const int &b) {return ops[a][0] < ops[b][0];});
    print(ans.size(), '\n');
    for (auto id : ans) print(id, ' ');
    return output(), 0;
}
