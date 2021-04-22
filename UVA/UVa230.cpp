//UVA230 Borrowers
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cstdio>
#include <queue>

using namespace std;

struct book
{
    string title, author;
    friend bool operator>(const book &a, const book &b)
    {
        return a.author==b.author?a.title>b.title:a.author>b.author;
    }
    friend bool operator<(const book &a, const book &b)
    {
        return a.author==b.author?a.title<b.title:a.author<b.author;
    }
};
typedef vector<book> vct;
vct shelf;
map<string, string> list; //book to author
priority_queue<book,vct,greater<book> > ret;

void shelff();
void rett();

int main()
{
    //freopen("230.in","r",stdin);
    string inn;
    while (1)
    {
        getline(cin, inn);
        if (inn == "END")
            break;
        int pos = (int)inn.find("by");
        string a = inn.substr(0, pos - 1);
        //cout<<a<<endl;
        string b = inn.substr(pos + 3);
        //cout<<b<<endl;
        shelf.push_back((book){a, b});
        list[a] = b;
        //shelff();
    }
    sort(shelf.begin(), shelf.end());
    //shelff();
    while (1)
    {
        getline(cin, inn);
        if (inn == "END")
            break;
        else if (inn[0]=='S')
        {
            while(!ret.empty())
            {
                book unreted=ret.top();
                ret.pop();
                if(unreted<*shelf.begin())
                {
                    cout<<"Put "<<unreted.title<<" first"<<endl;
                    shelf.insert(shelf.begin(),unreted);
                    continue;
                }
                else if(unreted>*prev(shelf.end()))
                {
                    cout<<"Put "<<unreted.title<<" after "<<(*prev(shelf.end())).title<<endl;
                    shelf.insert(shelf.end(),unreted);
                    continue;
                }
                else
                {
                    for(vct::iterator j=shelf.begin(),k=j+1;k!=shelf.end();j++,k++)
                    {
                        if(unreted>*j&&unreted<*k)
                        {
                            cout<<"Put "<<unreted.title<<" after "<<(*j).title<<endl;
                            shelf.insert(k,unreted);
                            break;
                        }
                    }
                    continue;
                }
            }
            cout<<"END"<<endl;
        }
        else
        {
            string title = inn.substr(7);
            //cout<<title<<endl;
            if (inn[0] == 'B')
            {
                for(vct::iterator i=shelf.begin();i!=shelf.end();i++)
                {
                    if((*i).title==title)
                    {
                        shelf.erase(i);
                        break;
                    }
                }
            }
            if (inn[0] == 'R')
            {
                ret.push((book){title,list[title]});
            }
        }
    }
    return 0;
}

void shelff()
{
    cout << "shelf:***************************" << endl;
    for (vct::iterator i = shelf.begin(); i != shelf.end(); i++)
    {
        cout << (*i).title << ' ' << (*i).author << endl;
    }
    cout << "********************************" << endl
         << endl;
}

void rett()
{
    cout << "ret:***************************" << endl;
    priority_queue<book,vct,greater<book> > q;
    while(!ret.empty())
    {
        book x=ret.top();
        ret.pop();
        q.push(x);
        cout << x.title << ' ' << x.author << endl;
    }
    ret=q;
    cout << "********************************" << endl
         << endl;
}

/*void shelve()
{
    sort(ret.begin(), ret.end());
    //rett();
    for (vct::iterator i = ret.begin(); i != ret.end(); i++)
    {
        book unreted = *i;
        //cout<<"unreted: "<<unreted.title<<" by "<<unreted.author<<endl;
        if (unreted < *shelf.begin())
        {
            cout << "Put " << unreted.title << " first" << endl;
            shelf.insert(shelf.begin(), unreted);
        }
        else if (unreted > *(shelf.end() - 1))
        {
            cout << "Put " << unreted.title << " after " << (*(shelf.end() - 1)).title << endl;
            shelf.push_back(unreted);
        }
        else
        {
            //cout<<"else"<<endl;
            for (vct::iterator k = shelf.begin() + 1, j = shelf.begin(); j != shelf.end(); j++, k++)
            {
                //cout<<"j: "<<(*j).title<<" by "<<(*j).author<<endl;
                //cout<<"k: "<<(*k).title<<" by "<<(*k).author<<endl;
                if (*j<unreted && * k> unreted)
                {
                    cout << "Put " << unreted.title << " after " << (*j).title << endl;
                    shelf.insert(j, unreted);
                    break;
                }
            }
        }
    }
    printf("END\n");
    ret.clear();
    return;
}*/