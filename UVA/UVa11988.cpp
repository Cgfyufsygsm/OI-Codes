#include <iostream>
#include <string>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    string str;
    while(cin>>str)
    {
        str=' '+str;
        int nxt[(int)str.size()];
        nxt[0]=0;
        int last,cur;
        last=cur=0;
        for(int i=1;i<str.size();i++)
        {
            char ch=str[i];
            if(ch=='[') cur=0;
            else if(ch==']') cur=last;
            else
            {
                nxt[i]=nxt[cur];
                nxt[cur]=i;
                if(cur==last) last=i;
                cur=i;
            }
        }
        for(int i=nxt[0];i!=0;i=nxt[i])
            cout<<str[i];
        cout<<endl;
    }
    return 0;
}