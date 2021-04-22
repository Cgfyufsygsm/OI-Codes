#include <cstdio>
#include <cstring>
#include <queue>

using std::queue;
using std::vector;

struct node
{
    bool have_value;
    int val;
    node *left,*right;
    node():have_value(false),left(NULL),right(NULL){}
};

const int maxn=258;
bool failed;
node* root;

inline node* newnode()
{
    return new node();
}

void remove_tree(node *now)
{
    if(now==NULL)
        return;
    remove_tree(now->left);
    remove_tree(now->right);
    delete now;
}

void addnode(int v,char *s)
{
    int n=strlen(s);
    node *u=root;
    for(int i=0;i<n;i++)
    {
        if(s[i]=='L')
        {
            if(u->left==NULL)
                u->left=newnode();
            u=u->left;
        }
        else if(s[i]=='R')
        {
            if(u->right==NULL)
                u->right=newnode();
            u=u->right;
        }
    }
    if(u->have_value)
        failed=true;
    u->val=v;
    u->have_value=true;
    return;
}

char s[maxn];

bool read()
{
    failed=false;
    remove_tree(root);
    root=newnode();
    while(1)
    {
        if(scanf("%s",s)!=1)
            return false;
        if(!strcmp(s,"()"))
            break;
        int v;
        sscanf(&s[1],"%d",&v);
        addnode(v,strchr(s,',')+1);
    }
    return true;
}

bool bfs(vector<int> &ans)
{
    queue<node*> q;
    ans.clear();
    q.push(root);
    while(!q.empty())
    {
        node *now=q.front();
        q.pop();
        if(!now->have_value)
            return false;
        ans.push_back(now->val);
        if(now->left!=NULL)
            q.push(now->left);
        if(now->right!=NULL)
            q.push(now->right);
    }
    return true;
}

void print(vector<int> &ans)
{
    for(int i=0;i<ans.size()-1;i++)
        printf("%d ",ans[i]);
    printf("%d\n",ans[ans.size()-1]);
    return;
}

int main()
{
    vector<int> ans;
    while(read())
    {
        if(bfs(ans) && (!failed))
            print(ans);
        else
            printf("not complete\n");
    }
    return 0;
}