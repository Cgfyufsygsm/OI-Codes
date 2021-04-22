#include <cstdio>
#include <cstring>

char s[1024+5];
int buf[33][33];
int ans,p;

void draw(int x1,int y1,int w)
{
    char ch=s[p++];
    if(ch=='p')
    {
        draw(x1+w/2,y1    ,w/2);
        draw(x1    ,y1    ,w/2);
        draw(x1    ,y1+w/2,w/2);
        draw(x1+w/2,y1+w/2,w/2);
    }
    else if(ch=='f')
        for(int i=x1;i<x1+w;i++)
            for(int j=y1;j<y1+w;j++)
                if(!buf[i][j])
                    buf[i][j]=1,ans++;
    return;
}

int main()
{
    int n;
    scanf("%d",&n);
    while(n--)
    {
        ans=0;
        memset(buf,0,sizeof buf);
        scanf("%s",s);
        p=0;
        draw(1,1,32);
        p=0;
        scanf("%s",s);
        draw(1,1,32);
        printf("There are %d black pixels.\n",ans);
    }
    return 0;
}