#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define YES puts("YES")
#define NO puts("NO")

const int maxn = 3e5 + 5;
char s[maxn];
int n;

int main()
{
    //freopen("CF1504A.out", "w", stdout);
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s", s + 1);
        n = strlen(s + 1);
        int flag = 0;
        FOR(i, 1, n)
            if (s[i] != 'a')
            {
                flag = i;
                break;
            }
        if (flag)
        {
            YES;
            flag = n - flag + 2;
            FOR(i, 1, flag - 1)
                printf("%c", s[i]);
            printf("a");
            FOR(i, flag >= 1 ? flag : 1, n)
                printf("%c", s[i]);
            puts("");
        }
        else NO;
    }
    return 0;
}