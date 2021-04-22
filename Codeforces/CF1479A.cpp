#include <cstdio>

int a[100005];

void ask(int i)
{
    if (a[i]) return;
    printf("? %d\n", i);
    fflush(stdout);
    scanf("%d", &a[i]);
    return;
}

int main()
{
    int n;
    scanf("%d", &n);
    int l = 1, r = n, mid;
    a[0] = a[n + 1] = 1e9;
    while (true)
    {
        mid = (l + r) / 2;
        ask(mid), ask(mid - 1), ask(mid + 1);
        if (a[mid - 1] > a[mid] && a[mid] < a[mid + 1])
        {
            printf("! %d\n", mid);
            return 0;
        }
        else if (a[mid - 1] > a[mid] && a[mid] > a[mid + 1])
            l = mid + 1;
        else r = mid - 1;
    }
    return 0;
}