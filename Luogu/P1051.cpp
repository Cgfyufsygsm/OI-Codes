#include <iostream>
#include <string>
using namespace std;

int main()
{
    int N;
    cin >> N;
    string maxname;
    int max=-1,sum=0;
    for(int i=1;i<=N;i++)
    {
        char ganbu,west;
        string name;
        int qimo,banji,paper;
        cin>>name>>qimo>>banji>>ganbu>>west>>paper;
        int money=0;
        if(qimo>80&&paper>0) money+=8000;
        if(qimo>85&&banji>80) money+=4000;
        if(qimo>90) money+=2000;
        if(qimo>85&&west=='Y') money+=1000;
        if(banji>80&&ganbu=='Y') money+=850;
        if(money>max)
        {
            max=money;
            maxname=name;
        }
        sum+=money;
    }
    cout<<maxname<<endl<<max<<endl<<sum<<endl;
    return 0;
}