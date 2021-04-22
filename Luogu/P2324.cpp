#include <cstdio>
#include <algorithm>
#include <cctype>
using namespace std;

const int tar[5][5]={
    {1,1,1,1,1},
    {0,1,1,1,1},
    {0,0,2,1,1},
    {0,0,0,0,1},
    {0,0,0,0,0}
};
int board[5][5],idt;
const int fx[8]={1,1,-1,-1,2,2,-2,-2},fy[8]={2,-2,2,-2,1,-1,1,-1};

int h()
{
    int res=0;
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            if(board[i][j]!=tar[i][j]) res++;
    return res;
}

bool dfs(int x,int y,int d)
{
    if(d+h()>idt+1) return false;
    if(!h()) return true;
    for(int k=0;k<8;k++)
    {
        int x1=x+fx[k],y1=y+fy[k];
        if(x1>4||x1<0||y1>4||y1<0) continue;
        swap(board[x][y],board[x1][y1]);
        if(dfs(x1,y1,d+1)) return true;
        swap(board[x][y],board[x1][y1]);
    }
    return false;
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int x0,y0;
        for(int i=0;i<5;i++)
        {
            char s[5];
            scanf("%s",s);
            for(int j=0;j<5;j++)
            {
                if(isdigit(s[j])) board[i][j]=s[j]-'0';
                if(s[j]=='*')
                {
                    board[i][j]=2;
                    x0=i;
                    y0=j;
                }
            }
        }
        bool flag=0;
        for(idt=1;idt<=15;idt++)
        {
            if(dfs(x0,y0,0)){flag=1;break;}
        }
        printf("%d\n",flag?idt:-1);
    }
    return 0;
}