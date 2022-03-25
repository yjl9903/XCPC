#include<cstdio>
#include<map>
#include<cstring>
using namespace std;
#define lld %I64d
#define REP(i,k,n) for(int i=k;i<n;i++)
#define REPP(i,k,n) for(int i=k;i<=n;i++)
#define mst(a,k)  memset(a,k,sizeof(a))
#define LL long long
#define N 505
inline int read(){int s=0;char ch=getchar();for(; ch<'0'||ch>'9'; ch=getchar());for(; ch>='0'&&ch<='9'; ch=getchar())s=s*10+ch-'0';return s;}

int line[N][N];
int girl[N],used[N];
int spe,ask;
int l,r;
bool found(int x)
{
    for(int i=0; i<r; i++)
    {
        if(line[x][i]&&!used[i])
        {
            used[i]=1;
            if(girl[i]==0||found(girl[i]))
            {
                girl[i]=x;
                return 1;
            }
        }
    }
    return 0;
}
multimap<int,int> coder;
int main(){
    
    while(scanf("%d %d",&l,&r)!=EOF)
    {
    	mst(line,0);
    	mst(girl,0);
		REP(i,0,r)
		{
			spe=read();
			coder.insert(make_pair(spe,i));
		}
		REP(i,0,l)
		{
			int t=read();
			while(t--)
			{
				ask=read();
				map<int,int>::iterator begin,end,it;
				begin=coder.lower_bound(ask);
				end=coder.upper_bound(ask);
				for(it=begin;it!=end;it++)
				{
					line[i][it->second]=1;
					//printf("%d like %d\n",i,it->second);
				}
			}
		}
		int sum=0;
		REP(i,0,l)
		{
			mst(used,0);
			if(found(i))
			sum++;
		}
		printf("%d\n",sum);
	}
    
    return 0;
}