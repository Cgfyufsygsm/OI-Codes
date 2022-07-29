#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

const int maxn = 4e5 + 5, LG = 18;
int ch[maxn][2], len[maxn], fa[maxn], tot = 1, las = 1;
int st[LG][maxn], lg[maxn], n;
char s[maxn], t[maxn];

void extend(int c) {
    int cur = ++tot;
    len[cur] = len[las] + 1;
    int p = las;
    while (p && !ch[p][c]) ch[p][c] = cur, p = fa[p];
    if (!p) fa[cur] = 1;
    else {
        int q = ch[p][c];
        if (len[q] == len[p] + 1) fa[cur] = q;
        else {
            int clone = ++tot;
            memcpy(ch[clone], ch[q], sizeof ch[q]);
            len[clone] = len[p] + 1, fa[clone] = fa[q];
            while (p && ch[p][c] == q) ch[p][c] = clone, p = fa[p];
            fa[cur] = fa[q] = clone;
        }
    }
    las = cur;
    return;
}

int main() {
    scanf("%s", s + 1), n = strlen(s + 1);
    scanf("%s", t + 1);
    for (int i = 1; t[i]; ++i) extend(t[i] - 'a');
    int p = 1, cur = 0;
    lg[0] = -1;
    FOR(i, 1, n) {
        int c = s[i] - 'a';
        while (p && !ch[p][c]) p = fa[p], cur = len[p];
        if (ch[p][c]) p = ch[p][c], ++cur;
        else p = 1, cur = 0;
        st[0][i] = cur;
        lg[i] = lg[i >> 1] + 1;
    }
    FOR(j, 1, LG - 1) FOR(i, 1, n) st[j][i] = max(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
    auto query = [](int l, int r) {
        int s = lg[r - l + 1];
        return max(st[s][l], st[s][r - (1 << s) + 1]);
    };
    int m; scanf("%d", &m);
    while (m--) {
        int L, R; scanf("%d %d", &L, &R);
        int l = 0, r = R - L + 1, ans = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (query(L + mid - 1, R) >= mid) ans = mid, l = mid + 1;
            else r = mid - 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}