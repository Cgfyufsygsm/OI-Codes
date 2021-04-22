#include<iostream>
#include<string>
#include<cstdio>
using namespace std;
int main()
{
    char a[20],t1,t2;
    int sum=0;
    scanf("%c-%c%c%c-%c%c%c%c%c-%c",&a[1],&a[2],&a[3],&a[4],&a[5],&a[6],&a[7],&a[8],&a[9],&t1);
    for(int i=1;i<=9;i++)
    {
        sum+=(a[i]-'0')*i;
    }
    t2=sum%11+'0';
    if(t2=='0'+10)
        t2='X';
    if(t2==t1)
        cout<<"Right"<<endl;
    else
    {
        cout<<a[1]<<'-'<<a[2]<<a[3]<<a[4]<<'-'<<a[5]<<a[6]<<a[7]<<a[8]<<a[9]<<'-'<<t2<<endl;
    }
    return 0;

}