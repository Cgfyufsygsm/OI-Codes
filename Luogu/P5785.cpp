#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

namespace fastIO
{
    const int maxc = 1e7 + 5;
    char buf[maxc], *p1 = buf, *p2 = buf;
    il char getchar() {return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, maxc, stdin), p1 == p2) ? EOF : *p1++;}
    int read()
    {
        int s = 0, x = 0;
        char c = getchar();
        while (!isdigit(c))
            x |= (c == '-'), c = getchar();
        while (isdigit(c))
            s = s * 10 + c - '0', c = getchar();
        return x ? -s : s;
    }
}

using namespace fastIO;

typedef long long ll;
const int maxn = 3e5 + 5;
ll n, s, T[maxn], C[maxn], f[maxn];

il ll X(int i) {return C[i];}
il ll Y(int i) {return f[i];}

int q[maxn], head, tail;

int search(int k)
{
    int l = head, r = tail, mid, ret = tail;
    while (l < r)
    {
        mid = (l + r) >> 1;
        int i = q[mid], j = q[mid + 1];
        if ((Y(j) - Y(i)) >= k * (X(j) - X(i))) ret = mid, r = mid;
        else l = mid + 1;
    }
    return q[ret];
}

int main()
{
    n = read(), s = read();
    FOR(i, 1, n) T[i] = T[i - 1] + read(), C[i] = C[i - 1] + read();
    q[head = tail = 1] = 0;
    FOR(i, 1, n)
    {
        int j = search(s + T[i]);
        f[i] = f[j] + T[i] * (C[i] - C[j]) + s * (C[n] - C[j]);
        while (head < tail && 
                (Y(q[tail]) - Y(q[tail - 1])) * (X(i) - X(q[tail])) >= (Y(i) - Y(q[tail])) * (X(q[tail]) - X(q[tail - 1]))) --tail;
        q[++tail] = i;
    }
    printf("%lld\n", f[n]);
    return 0;
}