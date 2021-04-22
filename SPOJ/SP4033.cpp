#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 1e4 + 5;

int trie[maxn * 201][10], end[maxn * 201], cnt;

bool insert(char *s)
{
    bool flag1 = 0, flag2 = 1;
    int len = strlen(s), p = 1;
    FOR(i, 0, len - 1)
    {
        if (end[p]) flag1 = 1;
        char ch = s[i] - '0';
        if (!trie[p][ch])
            flag2 = 0, trie[p][ch] = ++cnt;
        p = trie[p][ch];
    }
    end[p] = 1;
    if (flag1) return true;
    else if (flag2) return true;
    return false;
}

int main()
{
    int T;
    scanf("%d", &T);
    char str[15];
    while (T--)
    {
        int n;
        scanf("%d", &n);
        bool flag = 0;
        memset(trie, 0, sizeof trie);
        memset(end, 0, sizeof end);
        cnt = 1;
        while (n--)
        {
            scanf("%s", str);
            flag |= insert(str);
        }
        if (flag) printf("NO\n");
        else printf("YES\n");
    }
    return 0;
}