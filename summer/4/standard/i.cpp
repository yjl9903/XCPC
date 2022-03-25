/*
    f[i]:节点i周围不同颜色数
    对于树: ans=sigma(f[i])-(n-1)
    对于环：ans=sigma(f[i])-n
        环上只有一种颜色 ans=sigma(f[i])-(n-1)
    set.count对于相同数复杂度线性
    用find吧以后都
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <set>
#include <map>
#define MP      make_pair
using namespace std;
const int nmax=2e5+5;
const int mmax=4e5+5;
typedef pair<int,int> P;
map< P,int > mp;
set<int> node[nmax];
multiset<int> mulnode[nmax];
multiset <int> cir_e;
set<int> ee;

int n,m;

struct Edge{
    int u,v,w,nex;
    Edge(){}
    Edge(int u,int v,int w,int nex):u(u),v(v),w(w),nex(nex){}
};
Edge e[mmax];
bool flag;
int tag[nmax];
int etot,head[nmax],pre_n[nmax],pre_e[nmax],vis[nmax];

void Addedge(int u,int v,int w);
void dfs(int now,int pa);
void init();


int main(){
    int t,cas=1,u,v,w;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&m);
        init();
        for(int i=1;i<=n;i++){
            scanf("%d%d%d",&u,&v,&w);
            mp[MP(u,v)]=w;
            mp[MP(v,u)]=w;
            node[u].insert(w);
            mulnode[u].insert(w);
            node[v].insert(w);
            mulnode[v].insert(w);
            Addedge(u,v,w);
        }

        dfs(1,1);
        int tot=0,esiz=ee.size();
        for(int i=1;i<=n;i++)
            tot+=node[i].size();
        tot-=n;

        printf("Case #%d:\n",cas++);
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            int lastw=mp[MP(u,v)];
            if(lastw==w){
                if(esiz==1)printf("%d\n",tot+1);
                else printf("%d\n",tot);
                continue;
            }
            //对点删边
            mulnode[u].erase(mulnode[u].find(lastw));
            if(mulnode[u].find(lastw)==mulnode[u].end()){
                node[u].erase(lastw);--tot;
            }
            mulnode[v].erase(mulnode[v].find(lastw));
            if(mulnode[v].find(lastw)==mulnode[v].end()){
                node[v].erase(lastw);--tot;
            }

            //对点加边
            mulnode[u].insert(w);
            if(node[u].find(w)==node[u].end()){
                node[u].insert(w);++tot;
            }
            mulnode[v].insert(w);
            if(node[v].find(w)==node[v].end()){
                node[v].insert(w);++tot;
            }

            //对环操作
            if(tag[u]&&tag[v]){
                //先删
                cir_e.erase(cir_e.find(lastw));
                if(cir_e.find(lastw)==cir_e.end()){
                        ee.erase(lastw);
                        esiz--;
                }
                //后加
                if(cir_e.find(w)==cir_e.end()){
                        ee.insert(w);
                        esiz++;
                }
                cir_e.insert(w);
            }

            if(esiz==1)printf("%d\n",tot+1);
            else printf("%d\n",tot);

            mp[P(u,v)]=w;
            mp[P(v,u)]=w;
        }

    }
    return 0;
}

void init(){
    flag=false;
    etot=0;
    for(int i=1;i<=n;i++){
        tag[i]=0;
        vis[i]=0;
        head[i]=-1;
        node[i].clear();
        mulnode[i].clear();
    }
    cir_e.clear();
    ee.clear();
    mp.clear();
}

void Addedge(int u,int v,int w){
    e[++etot]=Edge(u,v,w,head[u]);
    head[u]=etot;
    e[++etot]=Edge(v,u,w,head[v]);
    head[v]=etot;
}

void dfs(int now,int pa){
    if(flag)return;
    vis[now]=1;
    for(int i=head[now];i!=-1;i=e[i].nex){
        int to=e[i].v;
        if(to==pa)continue;
        if(vis[to]==0){
            pre_n[to]=now;
            pre_e[to]=e[i].w;
            dfs(to,now);
        }
        else{
            int ok=now;
            tag[to]=1;
            cir_e.insert(e[i].w);
            ee.insert(e[i].w);
            while(ok!=to){
                tag[ok]=1;
                cir_e.insert(pre_e[ok]);
                ee.insert(pre_e[ok]);
                ok=pre_n[ok];
            }
            flag=true;
        }
        if(flag)return;
    }
}
