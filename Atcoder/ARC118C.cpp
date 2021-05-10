#include <cstdio>

int vis[10005];

int main()
{
    int n = 0;
    scanf("%d", &n);
    for (int i = 1; i * 6 <= 10000; ++i) vis[i * 6] = 1;
    for (int i = 1; i * 10 <= 10000; ++i) vis[i * 10] = 1;
    for (int i = 1; i * 15 <= 10000; ++i) vis[i * 15] = 1;
    int cnt = 4;
    printf("%d %d %d\n", 6, 10, 15), vis[6] = vis[10] = vis[15] = 0;
    for (int i = 6; i <= 10000 && cnt <= n; ++i) if (vis[i]) printf("%d ", i), ++cnt;
    return 0;
}