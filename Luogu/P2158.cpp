#include <cstdio>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 60000;
int phi[maxn];

void make_phi()
{
    phi[1] = 1;
    FOR(i, 2, maxn)
        if (!phi[i])
            for (int j = i; j <= maxn; j += i)
            {
                if (!phi[j])
                    phi[j] = j;
                phi[j] = phi[j] / i * (i - 1);
            }
    return;
}

int main()
{
    make_phi();
    int n;
    scanf("%d", &n);
    int ans = 0;
    FOR(i, 2, n - 1)
        ans += phi[i];
    if (n == 1)
        printf("0\n");
    else printf("%d\n", 2 * ans + 3);
    return 0;
}