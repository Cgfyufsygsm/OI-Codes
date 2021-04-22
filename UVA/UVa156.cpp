#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
using namespace std;

vector<string> words;
map<string,int> cnt;

string sort(const string &s)
{
    string ans=s;
    for(string::iterator it=ans.begin();it!=ans.end();it++)
        *it=tolower(*it);
    sort(ans.begin(),ans.end());
    return ans;
}

int main()
{
    string s;
    while(cin>>s)
    {
        if(s=="#") break;
        words.push_back(s);
        string r=sort(s);
        if(!cnt.count(r)) cnt[r]=0;
        cnt[r]++;
    }
    vector<string> ans;
    for(int i=0;i<words.size();i++)
    {
        if(cnt[sort(words[i])]==1)
            ans.push_back(words[i]);
    }
    sort(ans.begin(),ans.end());
    for(int i=0;i<ans.size();i++)
    cout<<ans[i]<<endl;
    return 0;
}