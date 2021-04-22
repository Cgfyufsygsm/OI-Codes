#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

char s[55];

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s", s + 1);
        int n = strlen(s + 1);
        FOR(i, 1, n)
        {
            if (i & 1)
            {
                if (s[i] != 'a')
                    s[i] = 'a';
                else s[i] = 'b';
            }
            else
            {
                if (s[i] != 'z')
                    s[i] = 'z';
                else s[i] = 'y';
            }
        }
        printf("%s\n", s + 1);
    }
    return 0;
}