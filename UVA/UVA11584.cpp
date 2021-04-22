#include <cstdio>
#include <cstring>

const int maxn=1005;
bool ispa[maxn][maxn];
char s[maxn];
int f[maxn];

inline int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s",s+1);
        memset(ispa,0,sizeof ispa);
        memset(f,0x3f,sizeof f);
        int n=strlen(s+1);
        for(int i=1;i<=n;i++)
            ispa[i][i]=1;
        for(int mid=1;mid<=n;mid++)
        {
            for(int i=mid-1,j=mid+1;i>=1 && j<=n && s[i]==s[j];i--,j++)
                ispa[i][j]=1;
            for(int i=mid-1,j=mid;i>=1 && j<=n && s[i]==s[j];i--,j++)
                ispa[i][j]=1;
            for(int i=mid,j=mid+1;i>=1 && j<=n && s[i]==s[j];i--,j++)
                ispa[i][j]=1;
        }
        f[0]=0;
        for(int i=1;i<=n;i++)
            for(int j=0;j<i;j++)
                if(ispa[j+1][i])
                    f[i]=min(f[i],f[j]+1);
        printf("%d\n",f[n]);
    }
    return 0;
}