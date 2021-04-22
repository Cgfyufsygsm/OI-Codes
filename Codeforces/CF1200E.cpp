#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 1e6 + 5;
int n, fail[maxn];
char ans[maxn], tmp[maxn];
int anslen;

inline int min(int a, int b) {return a < b ? a : b;}

int main()
{
    scanf("%d", &n);
    while (n--)
    {
        scanf("%s", tmp + 1);
        int tmplen = strlen(tmp + 1), tmplen1 = tmplen;
        int l = min(tmplen, anslen);
        tmp[++tmplen] = '#';
        for (int i = anslen - l + 1; i <= anslen; ++i)
            tmp[++tmplen] = ans[i];
        for (int i = 2, j = 0; i <= tmplen; ++i)
        {
            while (j && tmp[j + 1] != tmp[i])
                j = fail[j];
            if (tmp[j + 1] == tmp[i]) ++j;
            fail[i] = j;
        }
        for (int i = fail[tmplen] + 1; i <= tmplen1; ++i)
            ans[++anslen] = tmp[i];
    }
    for (int i = 1; i <= anslen; ++i) printf("%c", ans[i]);
    return 0;
}