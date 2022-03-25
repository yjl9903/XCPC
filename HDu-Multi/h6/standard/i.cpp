#include <bits/stdc++.h>
using namespace std;
typedef double db;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pw(x) (1ll << (x))
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);i++)
#define per(i,l,r) for(int i=(r)-1;i>=(l);i--)
#define dd(x) cout << #x << " = " << (x) << ", "
#define de(x) cout << #x << " = " << (x) << "\n"
#define endl "\n"

//-----
const int N=100005;
pii g[N];
int ans[N],vis[N];
void dfs(int p)
{
    vis[p]=1;
    if(g[p].second)
    {
        if(!vis[g[p].first])
        {
            dfs(g[p].first);
            ans[p] = ans[g[p].first];
            if(ans[p] == p) ans[p] = -1;
            // if(ans[g[p].fi]==-1)ans[a]=-1;
            // else if(a==ans[g[p].fi])ans[a]=-1;
            // else ans[p]=ans[g[p].fi];
        }
        else if(!ans[g[p].first]) ans[p] = N;
        else
        {
            ans[p] = ans[g[p].first];
            if(ans[p] == p) ans[p] = -1;
        }
    }
    else ans[p] = g[p].first;
}
int main()
{
    // std::ios::sync_with_stdio(false);
    // std::cin.tie(0);
    int T; scanf("%d", &T);
    while(T--)
    {
        int n; scanf("%d", &n);
        // rep(i,1,n+1)ans[i]=0,vis[i]=0;
        rep(i,1,n+1)
        {
            // int x;string s;cin>>x>>s;
            int x; char s[20]; scanf("%d%s", &x, s);
            if(s[0]=='v')g[i]=mp(x,1);
            else if (s[0] == 'w') g[i]=mp(x,0);
        }
        memset(ans, 0, sizeof ans); memset(vis, 0, sizeof vis);
        rep(i,1,n+1)if(!vis[i])dfs(i);
        int res=0;
        rep(i,1,n+1) res += ans[i] == -1;
        //rep(i,1,n+1)cout<<ans[i]<<endl;
        cout<<"0 "<<res<<endl;
    }
    return 0;
}