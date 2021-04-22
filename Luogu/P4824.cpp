#include <cstdio>
#include <cstring>

const int maxn = 1e6 +5;
char s[maxn], t[maxn];
int n, m;
int fail[maxn];

int posj[maxn], stk[maxn], top;

int main()
{
    scanf("%s", s + 1);
    scanf("%s", t + 1);
    n = strlen(s + 1), m = strlen(t + 1);
    for (int i = 2, j = 0; i <= m; ++i)
    {
        while (j && t[j + 1] != t[i])
            j = fail[j];
        if (t[j + 1] == t[i])
            ++j;
        fail[i] = j;
    }
    for (int i = 1, j = 0; i <= n; ++i)
    {
        while (j && t[j + 1] != s[i])
            j = fail[j];
        if (t[j + 1] == s[i])
            ++j;
        posj[i] = j, stk[++top] = i;
        if (j == m)
            top -= m, j = posj[stk[top]];
    }
    for (int i = 1; i <= top; ++i) putchar(s[stk[i]]);
    return 0;
}