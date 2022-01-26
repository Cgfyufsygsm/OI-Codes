#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

const int maxx = 1e7 + 5, N = 1e7;
bool ok[maxx];
int id[maxx], num[maxx];

bool check(int x) {
    bool ret = 0;
    while (x) ret |= (x % 10 == 7), x /= 10;
    return ret;
}

int main() {
    FOR(i, 1, N) {
        if (ok[i] || !check(i)) continue;
        for (int j = i; j <= N; j += i) ok[j] = 1;
    }
    int cnt = 0;
    FOR(i, 1, N) if (!ok[i]) num[id[i] = ++cnt] = i;
    num[id[N + 1] = ++cnt] = N + 1;

    int T; scanf("%d", &T);
    while (T--) {
        int n; scanf("%d", &n);
        if (ok[n]) puts("-1");
        else printf("%d\n", num[id[n] + 1]);
    }
    return 0;
}