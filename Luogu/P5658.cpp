#include <cstdio>
#include <cstring>

typedef long long ll;
const int maxn = 5e5 + 5;
char str[maxn];
int n, fa[maxn];
int head[maxn], to[maxn], next[maxn], cnt;
int s[maxn], top;
ll ans, lst[maxn], sum[maxn];

void add(int u, int v)
{
	to[++cnt] = v;
	next[cnt] = head[u];
	head[u] = cnt;
	return;
}

void dfs(int u)
{
	int tmp = 0;
	if (str[u] == ')' && top) lst[u] = lst[fa[tmp = s[top--]]] + 1;
	else if (str[u] == '(') s[++top] = u;
	sum[u] = sum[fa[u]] + lst[u];
	for (int i = head[u]; i; i = next[i]) dfs(to[i]);
	if (tmp) s[++top] = tmp;
	else if (top) --top;
	return;
}

int main()
{
	scanf("%d", &n);
	scanf("%s", str + 1);
	for (int i = 2; i <= n; i++)
	{
		scanf("%d", fa + i);
		add(fa[i], i);
	}
	dfs(1);
	for (ll i = 1; i <= n; i++)
		ans ^= (sum[i] * i);
	printf("%lld\n", ans);
	return 0;
}
