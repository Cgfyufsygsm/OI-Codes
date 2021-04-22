#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define il inline

const int maxn = 500000 + 5;
int n, m, s[maxn], f[maxn], head, tail, q[maxn];;

il int X(int j) {return s[j];}
il int Y(int j) {return f[j] + s[j] * s[j];}
il int SlopeUp(int i, int j) {return Y(i) - Y(j);}
il int SlopeDown(int i, int j) {return X(i) - X(j);}

int main()
{
    while (~scanf("%d %d", &n, &m))
    {
        s[0] = f[0] = q[0] = 0;
        FOR(i, 1, n)
            scanf("%d", s + i), s[i] += s[i - 1];
        q[head = tail = 1] = 0;
        FOR(i, 1, n)
        {
            while (head < tail && SlopeUp(q[head], q[head + 1]) >= 2 * s[i] * SlopeDown(q[head], q[head + 1]))
                ++head;
            int j = q[head];
            f[i] = f[j] + (s[i] - s[j]) * (s[i] - s[j]) + m;
            while (head < tail && SlopeUp(i, q[tail]) * SlopeDown(q[tail], q[tail - 1]) <= SlopeUp(q[tail], q[tail - 1]) * SlopeDown(i, q[tail]))
                --tail;
            q[++tail] = i;
        }
        printf("%d\n", f[n]);
    }
    return 0;
}