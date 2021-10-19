#include <cstdio>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

int n, m;
char s1[505], s2[1005];

bool check0(int p) {
    for (int i = p, j = p; i >= 1 && j <= m; --i, ++j) if (s2[i] != s2[j]) return false;
    return true;
}

bool check1(int edm) {
    bool flag = 0;
    FOR(st, 1, n) {
        int i, j;
        for (i = st, j = 1; i <= n && j <= edm; ++i, ++j) {
            if (s1[i] != s2[j]) break;
        }
        for (i -= 2; i >= 1 && j <= m; --i, ++j) {
            if (s1[i] != s2[j]) break;
        }
        if (j == m + 1) flag = 1;
        if (flag) break;
    }
    return flag;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%s", s1 + 1), scanf("%s", s2 + 1);
        n = strlen(s1 + 1), m = strlen(s2 + 1);
        bool flag = 0;
        FOR(i, 1, m) {
            if (check0(i) && check1(i)) {
                flag = 1;
                break;
            }
        }
        puts(flag ? "YES" : "NO");
    }
    return 0;
}