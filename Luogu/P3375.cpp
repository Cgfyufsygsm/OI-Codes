#include <cstdio>
#include <cstring>

const int maxn=1e6+5;
char s[maxn],p[maxn];
int next[maxn],lens,lenp;

void get_next()
{
    int i=0,j;
    next[0]=j=-1;
    while(i<lenp)
    {
        if(j==-1 || p[i]==p[j])
            next[++i]=++j;
        else j=next[j];
    }
    return;
}

void kmp()
{
    int i=0,j=0;
    while(i<lens)
    {
        if(j==-1 || s[i]==p[j])
            ++i,++j;
        else
            j=next[j];
        if(j==lenp)
            printf("%d\n",i-j+1),j=next[j];
    }
}

int main()
{
    scanf("%s",s);
    scanf("%s",p);
    lens=strlen(s);lenp=strlen(p);
    get_next();
    kmp();
    for(int i=1;i<=lenp;i++)
        printf("%d ",next[i]);
    return 0;
}