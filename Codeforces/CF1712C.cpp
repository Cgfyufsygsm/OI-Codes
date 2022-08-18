#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;
template<typename T> il T chkmax(T &a, const T &b) {return a = (b > a ? b : a);}
template<typename T> il T chkmin(T &a, const T &b) {return a = (b < a ? b : a);}

const int maxn = 1e5 + 5;
int n, a[maxn], l[maxn], r[maxn], vis[maxn], cnt[maxn];

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n;
        FOR(i, 1, n) l[i] = 1e9, r[i] = 0, vis[i] = 0, cnt[i] = 0;
        FOR(i, 1, n) {
            cin >> a[i], chkmin(l[a[i]], i), chkmax(r[a[i]], i);
            cnt[i] = cnt[i - 1];
            if (!vis[a[i]]) ++cnt[i];
            vis[a[i]] = 1;
        }
        set<int> S;
        int ans = 1e9;
        a[n + 1] = 1e9;
        DEC(i, n, 1) {
            if (a[i] > a[i + 1]) break;
            if (i == r[a[i]]) S.insert(a[i]);
            if (i == l[a[i]]) S.erase(a[i]);
            if (S.empty()) chkmin(ans, cnt[i - 1]);
        }
        chkmin(ans, cnt[n]);
        cout << ans << '\n';
    }
    return 0;
}