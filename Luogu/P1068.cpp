#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
using std::sort;

struct vlt
{
    int k, s;
};

bool cmp(vlt p1, vlt p2)
{
    if (p1.s > p2.s)
    {
        return true;
    }
    else if (p1.s == p2.s)
    {
        if (p1.k < p2.k)
            return true;
        else
            return false;
    }
    else
        return false;
}

int main()
{
    int n, m;
    cin >> n >> m;
    m = floor(m * 1.5);
    struct vlt v[n], t;
    for (int i = 0; i < n; i++)
        cin >> v[i].k >> v[i].s;
    sort(v, v + n, cmp);
    int fenshuxian = v[m - 1].s;
    int renshu = m;
    for (int i = m; i < n; i++)
    {
        if (v[i].s == fenshuxian)
            renshu ++;
        else if (v[i].s < fenshuxian)
            break;
    }
    cout<<fenshuxian<<" "<<renshu<<endl;
    for(int i=0;i<renshu;i++)
        cout<<v[i].k<<" "<<v[i].s<<endl;
    return 0;
}