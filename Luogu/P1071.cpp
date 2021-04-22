#include<bits/stdc++.h>
using namespace std;
map<char,char> m0,m1;
char mingwen[1000],miwen[1000],target[1000];
int main()
{
    fgets(mingwen,10000,stdin);
    fgets(miwen,10000,stdin);
    fgets(target,10000,stdin);
    for(int i=0;i<strlen(miwen);i++)
    {
        if((m0.count(miwen[i]) && m0[miwen[i]]!=mingwen[i]) || (m1.count(mingwen[i]) && m1[mingwen[i]]!=miwen[i]))
        {
            cout<<"Failed"<<endl;
            return 0;
        }
        else
        {
            m0[miwen[i]]=mingwen[i];
            m1[mingwen[i]]=miwen[i];
        }
    }
    for(char i='A';i<='Z';i++)
    {
        if(!m1.count(i))
        {
            cout<<"Failed"<<endl;
            return 0;
        }
    }
    for(int i=0;i<strlen(target);i++)
    {
        if(target[i]!=' ')
            cout<<m1[target[i]];
    }
    return 0;
}