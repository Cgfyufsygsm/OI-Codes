#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
bool is_prime(int n)
{
    if(n==2) return 1;
    if(n%2==0) return 0;
    int t=sqrt(n)+1;
    for(int i=3;i<=t;i++)
    {
        if(n%i==0)
            return 0;
    }
    return 1;
}

int main()
{
    int n;cin>>n;
    for(int i=3;i<n;i+=2)
    {
        if(is_prime(i))
        {
            if(i+4==n)
            {
                cout<<"2 2 "<<i<<endl;
                return 0;
            }
        }
    }
    for(int i=3;i<20000;i+=2)
    {
        if(is_prime(i))
        {
            for(int j=3;j<20000;j+=2)
            {
                if(is_prime(j))
                {
                    for(int k=3;k<20000;k+=2)
                    {
                        if(is_prime(k))
                        {
                            if(i+j+k==n)
                            {
                                cout<<i<<" "<<j<<" "<<k<<endl;
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }
}