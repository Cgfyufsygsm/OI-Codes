#include <cstdio>

int main()
{
    int m;
    scanf("%d",&m);
    int sum=1;
    for(int i=0,j=1;i<j&&i<m/2+1;)
    {
        if(sum<m)
            sum+=++j;
        else if(sum>m)
            sum-=i++;
        else if(sum==m)
            printf("%d %d\n",i,j),sum-=i++;
    }
    return 0;
}