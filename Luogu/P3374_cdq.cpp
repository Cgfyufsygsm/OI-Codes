#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

typedef long long ll;

namespace fastIO {
    const int maxc = 1e7 + 5;
    char buf[maxc], *p1 = buf, *p2 = buf;
    il char getchar() {return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, maxc, stdin), p1 == p2) ? EOF : *p1++;}
    ll read() {
        ll s = 0, x = 0;
        char c = getchar();
        while (!isdigit(c))
            x |= (c == '-'), c = getchar();
        while (isdigit(c))
            s = s * 10 + c - '0', c = getchar();
        return x ? -s : s;
    }
}

using namespace fastIO;

const int maxn = 5e6 + 5;

struct node {
    int type, id;
    ll val;
    il bool operator<(const node &b) {return id == b.id ? type < b.type : id < b.id;}
} A[maxn], B[maxn];
ll ans[maxn];

int n, m, tot, totx;

void cdq(int l, int r) {
    if (l == r) return;
    int m = (l + r) >> 1;
    cdq(l, m), cdq(m + 1, r);
    int t1 = l, t2 = m + 1;
    ll sum = 0;
    FOR(i, l, r) {
        if ((t1 <= m && A[t1] < A[t2]) || t2 > r) {
            if (A[t1].type == 1) sum += A[t1].val;
            B[i] = A[t1++];
        } else {
            if (A[t2].type == 3) ans[A[t2].val] += sum;
            else if (A[t2].type == 2) ans[A[t2].val] -= sum;
            B[i] = A[t2++];
        }
    }
    FOR(i, l, r) A[i] = B[i];
    return;
}

int main() {
    n = read(), m = read();
    FOR(i, 1, n) {
        ++tot;
        A[tot].type = 1, A[tot].id = i, A[tot].val = read();
    }
    FOR(i, 1, m) {
        int t = read();
        A[++tot].type = t;
        if (t == 1) A[tot].id = read(), A[tot].val = read();
        else {
            int l = read(), r = read();
            ++totx;
            A[tot].val = totx, A[tot].id = l - 1;
            ++tot;
            A[tot].type = 3, A[tot].val = totx, A[tot].id = r;
        }
    }
    cdq(1, tot);
    FOR(i, 1, totx) printf("%lld\n", ans[i]);
    return 0;
}