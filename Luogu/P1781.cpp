#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class president
{
public:
    int n;
    string score;
};

bool cmp(president a, president b)
{
    if (a.score.length() != b.score.length())
        return a.score.length() > b.score.length();
    for (int i = 0; i < a.score.length(); i++)
    {
        if (a.score[i] != b.score[i])
            return a.score[i] > b.score[i];
    }
    return a.n<b.n;
}

int main()
{
    int N;cin>>N;president p[N];
    for(int i=0;i<N;i++)
    {
        cin>>p[i].score;
        p[i].n=i+1;
    }
    sort(p,p+N,cmp);
    cout<<p[0].n<<endl<<p[0].score<<endl;
    return 0;
}