#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define il inline

typedef long long ll;

const int maxn = 4e5 + 5;

int n;

char T1[maxn], T2[maxn], s1[maxn], s2[maxn];

void revstr(char *a, char *b)
{
    int len = strlen(a + 1);
    FOR(i, 1, len) b[len - i + 1] = a[i];
    b[len + 1] = '\0';
    return;
}

ll left[maxn], right[maxn], ans;

struct ACAM
{
    struct node
    {
        int ch[26], fail, val;
    } t[maxn];
    int tot = 0;

    void insert(char *s)
    {
        int u = 0, len = strlen(s + 1);
        FOR(i, 1, len)
        {
            int c = s[i] - 'a';
            if (!t[u].ch[c]) t[u].ch[c] = ++tot;
            u = t[u].ch[c];
        }
        ++t[u].val;
    }

    void build()
    {
        static int q[maxn], head = 1, tail = 0;
        FOR(c, 0, 25)
            if (t[0].ch[c]) q[++tail] = t[0].ch[c];
        while (head <= tail)
        {
            int u = q[head++];
            FOR(c, 0, 25)
                if (t[u].ch[c])
                    t[t[u].ch[c]].fail = t[t[u].fail].ch[c], q[++tail] = t[u].ch[c];
                else t[u].ch[c] = t[t[u].fail].ch[c];
            t[u].val += t[t[u].fail].val;
        }
        return;
    }

    void query(ll *a, char *s)
    {
        int len = strlen(s + 1);
        int u = 0;
        FOR(i, 1, len)
        {
            int c = s[i] - 'a';
            u = t[u].ch[c];
            a[i] = t[u].val;
        }
        return;
    }
} t1, t2;//t1 存原串，t2 存反串

int main()
{
    scanf("%s", T1 + 1), revstr(T1, T2);
    scanf("%d", &n);
    FOR(i, 1, n)
    {
        scanf("%s", s1 + 1), revstr(s1, s2);
        t1.insert(s1), t2.insert(s2);
    }
    t1.build(), t2.build();
    int lent = strlen(T1 + 1);
    t1.query(left, T1), t2.query(right, T2);
    FOR(i, 1, lent - 1)
        ans += left[i] * right[lent - i];
    printf("%lld\n", ans);
    return 0;
}