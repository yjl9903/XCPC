#include<cstdio>
#include<cmath>
#include<algorithm>
#include <iostream>
#ifdef XLor
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define N 110
using namespace std;
int n,l,S,i,j,k,tot,son[N][10],v[N],fail[N],q[N],fin[N];
char s[N];double t,p[N],a[N][N],ans[N];
int ins(){
  scanf("%s",s);
  for(int x=0,i=0,w;i<l;i++){
    if(!son[x][w=s[i]-'A'])son[x][w]=++tot;x=son[x][w];
    if(i==l-1)return v[x]=1,x;
  }
}
void make(){
  int h=1,t=0,i,j,x;fail[0]=-1;
  for(i=0;i<S;i++)if(son[0][i])q[++t]=son[0][i];
  while(h<=t)for(x=q[h++],i=0;i<S;i++)if(son[x][i])fail[q[++t]=son[x][i]]=son[fail[x]][i];else son[x][i]=son[fail[x]][i];
}
int main(){
  scanf("%d%d%d",&n,&l,&S);
  for(i=0;i<S;i++)scanf("%lf%lf",&p[i],&t),p[i]/=t;
  for(i=0;i<n;i++)fin[i]=ins();
  make();
  for(i=0;i<=tot;i++)a[i+1][i+1]=-1;
  for(i=0;i<=tot;i++)if(!v[i])for(j=0;j<S;j++)a[son[i][j]+1][i+1]+=p[j];
  for(a[1][tot+2]=1,i=0;i<=tot;i++)if(v[i])a[1][i+1]=1;else a[1][i+1]=0;
  for (int i = 1; i <= tot + 1; i++) {
    for (int j = 1; j <= tot + 2; j++) {
      printf("%3.2lf ", a[i][j]);
    }
    cout << endl;
  }
  for(tot++,i=1;i<=tot;i++){
    for(k=i,j=i+1;j<=tot;j++)if(fabs(a[j][i])>fabs(a[k][i]))k=j;
    if(k!=i)for(j=i;j<=tot+1;j++)swap(a[i][j],a[k][j]);
    for(j=i+1;j<=tot;j++)for(t=a[j][i]/a[i][i],k=i;k<=tot+1;k++)a[j][k]-=a[i][k]*t;
  }
  for(ans[tot]=a[tot][tot+1]/a[tot][tot],i=tot-1;i;i--){
    for(ans[i]=a[i][tot+1],j=tot;j>i;j--)ans[i]-=ans[j]*a[i][j];
    ans[i]/=a[i][i];
  }
  for(i=0;i<n;i++)if(ans[fin[i]+1]>0)printf("%.2f\n",ans[fin[i]+1]);else puts("0.00");
  return 0;
}