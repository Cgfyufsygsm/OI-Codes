#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define clr(a) memset(a, 0, sizeof a)

const int maxn = (1 << 20) + 5;
typedef long long ll;

char s[maxn];
int z[maxn], n, fsuf[maxn], buc[26];

inline int min(int a, int b) {return a < b ? a : b;}

#define lowbit(x) (x & -x)

int t[27];

void add(int x)
{
    for (; x <= 26; x += lowbit(x))
        ++t[x];
    return;
}

int query(int x)
{
    int ret = 0;
    for (; x; x -= lowbit(x))
        ret += t[x];
    return ret;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s", s + 1);
        n = strlen(s + 1);
        clr(z), clr(fsuf), clr(buc);
        z[1] = n;
        for (int i = 2, l = 0, r = 0; i <= n; ++i)
        {
            if (i <= r) z[i] = min(z[i - l + 1], r - i + 1);
            while (i + z[i] <= n && s[i + z[i]] == s[z[i] + 1]) ++z[i];
            if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
        }
        //计算 z 数组
        DEC(i, n, 1)
        {
            ++buc[s[i] - 'a'];
            if (buc[s[i] - 'a'] & 1) fsuf[i] = fsuf[i + 1] + 1;
            else fsuf[i] = fsuf[i + 1] - 1;
        }
        //处理出所有后缀的 F 值
        clr(buc), clr(t);
        int f = 0;//当前前缀的 f 值
        ll ans = 0;
        FOR(i, 1, n - 1)
        {
            ++buc[s[i] - 'a'];
            f += ((buc[s[i] - 'a'] & 1) ? 1 : -1);
            int totk = min(z[i + 1], n - i - 1) / i + 1;
            int tot0 = totk >> 1, tot1 = (totk + 1) >> 1;//k 为偶数/奇数的数量
            ans += 1ll * tot0 * query(fsuf[1] + 1) + 1ll * tot1 * query(fsuf[i + 1] + 1);
            add(f + 1);
            //树状数组传进去的要全部加 1 是因为会有 0 的贡献
        }
        printf("%lld\n", ans);
    }
    return 0;
}