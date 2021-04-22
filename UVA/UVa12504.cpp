#include <iostream>
#include <string>
#include <map>
#include <set>
//#include <cstdio>
using namespace std;

typedef set<string> Set;
typedef map<string, string> Map;

void proc(string &, Map &, Set &);
void cmp(Map &, Map &, Set &, Set &);
void print(Set &, char);

int main()
{
    ios::sync_with_stdio(false);
    //freopen("1.in","r",stdin);
    int t;
    cin >> t;
    while (t--)
    {
        string dict1, dict2;
        cin >> dict1 >> dict2;
        Set s1, s2;
        Map m1, m2;
        proc(dict1, m1, s1);
        proc(dict2, m2, s2);
        cmp(m1, m2, s1, s2);
    }
    return 0;
}

void proc(string &dict, Map &m, Set &s)
{
    string key, val;
    for (string::iterator it = dict.begin(); it != dict.end(); it++)
    {
        if (isalpha(*it))
            key = key + (*it);
        if (isdigit(*it))
            val = val + (*it);
        if (*it == '}')
        {
            if (key != "" && val != "")
            {
                //cout<<"Key:"<<key<<" value:"<<val<<endl;
                m[key] = val;
                s.insert(key);
            }
            break;
        }
        if (*it == ',')
        {
            m[key] = val;
            s.insert(key);
            //cout<<"Key:"<<key<<" value:"<<val<<endl;
            key.clear();
            val.clear();
        }
    }
    return;
}

void cmp(Map &m1, Map &m2, Set &s1, Set &s2)
{
    Set added, removed, changed;
    for (Set::iterator it = s1.begin(); it != s1.end(); it++)
    {
        if (!s2.count(*it))
            removed.insert(*it);
        else
        {
            if (m2[*it] != m1[*it])
                changed.insert(*it);
        }
    }
    for (Set::iterator it = s2.begin(); it != s2.end(); it++)
    {
        if (!s1.count(*it))
            added.insert(*it);
    }
    print(added, '+');
    print(removed, '-');
    print(changed, '*');
    if (added.empty() && removed.empty() && changed.empty())
        cout << "No changes" << endl;
    cout << endl;
}

void print(Set &s, char mode)
{
    if (s.empty())
        return;
    cout << mode;
    for (Set::iterator it = s.begin(); it != s.end(); it++)
    {
        cout << *it;
        if (it != --s.end())
            cout << ',';
    }
    cout << endl;
    return;
}