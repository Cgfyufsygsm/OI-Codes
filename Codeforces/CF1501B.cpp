#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

int read()
{
    int s = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

inline int max(int a, int b) {return a > b ? a : b;}

const int maxn = 2e5 + 5;
int stk[maxn], n;

int main()
{
    int T = read();
    while (T--)
    {
        n = read();
        FOR(i, 1, n)
        {
            int a = read();
            if (!a) continue;
            int low = max(0, i - a + 1), up = i;
            ++stk[low], --stk[up + 1];
        }
        FOR(i, 1, n) stk[i] += stk[i - 1];
        FOR(i, 1, n) printf("%d ", stk[i] ? 1 : 0), stk[i] = 0;
        stk[n + 1] = stk[0] = 0;
        puts("");
    }
    return 0;
}