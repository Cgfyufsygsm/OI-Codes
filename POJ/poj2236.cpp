#include <cstdio>
#include <cctype>
#include <set>

using std::set;

const int maxn=1005;
int n,d2;

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

struct Point
{
    int x,y;
}a[maxn];

int Dist2(Point a,Point b)
{
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}


int bin[maxn],dist2[maxn][maxn];
set<int> repaired;

int find(int x)
{
    return bin[x]==x?x:bin[x]=find(bin[x]);
}

void uni(int x,int y)
{
    if(find(x)!=find(y))
        bin[find(x)]=find(y);
    return;
}

bool query(int x,int y)
{
    return find(x)==find(y);
}

void repair(int x)
{
    for(set<int>::iterator i=repaired.begin();i!=repaired.end();i++)
    {
        int y=*i;
        if(dist2[x][y]<=d2)
            uni(x,y);
    }
    repaired.insert(x);
}

int main()
{
    n=read(),d2=read();
    d2*=d2;
    for(int i=1;i<=n;i++)
        a[i].x=read(),a[i].y=read(),bin[i]=i;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            dist2[i][j]=dist2[j][i]=Dist2(a[i],a[j]);
    char c;
    while(scanf("%c",&c)!=EOF)
    {
        int x,y;
        if(c=='O')
        {
            x=read();
            repair(x);
        }
        if(c=='S')
        {
            x=read(),y=read();
            printf("%s\n",query(x,y)?"SUCCESS":"FAIL");
        }
    }
    return 0;
}