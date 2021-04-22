#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define DEC(i,a,b) for(int i=a;i>=b;i--)

const int maxn=55,maxt=500;
int n,T;
int f[maxt][maxn],t[maxn],s1[maxn],s2[maxn];
bool has_train[maxt][maxn][2];

inline int read()
{
    char c = getchar();
    int s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

inline int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int kase=0;
    while(n=read())
    {
        memset(t,0,sizeof t);
        memset(s1,0,sizeof s1);
        memset(s2,0,sizeof s2);
        memset(f,0x3f,sizeof f);
        memset(has_train,0,sizeof has_train);
        T=read();
        FOR(i,1,n-1)
            t[i]=read();
        FOR(i,1,n)
            s1[i]=s1[i-1]+t[i-1];
        DEC(i,n,1)
            s2[i]=s2[i+1]+t[i];
        int m=read(),tmp;
        while(m--)
        {
            tmp=read();
            FOR(i,1,n)
                has_train[tmp+s1[i]][i][0]=1;
        }
        m=read();
        while(m--)
        {
            tmp=read();
            DEC(i,n,1)
                has_train[tmp+s2[i]][i][1]=1;
        }
        f[T][n]=0;
        DEC(i,T-1,0)
            FOR(j,1,n)
            {
                f[i][j]=f[i+1][j]+1;
                if(j<n && has_train[i][j][0] && i+t[j]<=T)
                    f[i][j]=min(f[i][j],f[i+t[j]][j+1]);
                if(j>1 && has_train[i][j][1] && i+t[j-1]<=T)
                    f[i][j]=min(f[i][j],f[i+t[j-1]][j-1]);
            }
        printf("Case Number %d: ",++kase);
        if(f[0][1]>T)
            printf("impossible\n");
        else printf("%d\n",f[0][1]);
    }
    return 0;
}