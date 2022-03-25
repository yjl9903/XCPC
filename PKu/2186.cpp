#include <iostream>
#include <stack>
#include <cstring>
#include <algorithm>
#define M(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn = 10010;//节点数
const int maxm = 50010;//边数

stack<int> s;
int x[maxm], y[maxm];
int N, M, cnt = 0, head[maxn], dfn[maxn], low[maxn], vis[maxn], index = 0;
int bel[maxn], len[maxn], mark[maxn], num = 0;
struct edge{int to, next;} f[maxm];

void add(int x, int y){
	f[++cnt].to = y, f[cnt].next = head[x], head[x] = cnt;
    //邻接表建图，边编号cnt从1开始，0号边为结束，edge.to表示边指向的节点，edge.next表示此节点的下一条边，head[x]表示此节点的第一条边
}

void tarjan(int u){
	dfn[u] = low[u] = ++index;
	vis[u] = 1;
	s.push(u);
	for (int i = head[u]; i; i = f[i].next){
		int v = f[i].to;
		if (!dfn[v]) //尚未访问
			tarjan(v), low[u] = min(low[u], low[v]);
		else if (vis[v]) //在栈中
			low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]){
		int v;
		do {
			v = s.top(); s.pop();
			bel[v] = num; //节点染色
            vis[v] = 0; //节点出栈
			len[num]++; //强联通分量长度更新
		} while (u != v);
		num++;
	}
}

int main(){
	cin >> N >> M;
	M(dfn, 0); M(vis, 0); M(head, 0); M(mark, 0);
	for (int i = 0; i < M; i++)
	{
		cin >> x[i] >> y[i];
		add(x[i], y[i]); //添加新边
	}
	
	for (int i = 1; i <= N; i++)
		if (!dfn[i]) //尚未访问过
			tarjan(i);
	
	int flag = 0, res = 0;
	for (int i = 0; i < M; i++)
		if (bel[x[i]] != bel[y[i]]) //边连接了两块不同的强联通分量
			mark[bel[x[i]]] = 1; //存在出度
	for (int i = 0; i < num; i++)
		if (!mark[i])
			res = len[i], flag++; //计算出度为0的强联通分量数
	if (flag == 1) //只有一个出度为0的强联通分量，输出该长度
		cout << res << endl;
	else
		cout << 0 << endl;
	return 0;
}