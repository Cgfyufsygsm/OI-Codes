#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

const int maxn = 3e5 + 5;
int len[maxn], ch[maxn][26], fail[maxn], sum[maxn], tot, last;
char s[maxn];

void initPAM() {
    tot = 1;
    len[0] = 0, len[1] = -1;
    fail[0] = fail[1] = 1;
    return;
}

int getfail(int u, int i) {
    while (i - len[u] - 1 < 0 || s[i - len[u] - 1] != s[i])
        u = fail[u];
    return u;
}

void insert(int c, int i) {
    int u = getfail(last, i);
    if (!ch[u][c]) {
        len[++tot] = len[u] + 2;
        fail[tot] = ch[getfail(fail[u], i)][c];
        ch[u][c] = tot;
    }
    ++sum[last = ch[u][c]];
    return;
}

template<typename T> inline T max(const T &a, const T &b) {return a > b ? a : b;}

int main() {
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    initPAM();
    FOR(i, 1, n) insert(s[i] - 'a', i);
    long long ans = 0;
    DEC(i, tot, 2) sum[fail[i]] += sum[i], ans = max(ans, 1ll * sum[i] * len[i]);
    printf("%lld\n", ans);
    return 0;
}