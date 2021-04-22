#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define YES printf("YES\n")
#define NO printf("NO\n")

inline int read()
{
    char c = getchar();
    int s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

const int maxn = 1e5 + 5;
char s[maxn];

int main()
{
    int T = read();
    int px, py;
    while (T--)
    {
        scanf("%d %d", &px, &py);
        scanf("%s", s + 1);
        int n = strlen(s + 1);
        int l = 0, r = 0, u = 0, d = 0;
        FOR(i, 1, n)
            if (s[i] == 'U')
                ++u;
            else if (s[i] == 'D')
                ++d;
            else if (s[i] == 'L')
                ++l;
            else if (s[i] == 'R')
                ++r;
        bool flag1 = 0, flag2 = 0;
        flag1 = ((px > 0 && px <= r) || (px < 0 && ((-px) <= l)) || (px == 0));
        flag2 = ((py > 0 && py <= u) || (py < 0 && ((-py) <= d)) || (py == 0));
        if (flag1 && flag2) YES;
        else NO;
    }
    return 0;
}