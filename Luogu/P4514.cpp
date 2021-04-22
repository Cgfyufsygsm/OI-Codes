#include <cstdio>
#define lowbit(x) (x&-x)

const int maxn=2058;
int f1[maxn][maxn],f2[maxn][maxn],f3[maxn][maxn],f4[maxn][maxn];
int n,m;

void add(int x,int y,int d)
{
    for(int i=x;i<=n;i+=lowbit(i))
        for(int j=y;j<=m;j+=lowbit(j))
            f1[i][j]+=d,
            f2[i][j]+=x*d,
            f3[i][j]+=y*d,
            f4[i][j]+=x*y*d;
    return;
}

int sum(int x,int y)
{
    int ans1=0,ans2=0,ans3=0,ans4=0;
    for(int i=x;i>0;i-=lowbit(i))
        for(int j=y;j>0;j-=lowbit(j))
            ans1+=f1[i][j],
            ans2+=f2[i][j],
            ans3+=f3[i][j],
            ans4+=f4[i][j];
    return ans1*(x+1)*(y+1)-ans2*(y+1)-ans3*(x+1)+ans4;
}

int main()
{
    scanf("%c %d %d\n",&n,&n,&m);
    char t;
    int a,b,c,d,x;
    while(scanf("%c",&t)!=EOF)
    {
        if(t=='L')
        {
            scanf("%d %d %d %d %d\n",&a,&b,&c,&d,&x);
            add(a,b,x),add(a,d+1,-x),add(c+1,b,-x),add(c+1,d+1,x);
        }
        else
        {
            scanf("%d %d %d %d\n",&a,&b,&c,&d);
            printf("%d\n",sum(c,d)-sum(a-1,d)-sum(c,b-1)+sum(a-1,b-1));
        }
    }
    return 0;
}