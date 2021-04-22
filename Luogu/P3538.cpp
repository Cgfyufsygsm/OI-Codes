#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

typedef long long ll;

const int maxn = 500000 + 5;
const ll mod = 1e9 + 7;
int n, is_prime[maxn + 2], prime[maxn + 2], minfact[maxn + 2], pcnt;
char s[maxn];
ll hash[maxn], pow[maxn], p = 29;

void make_prime()
{
    minfact[1] = 1;
    FOR(i, 2, maxn)
    {
        if (!is_prime[i])
        {
            prime[++pcnt] = i;
            minfact[i] = i;
        }
        for (int j = 1; j <= pcnt && i * prime[j] <= maxn; ++j)
        {
            is_prime[i * prime[j]] = 1;
            minfact[i * prime[j]] = prime[j];
            if (i % prime[j] == 0) break;
        }
    }
    return;
}

ll gethash(int l, int r)
{
    return ((hash[r] - hash[l - 1] * pow[r - l + 1]) % mod + mod) % mod;
}

int work(int l, int r)
{
    int len = r - l + 1, ans = len;
    while (len > 1)
    {
        //printf("%d\n", minfact[len]);
        if (gethash(l + ans / minfact[len], r) == gethash(l, r - ans / minfact[len]) && gethash(l + ans / minfact[len], r) == gethash(l, r - ans / minfact[len]))
            ans /= minfact[len];
        len /= minfact[len];
    }
    return ans;
}

int main()
{
    make_prime();
    scanf("%d", &n);
    scanf("%s", s + 1);
    FOR(i, 1, n)
        hash[i] = (hash[i - 1] * p + s[i] - 'b') % mod;
    pow[0] = 1;
    FOR(i, 1, n) pow[i] = pow[i - 1] * p % mod;
    int q;
    scanf("%d", &q);
    while (q--)
    {
        int l, r;
        scanf("%d %d", &l, &r);
        if (gethash(l + 1, r) == gethash(l, r - 1)) printf("1\n");
        else printf("%d\n", work(l, r));
    }
    return 0;
}