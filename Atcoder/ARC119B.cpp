#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

template<typename T> inline void swap(T &a,T &b)
{
    T t = a;
    return void(a = b, b = t);
}

const int maxn = 5e5 + 5;

int n;
char s[maxn], t[maxn];
int pos1[maxn], pos2[maxn];

int main()
{
    scanf("%d", &n);
    scanf("%s", s + 1);
    scanf("%s", t + 1);
    FOR(i, 1, n) if (s[i] == '0') pos1[++pos1[0]] = i;
    FOR(i, 1, n) if (t[i] == '0') pos2[++pos2[0]] = i;
    int ans = 0;
    if (pos1[0] != pos2[0])
        return puts("-1"), 0;
    for (int i = 1, j = 1; i <= pos2[0]; ++i, ++j)
    {
        if (j > pos1[0])
            return puts("-1"), 0;
        ++ans;
        if (pos1[j] == pos2[i]) --ans;
    }
    printf("%d\n", ans);
    return 0;

}