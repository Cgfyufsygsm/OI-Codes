#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

const int maxn = 5e5 + 5;
int fail[maxn], len[maxn], ch[maxn][26], trans[maxn], sum[maxn];
int tot, last;
char s[maxn];

void initPAM() {
    tot = 1;
    fail[0] = fail[1] = 1;
    len[0] = 0, len[1] = -1;
    return;
}

int getfail(int u, int i) {
    while (i - len[u] - 1 < 0 || s[i - len[u] - 1] != s[i])
        u = fail[u];
    return u;
}

int gettrans(int u, int i) {
    while (((len[u] + 2) << 1) > len[tot] || s[i - len[u] - 1] != s[i])
        u = fail[u];
    return u;
}

void insert(int c, int i) {
    int u = getfail(last, i);
    if (!ch[u][c]) {
        len[++tot] = len[u] + 2;
        fail[tot] = ch[getfail(fail[u], i)][c];
        ch[u][c] = tot;
        sum[tot] = sum[fail[tot]] + 1;
        if (len[tot] <= 2) trans[tot] = fail[tot];
        else trans[tot] = ch[gettrans(trans[u], i)][c];
    }
    last = ch[u][c];
    return;
}

inline int max(int a, int b) {return a > b ? a : b;}

int main() {
    int n;
    scanf("%d %s", &n, s + 1);
    initPAM();
    FOR(i, 1, n) insert(s[i] - 'a', i);
    int ans = 0;
    FOR(u, 2, tot)
        if (len[trans[u]] * 2 == len[u] && len[trans[u]] % 2 == 0)
            ans = max(ans, len[u]);
    printf("%d\n", ans);
}