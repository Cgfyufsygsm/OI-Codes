#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#define maxn 26
using namespace std;

vector<int> pile[maxn];

int n;

void find_block(int,int&,int&);
void clear_above(int,int);
void pile_onto(int,int,int);
void print();

int main()
{
    cin>>n;
    string s1,s2;
    int a,b;
    //print();
    for(int i=0;i<n;i++) pile[i].push_back(i);
    //print();
    while(cin>>s1>>a>>s2>>b)
    {
        int pa,pb,ha,hb;
        find_block(a,pa,ha);
        //printf("%d is found in pile %d at pos %d\n",a,pa,ha);
        find_block(b,pb,hb);
        //printf("%d is found in pile %d at pos %d\n",b,pb,hb);
        if(pa==pb) continue;
        if(s2=="onto") clear_above(pb,hb);
        if(s1=="move") clear_above(pa,ha);
        pile_onto(pa,ha,pb);
        //print();
    }
    print();
    return 0;
}

void find_block(int a,int &p,int &h)
{
    for(p=0;p<n;p++)
    {
        for(h=0;h<pile[p].size();h++)
        {
            if(pile[p][h]==a) return;
        }
    }
}

void clear_above(int p,int h)
{
    for(int i=h+1;i<pile[p].size();i++)
    {
        int b=pile[p][i];
        pile[b].push_back(b);
    }
    pile[p].resize(h+1);
}

void pile_onto(int p,int h,int p2)
{
    for(int i=h;i<pile[p].size();i++)
        pile[p2].push_back(pile[p][i]);
    pile[p].resize(h);
    return;
}

void print()
{
    for(int i=0;i<n;i++)
    {
        printf("%d:",i);
        for(int j=0;j<pile[i].size();j++)
            printf(" %d",pile[i][j]);
        cout<<endl;
    }
}