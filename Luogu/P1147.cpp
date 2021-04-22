#include <cstdio>
#include <cmath>

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=n;i>1;i--)//枚举项数
    {
        if(((!(n%i) && i&1) || (fabs((n/(double)i)-(n/i)-0.5)<1e-5)) && n/(double)i-i/2.0>0)
        {
            if(fabs((n/(double)i)-(n/i)-0.5)<1e-5)//偶数项
                printf("%d %d\n",n/i-i/2+1,n/i+i/2);
            else
                printf("%d %d\n",n/i-i/2,n/i+i/2);//奇数项
        }
    }
    return 0;
}