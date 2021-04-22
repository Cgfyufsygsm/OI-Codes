#include <cstdio>
#include <cstring>

const int maxn = 1e6 + 5;
int n, fail[maxn];
char s[maxn];

int main()
{
    scanf("%d", &n);
    scanf("%s", s + 1);
    fail[1] = 0;
    for (int i = 2, j = 0; i <= n; ++i)
    {
        while (j && s[j + 1] != s[i])
            j = fail[j];
        if (s[j + 1] == s[i]) ++j;
        fail[i] = j;
    }
    printf("%d\n", n - fail[n]);
    return 0;
}