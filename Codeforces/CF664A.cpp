#include <iostream>
#include <string>
using namespace std;

bool cmp(string a,string b)//a<b时返回1，否则返回0
{
    if(a==b) return 0;
    return 1;
}

int main()
{
    string a,b;
    cin>>a>>b;
    if(cmp(a,b)) cout<<1<<endl;
    else cout<<a<<endl;
    return 0;
}