#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

const int maxn = 5e5 + 5;
char s[maxn];

struct node {
    int ch[26], len, fa, cnt;
} t[maxn];
int tot, last;

void PAMinit() {
    tot = 1;
    t[0].fa = t[1].fa = 1;
    t[0].len = 0, t[1].len = -1;
    return;
}

int getfail(int u, int i) {
    while (i - t[u].len - 1 < 0 || s[i - t[u].len - 1] != s[i])
        u = t[u].fa;
    return u;
}

void insert(int c, int i) {
    int u = getfail(last, i);
    if (!t[u].ch[c]) {
        t[++tot].len = t[u].len + 2;
        int tmp = getfail(t[u].fa, i);
        t[tot].fa = t[tmp].ch[c];
        t[tot].cnt = t[t[tot].fa].cnt + 1;
        t[u].ch[c] = tot;
    }
    last = t[u].ch[c];
    return;
}

int main() {
    scanf("%s", s + 1);
    int n = strlen(s + 1), lastans = 0;
    PAMinit();
    FOR(i, 1, n) {
        s[i] = (s[i] - 97 + lastans) % 26 + 97;
        insert(s[i] - 'a', i);
        printf("%d ", lastans = t[last].cnt);
    }
    return 0;
}