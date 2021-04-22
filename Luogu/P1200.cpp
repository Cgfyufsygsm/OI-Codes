#include<iostream>
#include<cstring>
char a[10],b[10];
using namespace std;
int main()
{
    cin>>a>>b;
    int suma=1,sumb=1;
    for(int i=0;i<strlen(a);i++)
    {
        suma*=(a[i]-64);
    }
    for(int i=0;i<strlen(b);i++)
    {
        sumb*=(b[i]-64);
    }
    if(suma%47==sumb%47)
        cout<<"GO"<<endl;
    else
        cout<<"STAY"<<endl;
    return 0;
}