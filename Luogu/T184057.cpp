#include <cstdio>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

typedef unsigned uint;

const int maxn = 1e7 + 5;
int p[maxn], vis[maxn], n, cnt;
uint a[maxn], ans;

int main() {
    scanf("%d", &n);
    FOR(i, 2, n) {
        if (!vis[i]) {
            a[i] = i * i - 1;
            p[++cnt] = i;
        }
        FOR(j, 1, cnt) {
            int k = i * p[j];
            if (k > n) break;
            vis[k] = 1;
            if (i % p[j] == 0) {
                a[k] = a[i] * p[j] * p[j];
                break;
            }
            a[k] = a[i] * (p[j] * p[j] - 1);
        }
        ans += a[i];
    }
    printf("%u\n", ans);
}