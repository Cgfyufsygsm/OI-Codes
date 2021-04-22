#include <iostream>
#include <algorithm>
using namespace std;

class student
{
public:
    int num, chs, mth, eng, sum;
};

bool cmp(student a, student b)
{
    if (a.sum != b.sum)
        return a.sum > b.sum;
    else
    {
        if (a.chs != b.chs)
            return a.chs > b.chs;
        else
            return a.num < b.num;
    }
}

int main()
{
    int n;cin>>n;
    student s[n];
    for(int i=0;i<n;i++)
    {
        cin>>s[i].chs>>s[i].mth>>s[i].eng;
        s[i].sum=s[i].chs+s[i].mth+s[i].eng;
        s[i].num=i+1;
        //cout<<s[i].sum<<" ";
    }
    sort(s,s+n,cmp);
    for(int i=0;i<5;i++)
        cout<<s[i].num<<" "<<s[i].sum<<endl;
    return 0;
}