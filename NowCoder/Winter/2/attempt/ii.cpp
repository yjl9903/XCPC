#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define BIT 29
typedef long long LL;
const int N=2e5+5;

inline int lowbit(int x) {return x & -x;}

int read();
char IN[MAXIN],*SS=IN,*TT=IN;
struct Trie
{
    #define ls son[x][0]
    #define rs son[x][1]
    #define S N*31
    int n,A[N],tot,son[S][2],L[S],R[S];
    LL Ans;
    #undef S

    void Insert(int v,int id)
    {
        int x=0;
        for(int i=BIT; ~i; --i)
        {
            int c=v>>i&1;
            if(!son[x][c]) son[x][c]=++tot, L[tot]=R[tot]=id;
            x=son[x][c];
            L[x]=std::min(L[x],id), R[x]=std::max(R[x],id);
        }
    }
    int Query(int x,int v,int bit)
    {
        if(bit<0||L[x]==R[x]) return A[L[x]];//同样注意第0位还可以继续递归== 
        int c=v>>bit&1;
        return son[x][c]?Query(son[x][c],v,bit-1):(son[x][c^1]?Query(son[x][c^1],v,bit-1):0);
    }
    void DFS(int x,int bit)
    {
//      if(bit<0) return;
        if(!bit)
        {
            if(ls&&rs) Ans+=A[L[ls]]^A[L[rs]];//第0位还会有分叉 
            return;
        }
        if(ls&&rs)
        {
            int res=0x7fffffff;
            for(int i=L[ls],r=R[ls],p=rs; i<=r; ++i)
                res=std::min(res,lowbit(A[i]^Query(p,A[i],bit-1)));
            Ans+=res;
        }
        if(ls) DFS(ls,bit-1);
        if(rs) DFS(rs,bit-1);
    }
    void Solve()
    {
        n=read();
        for(int i=1; i<=n; ++i) A[i]=read();
        std::sort(A+1,A+1+n);
        for(int i=1; i<=n; ++i) Insert(A[i],i);
        DFS(0,BIT), printf("%I64d\n",Ans);
    }
}T;

inline int read()
{
    int now=0;register char c=gc();
    for(;!isdigit(c);c=gc());
    for(;isdigit(c);now=now*10+c-'0',c=gc());
    return now;
}

int main()
{
    T.Solve();
    return 0;
}