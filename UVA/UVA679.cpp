#include <cstdio>

int main()
{
    int D,I,l;
    scanf("%d",&l);
    while(l--)
    {
        scanf("%d %d",&D,&I);
        int k=1;
        for(int i=1;i<D;i++)
        {
            k<<=1;
            if(!(I&1))
                k|=1;
            else
                I+=1;
            I>>=1;
        }
        printf("%d\n",k);
    }
    return 0;
}