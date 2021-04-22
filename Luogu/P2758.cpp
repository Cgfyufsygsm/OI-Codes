#include <cstdio>
#include <cstring>

char s1[2010],s2[2010];
int f[2010][2010];

inline int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    scanf("%s",s1+1);
    scanf("%s",s2+1);
    int l1=strlen(s1+1),l2=strlen(s2+1);
    memset(f,0x3f3f3f3f,sizeof(f));
    for(int i=0;i<=l1;i++)
        f[i][0]=i;
    for(int i=0;i<=l2;i++)
        f[0][i]=i;
    for(int i=1;i<=l1;i++)
        for(int j=1;j<=l2;j++)
        {
            if(s1[i]!=s2[j])
                f[i][j]=min(f[i-1][j-1]+1,min(f[i-1][j]+1,f[i][j-1]+1));
            else
                f[i][j]=min(f[i-1][j-1],min(f[i-1][j]+1,f[i][j-1]+1));
        }
    printf("%d\n",f[l1][l2]);
    return 0;
}