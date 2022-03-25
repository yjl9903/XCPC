#include <bits/stdc++.h>
using namespace std;
namespace fastIO{
	#define BUF_SIZE 100000
	#define OUT_SIZE 100000
	//fread->read
	bool IOerror=0;
//	inline char nc(){char ch=getchar();if(ch==-1)IOerror=1;return ch;} 
	inline char nc(){
		static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;
		if(p1==pend){
			p1=buf;pend=buf+fread(buf,1,BUF_SIZE,stdin);
			if(pend==p1){IOerror=1;return -1;}
		}
		return *p1++;
	}
	inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';}
	template<class T> inline bool read(T &x){
		bool sign=0;char ch=nc();x=0;
		for(;blank(ch);ch=nc());
		if(IOerror)return false;
		if(ch=='-')sign=1,ch=nc();
		for(;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
		if(sign)x=-x;
		return true;
	}
	inline bool read(double &x){
		bool sign=0;char ch=nc();x=0;
		for(;blank(ch);ch=nc());
		if(IOerror)return false;
		if(ch=='-')sign=1,ch=nc();
		for(;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
		if(ch=='.'){
			double tmp=1; ch=nc();
			for(;ch>='0'&&ch<='9';ch=nc())tmp/=10.0,x+=tmp*(ch-'0');
		}
		if(sign)x=-x;
		return true;
	}
	inline bool read(char *s){
		char ch=nc();
		for(;blank(ch);ch=nc());
		if(IOerror)return false;
		for(;!blank(ch)&&!IOerror;ch=nc())*s++=ch;
		*s=0;
		return true;
	}
	inline bool read(char &c){
		for(c=nc();blank(c);c=nc());
		if(IOerror){c=-1;return false;}
		return true; 
	}
	template<class T,class... U>bool read(T& h,U&... t){return read(h)&&read(t...);}
	#undef OUT_SIZE
	#undef BUF_SIZE
};
using namespace fastIO;
/************* debug begin *************/
string to_string(string s){return '"'+s+'"';}
string to_string(const char* s){return to_string((string)s);}
string to_string(const bool& b){return(b?"true":"false");}
template<class T>string to_string(T x){ostringstream sout;sout<<x;return sout.str();}
template<class A,class B>string to_string(pair<A,B> p){return "("+to_string(p.first)+", "+to_string(p.second)+")";}
template<class A>string to_string(const vector<A> v){
	int f=1;string res="{";for(const auto x:v){if(!f)res+= ", ";f=0;res+=to_string(x);}res+="}";
	return res;
}
void debug_out(){puts("");}
template<class T,class... U>void debug_out(const T& h,const U&... t){cout<<" "<<to_string(h);debug_out(t...);}
#ifdef tokitsukaze 
#define debug(...) cout<<"["<<#__VA_ARGS__<<"]:",debug_out(__VA_ARGS__);
#else
#define debug(...) 233;
#endif
/*************  debug end  *************/
#define mem(a,b) memset((a),(b),sizeof(a))
#define MP make_pair
#define pb push_back
#define fi first
#define se second
#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define sqr(x) (x)*(x)
using namespace __gnu_cxx;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;
typedef pair<int,ll> PIL;
typedef pair<ll,int> PLI;
typedef vector<int> VI;
typedef vector<ll> VL;
/************* define end  *************/
void read(int *x,int l,int r){for(int i=l;i<=r;i++) read(x[i]);}
void read(ll *x,int l,int r){for(int i=l;i<=r;i++) read(x[i]);}
void read(double *x,int l,int r){for(int i=l;i<=r;i++) read(x[i]);}
void println(VI x){for(int i=0;i<sz(x);i++) printf("%d%c",x[i]," \n"[i==sz(x)-1]);}
void println(VL x){for(int i=0;i<sz(x);i++) printf("%lld%c",x[i]," \n"[i==sz(x)-1]);}
void println(int *x,int l,int r){for(int i=l;i<=r;i++) printf("%d%c",x[i]," \n"[i==r]);}
void println(ll *x,int l,int r){for(int i=l;i<=r;i++) printf("%lld%c",x[i]," \n"[i==r]);}
/*************** IO end  ***************/
void go();
int main(){
	#ifdef tokitsukaze
		freopen("TEST.txt","r",stdin);
	#endif
	go();return 0;
}
const int INF=0x3f3f3f3f;
const ll LLINF=0x3f3f3f3f3f3f3f3fLL;
const double PI=acos(-1.0);
const double eps=1e-6;
const int MAX=2e5+10;
const ll mod=1e9+7;
/*********************************  head  *********************************/
struct AC_Automaton
{
	static const int K=26;//may need change
	int nex[MAX][K],fail[MAX],cnt[MAX],last[MAX],dep[MAX];
	int root,tot;
	inline int getid(char c)//may need change
	{
		return c-'a';
	}
	int newnode()
	{
		mem(nex[tot],0);
		fail[tot]=0;
		cnt[tot]=0;
		dep[tot]=0;
		return tot++;
	}
	void init()
	{
		tot=0;
		root=newnode();
	}
	void insert(char *s)
	{
		int len,now,i;
		len=strlen(s);
		now=root;
		for(i=0;i<len;i++)
		{
			int t=getid(s[i]);
			if(!nex[now][t])
			{
				nex[now][t]=newnode();
				dep[nex[now][t]]=i+1;
			}
			now=nex[now][t];
		}
		cnt[now]++;
	}
	void setfail()
	{
		int i,now;
		queue<int>q;
		for(i=0;i<K;i++)
		{
			if(nex[root][i]) q.push(nex[root][i]);
		}
		while(!q.empty())
		{
			now=q.front();
			q.pop();
			//suffix link
			if(cnt[fail[now]]) last[now]=fail[now];
			else last[now]=last[fail[now]];
			/*
			may need add something here:
			cnt[now]+=cnt[fail[now]];
			*/
			for(i=0;i<K;i++)
			{
				if(nex[now][i])
				{
					fail[nex[now][i]]=nex[fail[now]][i];
					q.push(nex[now][i]);
				}
				else nex[now][i]=nex[fail[now]][i];
			}
		}
	}
	ll be[MAX],en[MAX];
	void work(char *s)
	{
		int n,i,now,tmp;
		ll ans;
		n=strlen(s);
		now=root;
		for(i=0;i<=n;i++) be[i]=en[i]=0;
        int d = 0;
		for(i=0;i<n;i++)
		{
			now=nex[now][getid(s[i])];
			tmp=0;
			if(cnt[now]) tmp=now;
			else if(cnt[last[now]]) tmp=last[now];
			while(tmp)
			{
                d++;
				en[i]+=cnt[tmp];
				if(i-dep[tmp]+1>=0) be[i-dep[tmp]+1]+=cnt[tmp];
				tmp=last[tmp];
			}
		}
		ans=0;
		for(i=0;i<n-1;i++) ans+=en[i]*be[i+1];
		printf("%lld\n%d\n",ans, d);
	}
}ac;
char s[MAX],tmp[MAX];
void go()
{
	int i,q;
	while(read(s))
	{
		ac.init();
		read(q);
		while(q--)
		{
			read(tmp);
			ac.insert(tmp);
		}
		ac.setfail();
		ac.work(s);
	}
}