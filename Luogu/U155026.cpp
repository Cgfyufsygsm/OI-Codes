#include <cstdio>

const int maxn = 1e5 + 5, mod = 1e9 + 7;

int phi[maxn], n, ans[maxn];

void get_phi()
{
    phi[1] = 1;
    for (int i = 2; i < maxn; ++i)
    {
        if (!phi[i])
        {
            for (int j = i; j < maxn; j += i)
            {
                if (!phi[j]) phi[j] = j;
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
    return;
}

int main()
{
    scanf("%d", &n);
    get_phi();
    int k = n >> 1;
    for (int c = 1; c <= k; ++c)
        for (int a = c * 2; a <= n; a += c)
        {
            int b = a - c;
            if (c == (a ^ b))
                ++ans[a ^ b];
        }
    long long ret = 0;
    for (int i = 1; i <= n; ++i)
        (ret += 2ll * ans[i] * phi[i]) %= mod;
    printf("%lld\n", ret);
    return 0;
}