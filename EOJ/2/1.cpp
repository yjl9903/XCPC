

//DAG最长路
//以i为起点，不固定终点

int dp[maxn];
int choice[maxn];
int DP(int i)
{
    if (dp[i] > 0)
        return dp[i];
    for (int j = 0; j < G[i].size(); j++)
    {
        int v = G[i][j].v;
        int w = G[i][j].w;
        int temp = DP(v) + w;
        if (dp[i] < temp)
        {
            dp[i] = temp;
            choice[i] = v;
        }
    }
    return dp[i];
}
//固定终点T，以i为起点的最长路,dp[t]=0,当某点i的出度为0时,永远不可能到达t,dp[i]=-inf;
int vis[maxn] = {0};
int DP(int i)
{
    if (vis[i] == 1)
        return dp[i];
    vis[i] = 1;
    for (int j = 0; j < G[i].size(); j++)
    {
        int v = G[i][j].v;
        int w = G[i][j].w;
        int temp = DP(v) + w;
        if (dp[i] < temp)
        {
            dp[i] = temp;
            choice[i] = v;
        }
    }
    return dp[i];
}