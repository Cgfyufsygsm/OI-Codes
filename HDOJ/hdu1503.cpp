#include <cstdio>
#include <cstring>

char a[105],b[105];
int lena,lenb;
int f[105][105],way[105][105];
int chosen[105];

inline int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    while(scanf("%s %s",a+1,b+1)!=EOF)
    {
        lena=strlen(a+1),lenb=strlen(b+1);
        memset(chosen,0,sizeof chosen);
        for(int i=1;i<=lena;i++)
            for(int j=1;j<=lenb;j++)
                if(a[i]==b[j])
                    f[i][j]=f[i-1][j-1]+1,way[i][j]=0;
                else
                    if(f[i-1][j]<=f[i][j-1])
                        f[i][j]=f[i][j-1],way[i][j]=1;
                    else
                        f[i][j]=f[i-1][j],way[i][j]=2;
        for(int i=lena,j=lenb;i>0 && j>0;)
        {
            if(way[i][j]==0)
            {
                chosen[i]=j;
                i--,j--;
                continue;
            }
            else if(way[i][j]==1)
                j--;
            else
                i--;
        }
        for(int i=1,j=1;i<=lena;i++)
        {
            if(chosen[i]>=j)
                for(;j<=chosen[i];j++)
                    printf("%c",b[j]);
            else
                printf("%c",a[i]);
            if(i==lena && j<=lenb)
                for(;j<=lenb;j++)
                    printf("%c",b[j]);
        }
        printf("\n");
    }
}