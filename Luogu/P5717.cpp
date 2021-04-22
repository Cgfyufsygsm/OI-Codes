#include <cstdio>
int a,b,c;

void swap(int&a,int&b)
{
    int t=a;a=b;b=t;
    return;
}

int main()
{
    scanf("%d %d %d",&a,&b,&c);
    if(a>b) swap(a,b);
    if(a>c) swap(a,c);
    if(b>c) swap(b,c);
    //printf("%d %d %d",a,b,c);
    if(a+b<=c)
    {
        printf("Not triangle\n");
        return 0;
    }
    int a1=a*a,b1=b*b,c1=c*c;
    if(a1+b1==c1) printf("Right triangle\n");
    else if(a1+b1<c1) printf("Obtuse triangle\n");
    else if(a1+b1>c1) printf("Acute triangle\n");
    if(a==b||a==c||b==c) printf("Isosceles triangle\n");
    if(a==b&&a==c&&b==c) printf("Equilateral triangle\n");
    return 0;
}