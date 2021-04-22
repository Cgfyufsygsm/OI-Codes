#include <cstdio>
#include <cmath>
#include <cstring>

const int maxn = 1000000 + 5;
int n, k, fail[maxn];
char s[maxn];

bool check(int i)
{
    int period = i - fail[i];
    int up = floor(i / (1.0 * k * period)), down = ceil(i / ((k + 1.0) * period));
    return up >= down;
}

int main()
{
    scanf("%d %d", &n, &k);
    scanf("%s", s + 1);
    for (int i = 2, j = 0; i <= n; ++i)
    {
        while (j && s[i] != s[j + 1])
            j = fail[j];
        if (s[i] == s[j + 1])
            ++j;
        fail[i] = j;
    }
    for (int i = 1; i <= n; ++i) printf("%d", check(i));
    return 0;
}