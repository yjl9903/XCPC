
// hdu 2815
// by utoppia
 
#include<cstdio>
#include<iostream>
#include<cstring>
#include<map>
#include<math.h>
using namespace std;
 
typedef long long ll;
 
ll phi(ll x){
    ll ret = x;
    for(int i=2;i*i<=x;++i) if(x%i==0) {
        ret = ret/i*(i-1);
        while(x%i==0) x/=i;
    }
    if(x!=1) ret=ret/x*(x-1);
    return ret;
}
 
ll pow(ll a,int n,ll mo) {
    if(n==0) return 1ll%mo;
    ll k = pow(a,n>>1,mo);
    k = k * k % mo;
    if(n&1) k = k * a % mo;
    return k;
}
 
ll gcd(ll a,ll b) {
    if(b==0) return a;
    return gcd(b,a%b);
}
void gcd(ll a,ll b,ll& x,ll& y,ll& d){
    if(b==0) {d=a;x=1;y=0;}
    else {gcd(b,a%b,y,x,d);y-=x*(a/b);}
}
ll inv(ll a,ll n) {
    ll d,x,y;
    gcd(a,n,x,y,d);
    return d==1 ? (x+n)%n : -1;
}
 
int expand_log_mod(ll a,ll b,ll n){ // a^x = b (mod n); gcd(a,n) != 1
    ll c=0,d=1,g;
    while(1) {
        g = gcd(a,n);
        if(g==1) break;
        n/=g;d=d*a/g%n;c++;
        if(b%g) return -1;
        b/=g;
        if(d==b) return (int)c;
    }
    map<ll,int> hash;hash.clear();
    int m = (int)(sqrt(n+0.5));
    ll e=d;
    hash[d]=0;
    for(int i=1;i<m;++i){
        e = e*a%n;
        if(!hash.count(e)) hash[e]=i;
    }
    ll v = inv(pow(a,m,n),n);
    for(int i=0;i<m;++i) {
        if(hash.count(b)) return c+i*m + hash[b];
        b = b * v % n;
    }
    return -1;
}
 
int main() {
    ll a,b,n;
    while(cin >> a >> n >> b) {
        if(b>=n) {
            printf("Orz,I can’t find D!\n");
            continue;
        }else if(b==0){
            printf("0\n");
            continue;
        }
        int ans = expand_log_mod(a%n,b%n,n);
        if(ans==-1) printf("Orz,I can’t find D!\n");
        else printf("%d\n",ans);
    }
}