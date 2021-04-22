#include<iostream>
#include<queue>
#include<string>
#include<map>
using namespace std;
string a,b;
string b4[7],af[7];
map<string,int> map1;
int l=1;
struct node
{
    string str;
    int step;
};
queue<node> q;
void bfs();
int main()
{
    cin>>a>>b;
    while(cin>>b4[l]>>af[l]) l++;
    l--;
    if(l==0&&a!=b) {cout<<"NO ANSWER!"<<endl;return 0;}
    q.push((node){a,0});
    bfs();
    return 0;
}
void bfs()
{
    string s,ss;
    while(!q.empty()&&q.front().step<=10)
    {
        if(q.front().str==b)
        {
            cout<<q.front().step<<endl;
            return;
        }
        if (map1[q.front().str]==1)
        {
            q.pop();
            continue;
        }
        map1[q.front().str]=1;
        for(int i=1;i<=l;i++)
        {
            s=q.front().str;
            for(;;)
            {
                int m=s.find(b4[i]);
                if(m==-1) break;
                ss=q.front().str;
                ss.replace(m,b4[i].size(),af[i]);
                q.push((node){ss,q.front().step+1});
                s[m]='~';
            }
        }
        q.pop();
    }
    cout<<"NO ANSWER!"<<endl;
    return;
}