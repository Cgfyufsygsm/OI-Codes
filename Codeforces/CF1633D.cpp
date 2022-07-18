#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;
template<typename T> il T chkmax(T &a, const T &b) {return a = (b > a ? b : a);}
template<typename T> il T chkmin(T &a, const T &b) {return a = (b < a ? b : a);}

const int maxn = 1005, N = 1000;
int g[maxn], f[maxn * 12], b[maxn], c[maxn], n, k;

int main() {
    memset(g, 0x3f, sizeof g);
    g[1] = 0;
    FOR(i, 1, N - 1) {
        for (int l = 1, r; l <= i; l = r + 1) {
            r = i / (i / l);
            if (i + i / l <= N) chkmin(g[i + i / l], g[i] + 1);
        }
    }
    int T; cin >> T;
    while (T--) {
        cin >> n >> k;
        FOR(i, 1, n) cin >> b[i];
        FOR(i, 1, n) cin >> c[i];
        memset(f, 0, sizeof f);
        FOR(i, 1, n) DEC(j, min(n * 12, k), g[b[i]]) chkmax(f[j], f[j - g[b[i]]] + c[i]);
        cout << f[min(n * 12, k)] << endl;
    }
    return 0;
}