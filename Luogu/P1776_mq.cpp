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

il int min(int a, int b) {return a < b ? a : b;}

const int maxn = 4e4 + 5;
int f[maxn], head, tail;

struct node
{
    int pos, val;
} q[maxn];

int main()
{
    int n = read(), W = read();
    FOR(i, 1, n)
    {
        int v = read(), w = read(), m = read();
        m = min(m, W / w);
        FOR(mod, 0, w - 1)
        {
            head = 1, tail = 0;
            FOR(k, 0, (W - mod) / w)
            {
                int x = k, y = f[k * w + mod] - k * v;
                while (head <= tail && q[head].pos <  k - m) ++head;
                while (head <= tail && q[tail].val <= y) --tail;
                q[++tail].val = y, q[tail].pos = k;
                f[k * w + mod] = q[head].val + k * v;
            }
        }
    }
    printf("%d\n", f[W]);
    return 0;
}