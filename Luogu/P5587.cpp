#include<iostream>
#include<string>
#include <cmath>
using namespace std;
string input[1200],output[1200];

string chuli(string str)
{
	string res;
	for(int i=0;i<str.length();i++)
	{
		if(str[i]!='<') res.push_back(str[i]);
		else if(res.length()!=0) res.pop_back();
	}
	return res;
}

int main()
{
	int i=-1;
	while(true)
	{
		i++;
		getline(cin,input[i]);
		if(input[i]=="EOF")
		{
			i--;
			break;
		}
		input[i]=chuli(input[i]);
	}
	int j=-1;
	while(true)
	{
		j++;
		getline(cin,output[j]);
		if(output[j]=="EOF")
		{
			j--;
			break;
		}
		output[j]=chuli(output[j]);
	}
	double T;
	cin>>T;
	/*for(int k=0;k<=i;k++)
	{
		cout<<input[k]<<endl;
	}
	for(int k=0;k<=j;k++)
	{
		cout<<output[k]<<endl;
	}*/
	int cnt=0;
	for(int k=0;k<=min(i,j);k++)
	{
		string a(input[k]);
		string b(output[k]);
		int tmp=0;
		for(int l=0;l<min(a.length(),b.length());l++)
		{
			if(a[l]==b[l]) 
				tmp++;
		}
		//cout<<tmp<<endl;
		cnt+=tmp;
	}
	double ans=(double)cnt/((double)T/60.0);
	cout<<floor(ans+0.5)<<endl;
	return 0;
}