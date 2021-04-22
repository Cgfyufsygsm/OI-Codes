#include <cstdio>
#include <iostream>
using namespace std;

int main()
{
    int A,B,C;
    cin>>A>>B>>C;
    if(B%A==0&&C%A==0) {B/=A;C/=A;A=1;}
    int cnt=0;
    for(int abc=111;abc<=999;abc++)
    {
        if(abc%A!=0) continue;
        int def=abc/A*B,ghi=abc/A*C;
        if(def>999||ghi>999) break;
        int a=abc/100,b=(abc/10)%10,c=abc%10;
        int d=def/100,e=(def/10)%10,f=def%10;
        int g=ghi/100,h=(ghi/10)%10,i=ghi%10;
        if (a == b || a == c || a == d || a == e || a == f || a == g || a == h || a == i || b == c || b == d || b == e || b == f || b == g || b == h || b == i || c == d || c == e || c == f || c == g || c == h || c == i || d == e || d == f || d == g || d == h || d == i || e == f || e == g || e == h || e == i || f == g || f == h || f == i || g == h || g == i || h == i ||a==0||b==0||c==0||d==0||e==0||f==0||g==0||h==0||i==0)
            continue;
        cout<<abc<<" "<<def<<" "<<ghi<<endl;
        cnt++;
    }
    if(cnt==0)
        cout<<"No!!!"<<endl;
    return 0;
}