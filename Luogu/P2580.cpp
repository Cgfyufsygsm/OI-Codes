#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 1e4 + 5;
int trie[maxn * 26 * 50][26], end[maxn * 26 * 50], tot, vis[maxn];

void insert(char *s, int val)
{
    int len = strlen(s), p = 1;
    FOR(i, 0, len - 1)
    {
        char ch = s[i] - 'a';
        if (!trie[p][ch])
            trie[p][ch] = ++tot;
        p = trie[p][ch];
    }
    end[p] = val;
    return;
}

int search(char *s)
{
    int len = strlen(s), p = 1;
    FOR(i, 0, len - 1)
    {
        if (!trie[p][s[i] - 'a']) return 0;
        p = trie[p][s[i] - 'a'];
    }
    return end[p];
}

int main()
{
    int n, m;
    scanf("%d", &n);
    char str[52];
    FOR(i, 1, n)
    {
        scanf("%s", str);
        insert(str, i);
    }
    scanf("%d", &m);
    while (m--)
    {
        scanf("%s", str);
        int ret = search(str);
        if (ret && !vis[ret]) printf("OK\n");
        else if (!ret) printf("WRONG\n");
        else printf("REPEAT\n");
        ++vis[ret];
    }
    return 0;
}