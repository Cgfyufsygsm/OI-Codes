#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;

const int maxn = 2e3 + 5;
bitset<maxn> a[maxn];
char s[maxn];
int n, m, tot, ans[maxn];

int main() {
    cin >> n >> m;
    FOR(i, 1, m) {
        cin >> s + 1 >> s[n + 1];
        FOR(j, 1, n + 1) a[i][j] = s[j] - '0';
    }
    FOR(i, 1, n) {
        int r = i;
        for (; r <= m && !a[r][i]; ++r) ;
        if (r == m + 1) return puts("Cannot Determine"), 0;
        tot = max(tot, r);
        swap(a[r], a[i]);
        FOR(j, 1, m) if (i != j && a[j].test(i)) a[j] ^= a[i];
    }
    cout << tot << endl;
    FOR(i, 1, n) puts(a[i].test(n + 1) ? "?y7M#" : "Earth");
    return 0;
}