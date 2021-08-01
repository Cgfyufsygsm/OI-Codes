#include <cstdio>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

const int maxn = 2e5 + 5;
int t, n;
char s1[maxn], s2[maxn];
bool vis[maxn];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        scanf("%s", s1 + 1);
        scanf("%s", s2 + 1);
        FOR(i, 0, n + 1) vis[i] = 0;
        int ans1 = 0, ans2 = 0;
        FOR(i, 1, n) {
            if (s1[i] == '0' && s2[i] == '1') {
                ++ans1;
                continue;
            }
            if (s2[i] == '1') {
                if (s1[i - 1] == '1' && !vis[i - 1]) ++ans1, vis[i - 1] = 1;
                else if (s1[i + 1] == '1' && !vis[i + 1]) ++ans1, vis[i + 1] = 1;
            }
        }
        FOR(i, 0, n + 1) vis[i] = 0;
        DEC(i, n, 1) {
            if (s1[i] == '0' && s2[i] == '1') {
                ++ans2;
                continue;
            }
            if (s2[i] == '1') {
                if (s1[i + 1] == '1' && !vis[i + 1]) ++ans2, vis[i + 1] = 1;
                else if (s1[i - 1] == '1' && !vis[i - 1]) ++ans2, vis[i - 1] = 1;
            }
        }
        printf("%d\n", ans1 > ans2 ? ans1 : ans2);
    }
    return 0;
}