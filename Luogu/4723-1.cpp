#include<bits/stdc++.h>
#ifdef XLor
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ri register int
using namespace std;
const int rlen=1<<18|1;
inline char gc(){
	static char buf[rlen],*ib,*ob;
	(ib==ob)&&(ob=(ib=buf)+fread(buf,1,rlen,stdin));
	return ib==ob?-1:*ib++;
}
inline int read(){
	int ans=0;
	char ch=gc();
	bool f=1;
	while(!isdigit(ch))f^=ch=='-',ch=gc();
	while(isdigit(ch))ans=((ans<<2)+ans<<1)+(ch^48),ch=gc();
	return f?ans:-ans;
}
typedef vector<int> poly;
typedef long long ll;
const int mod=1e9+7;
inline int add(int a,int b){return (a+=b)>=mod?a-mod:a;}
inline int dec(int a,int b){return (a-=b)<0?a+mod:a;}
inline int mul(int a,int b){return (ll)a*b%mod;}
inline void Add(int&a,int b){(a+=b)>=mod?a-=mod:a;}
inline void Dec(int&a,int b){(a-=b)<0?a+=mod:a;}
inline void Mul(int&a,int b){a=(ll)a*b%mod;}
inline int ksm(int a,int p){int ret=1;for(;p;p>>=1,Mul(a,a))if(p&1)Mul(ret,a);return ret;}
inline poly operator-(poly a,poly b){
	int n=a.size(),m=b.size();
	poly c(max(n,m));
	for(ri i=0;i<n;++i)Add(c[i],a[i]);
	for(ri i=0;i<m;++i)Dec(c[i],b[i]);
	return c;
}
inline poly operator*(poly a,poly b){
	int n=a.size(),m=b.size(),t=n+m-1;
	poly c(t);
	for(ri i=0;i<n;++i)for(ri j=0;j<m;++j)Add(c[i+j],mul(a[i],b[j]));
	return c;
}
inline poly operator%(poly a,poly b){
	int n=a.size()-1,m=b.size()-1;
	if(n<m)return a;
	for(ri t,i=n;i>=m;--i){
		t=a[i];
		for(ri j=i,tt=m;~tt;--tt,--j)Dec(a[j],mul(b[tt],t));
	}
	a.resize(m),a;
  return a;
}
const int N=2005;
inline int calc(int*coe,int*a,int k,int n){
	if(n<k)return a[n];
	poly md(k+1),f(2),g(1,1);
	f[1]=md[k]=1;
	for(ri i=1;i<=k;++i)md[k-i]=coe[i]?mod-coe[i]:0;
	for(;n;n>>=1,f=f*f%md)if(n&1)g=g*f%md;
  for (int i = 0; i < k; i++) {
    dbg(i, g[i]);
  }
	int ret=0;
	for(ri i=0;i<k;++i)Add(ret,mul(g[i],a[i]));
  dbg(ret);
	return ret;
}
int n,k,a[N],b[N];
int main(){
	n=read(),k=read();
	for(ri i=1;i<=k;++i)a[i]=read(),a[i]<0?a[i]+=mod:a[i];
	for(ri i=0;i<k;++i)b[i]=read(),b[i]<0?b[i]+=mod:b[i];
	cout<<calc(a,b,k,n);
	return 0;
}