#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

vector<string> s;
map<string,bool> m;

int main()
{
    string str;
    while(cin>>str)
    {
        s.push_back(str);
        m[str]=1;
    }
    for(int i=0;i<s.size();i++)
    {
        for(int j=0;j<s[i].size();j++)
        {
            string a=s[i].substr(0,j);
            if(m[a])
            {
                string b=s[i].substr(j);
                if(m[b])
                {
                    cout<<s[i]<<endl;
                    break;
                }
            }
        }
    }
    return 0;
}