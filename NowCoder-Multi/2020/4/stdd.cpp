#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+12;
char s[maxn];
int a[maxn],n,_,ans,sum[maxn],mn[maxn],mx[maxn],t[maxn];
bool cmp(int b[],int c[],int n){
    for (int i=1;i<=n;i++) if (b[i]!=c[i]) return b[i]<c[i];
    return 0;
}
int work(int x){
    if (x>1&&!a[1]) return 9;
    for (int i=1;i<=x;i++) mx[i]=mn[i]=a[i];
    for (int p=1;p<n/x;p++){
        for (int i=1;i<=x;i++) t[i]=a[p*x+i];
        if (x>1&&!t[1]) return 9;
        if (cmp(t,mn,x)) for (int i=1;i<=x;i++) mn[i]=t[i];
        if (cmp(mx,t,x)) for (int i=1;i<=x;i++) mx[i]=t[i];
    }
    for (int i=1;i<=x;i++) t[i]=mx[i]-mn[i];
    for (int i=x;i;i--) if (t[i]<0) t[i]+=10,t[i-1]--;
    for (int i=1;i<x;i++) if (t[i]) return 9;
    return t[x];
}
bool all0(int l,int r){
    return sum[r]==sum[l-1];
}
bool all9(int l,int r){
    return sum[r]-sum[l-1]==(r-l+1)*9;
}
int work0(int x){
    int p=1,t=0,s=0;
    while (p<=n){
        if (a[p]==1){
            if (p+x>n) return 9;
            if (!all0(p+1,p+x-1)) return 9;
            s=max(s,a[p+x]);
            p+=x+1;
        } else {
            if (p+x-1>n) return 9;
            if (!all9(p,p+x-2)) return 9;
            t=max(t,9-a[p+x-1]);
            p+=x;
        }
    }
    return s+t+1;
}
void solve(){
    scanf("%d",&n);
    scanf("%s",s+1);
    ans=9;
    for (int i=1;i<=n;i++) a[i]=s[i]-'0',sum[i]=sum[i-1]+a[i];
    for (int i=1;i<=n/2;i++) ans=min(ans,work0(i));
    for (int i=1;i<=n/2;i++) if (n%i==0) ans=min(ans,work(i));
    printf("%d\n",ans);
}
int main(){
    scanf("%d",&_);
    while (_--) solve();
}