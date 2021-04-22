#include <cstdio>
#include <cstring>

const int maxn=105;
int f[maxn][maxn],ans[maxn],n;
char s1[maxn],s2[maxn];

inline int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    while(scanf("%s%s",s1+1,s2+1)!=EOF)
    {
        n=strlen(s1+1);
        memset(f,0x3f,sizeof f);
        for(int len=1;len<=n;len++)
            for(int i=1,j=i+len-1;j<=n;i++,j++)
                if(i==j)
                    f[i][j]=1;
                else
                    if(s2[i]==s2[j])
                        f[i][j]=min(f[i][j-1],f[i+1][j]);
                    else
                        for(int k=i;k<j;k++)
                            f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]);
        for(int i=1;i<=n;i++)
        {
            ans[i]=f[1][i];
            if(s1[i]==s2[i])
                ans[i]=ans[i-1];
            else
                for(int j=1;j<i;j++)
                    ans[i]=min(ans[i],ans[j]+f[j+1][i]);
        }
        printf("%d\n",ans[n]);
    }
    return 0;
}