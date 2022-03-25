#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int max_n=1000005;
const int mod=1000000007;
inline int Add(int x,int y){
    return (x+=y)>=mod?x-mod:x;
}
inline int Sub(int x,int y){
    return (x-=y)>=0?x:x+mod;
}
inline int Mul(int x,int y){
    return 1ll*x*y%mod;
}
inline int Pow(int x,int y=mod-2){
    int res=1;
    while(y){
        if(y&1)res=1ll*res*x%mod;
        y>>=1;
        x=1ll*x*x%mod;
    }
    return res;
}
bool p[max_n];
int pri[max_n],cnt;
int d[max_n];
int divisor[max_n];
int f[max_n];
void sieve(int n){
    p[0]=p[1]=true;
    d[1]=1;divisor[1]=1;
    f[1]=1;
    for(int i=2;i<=n;i++){
        if(!p[i])pri[++cnt]=i,divisor[i]=i,d[i]=2,f[i]=Pow(i);
        for(int j=1;j<=cnt&&1ll*i*pri[j]<=n;j++){
            p[i*pri[j]]=true;
            f[i*pri[j]]=Mul(f[i],f[pri[j]]);
            if(i%pri[j]==0){
                divisor[i*pri[j]]=divisor[i]*pri[j];
                if(i==divisor[i])d[i*pri[j]]=d[i]+1;
                else d[i*pri[j]]=Mul(d[i/divisor[i]],d[divisor[i*pri[j]]]);
                break;
            }
            else{
                divisor[i*pri[j]]=pri[j];
                d[i*pri[j]]=Mul(d[i],d[pri[j]]);
            }
        }
    }
    for(int i=1;i<=n;i++)f[i]=Add(f[i-1],f[i]);
    for(int i=1;i<=n;i++)d[i]=Add(d[i-1],d[i]);
}
int T;
int n,m;
unordered_map<int,int> md;
int cal(int n){
    if(n<max_n)return d[n];
    if(md.count(n))return md[n];
    int res=0;
    for(int l=1,r;l<=n;l=r+1){
        r=n/(n/l);
        res=Add(res,Mul(n/l,r-l+1));
    }
    return md[n]=res;
}
int sum(int n){
    return 1ll*n*(n+1)/2%mod;
}
unordered_map<int,int> mp;
int S(int n){
    if(n<max_n)return f[n];
    if(mp.count(n))return mp[n];
    int res=cal(n);
    for(int l=2,r;l<=n;l=r+1){
        r=n/(n/l);
        res=Sub(res,Mul(S(n/l),Sub(sum(r),sum(l-1))));
    }
    return mp[n]=res;
}
int solve(int n,int m){
    if(n<=m)return 0;
    if(n==m+1)return Sub(n,1);
    int res=0;
    res=Add(res,Mul(3,Sub(S(n+1),S(m+2))));
    int t1=Sub(S(n+1),Pow(n+1)),t2=Sub(S(m+2),Pow(m+2));
    res=Sub(res,Mul(2,Sub(t1,t2)));
    res=Mul(res,1ll*(n+2)*(n+1)%mod);
    res=Add(res,n-1);
    return res;
}
int main(){
    sieve(max_n-1);
    scanf("%d%d",&n,&m);
    printf("%d\n",Sub(solve(n,m),solve(n-1,m)));
    return 0;
}