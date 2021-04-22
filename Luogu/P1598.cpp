#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;
string text1, text2, text3, text4, text;
int main()
{
    getline(cin, text1);
    getline(cin, text2);
    getline(cin, text3);
    getline(cin, text4);
    text = text1 + text2 + text3 + text4;
    //cout << text;
    int cnt[26];
    memset(cnt,0,sizeof(cnt));
    for(char i='A';i<='Z';i++)
    {
        for(int j=0;j<text.length();j++)
        {
            if(text[j]==i)
                cnt[i-'A']++;
        }
    }
    int maxn=*max_element(cnt,cnt+26);
    for(int i=maxn;i>0;i--)
    {
        for(int j=0;j<26;j++)
        {
            if(cnt[j]>=i)
                cout<<"* ";
            else
                cout<<"  ";
        }
        cout<<endl;
    }
    //cout<<cnt[0]<<endl;
    cout<<"A B C D E F G H I J K L M N O P Q R S T U V W X Y Z"<<endl;
}