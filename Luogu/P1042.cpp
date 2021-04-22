#include <cstdio>

int a[25*2500+5],n=0;
int f[2]={11,21};

inline int abs(int x)
{
    return x>=0?x:-x;
}

int main()
{
    char c;
    while(1)
    {
        c=getchar();
        if(c=='E')
            break;
        if(c=='W')
            a[++n]=1;
        if(c=='L')
            a[++n]=0;
    }
    for(int k=0;k<2;k++)
    {
        int tmp1=0,tmp2=0;
        for(int i=1;i<=n;i++)
        {
            if(a[i])
                tmp1++;
            else
                tmp2++;
            if((tmp1>=f[k] || tmp2>=f[k]) && abs(tmp1-tmp2)>=2)
            {
                printf("%d:%d\n",tmp1,tmp2);
                tmp1=tmp2=0;
            }
        }
        printf("%d:%d\n\n",tmp1,tmp2);
    }
    return 0;
}