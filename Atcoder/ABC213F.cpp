#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

typedef long long ll;
const int maxn = (1000000 * 2) + 5;
int sa[maxn], rk[maxn], oldrk[maxn], id[maxn], cnt[maxn], ht[maxn];
char s[maxn];

int n, m;

inline bool cmp(int i, int j, int k) { return oldrk[i] == oldrk[j] && oldrk[i + k] == oldrk[j + k]; }

int l[maxn], r[maxn], stk[maxn], top;
ll ans[maxn];

int main() {
    scanf("%d", &n);
    scanf("%s", s + 1);

    m = 'z';
    FOR(i, 1, n) ++cnt[rk[i] = s[i]];
    FOR(i, 1, m) cnt[i] += cnt[i - 1];
    DEC(i, n, 1) sa[cnt[rk[i]]--] = i;

    for (int k = 1; k < n; k <<= 1) {
        int num = 0;
        FOR(i, n - k + 1, n) id[++num] = i;
        FOR(i, 1, n) if (sa[i] > k) id[++num] = sa[i] - k;

        memset(cnt, 0, sizeof cnt);
        FOR(i, 1, n) ++cnt[rk[i]];
        FOR(i, 1, m) cnt[i] += cnt[i - 1];
        DEC(i, n, 1) sa[cnt[rk[id[i]]]--] = id[i];

        memcpy(oldrk, rk, sizeof rk);
        num = 0;
        FOR(i, 1, n) rk[sa[i]] = cmp(sa[i], sa[i - 1], k) ? num : ++num;
        m = num;
        if (num == n) break;
    }

    for (int i = 1, k = 0; i <= n; ++i) {
        if (k) --k;
        while (s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
        ht[rk[i]] = k;
    }
    
    top = 0;
    ll res = 0;
    stk[0] = 1;
    FOR(i, 1, n) {
        if (i != 1) {
            while (top >= 1 && ht[stk[top]] >= ht[i]) {
                res -= 1LL * ht[stk[top]] * (stk[top] - stk[top - 1]);
                top--;
            }
            res += 1LL * ht[i] * (i - stk[top]);
            stk[++top] = i;
        }
        ans[sa[i]] = res;
    }
    top = 0;
    res = 0;
    stk[0] = n + 1;
    DEC(i, n, 1) {
        if (i != n) {
            while (top >= 1 && ht[stk[top]] >= ht[i + 1]) {
                res -= 1LL * ht[stk[top]] * (stk[top - 1] - stk[top]);
                top--;
            }
            res += 1LL * ht[i + 1] * (stk[top] - i - 1);
            stk[++top] = i + 1;
        }
        ans[sa[i]] += res;
    }
    FOR(i, 1, n) ans[i] += n - i + 1;
    FOR(i, 1, n) printf("%lld\n", ans[i]);
    return 0;
}