#include <cstdio>
#include <cstring>

const int maxn = 1e6 + 5;
int n, fail[maxn];
char s[maxn];

int main()
{
    while (scanf("%s", s + 1) != EOF)
    {
        n = strlen(s + 1);
        if (n == 1 && s[1] == '.') return 0;
        fail[1] = 0;
        for (int i = 2, j = 0; i <= n; ++i)
        {
            while (j && s[j + 1] != s[i])
                j = fail[j];
            if (s[j + 1] == s[i]) ++j;
            fail[i] = j;
        }
        if (n % (n - fail[n])) printf("%d\n", 1);
        else printf("%d\n", n / (n - fail[n]));
    }
    return 0;
}