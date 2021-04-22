#include <cstdio>
#include <cctype>

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

const int maxn=5e4+5;
int n,k,bin[maxn*3],sum;

int find(int x)
{
    return bin[x]==x?x:bin[x]=find(bin[x]);
}

void uni(int x,int y)
{
    bin[find(x)]=find(y);
}

bool query(int x,int y)
{
    return find(x)==find(y);
}

int main()
{
    n=read(),k=read();
    int s,x,y;
    for(int i=1;i<=3*n;i++)
        bin[i]=i;
    while(k--)
    {
        s=read(),x=read(),y=read();
        if(x>n || y>n)
        {
            sum++;
            continue;
        }
        if(s==1)
        {
            if(query(x,y+n) || query(x+n,y))
            {
                sum++;
                continue;
            }
            uni(x,y);
            uni(x+n,y+n);
            uni(x+n+n,y+n+n);
        }
        else if(s==2)
        {
            if(query(x,y) || query(x,y+n))
            {
                sum++;
                continue;
            }
            uni(x+n,y);
            uni(x+n+n,y+n);
            uni(x,y+n+n);
        }
    }
    printf("%d\n",sum);
    return 0;
}