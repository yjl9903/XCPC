#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod=1025436931;
int t;
int n,m,r1,c1,r2,c2;

struct mat{
	ll a[2][2];
};

mat mul(mat a, mat b){
	mat ans;
	memset(ans.a,0,sizeof(ans.a));
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			for(int k=0; k<2; k++){
				ans.a[i][j]=(ans.a[i][j]+a.a[i][k]*b.a[k][j])%mod;
			}
		}
	}
	return ans;
}

mat qpow(mat x, ll y){
	mat ans;
	ans.a[0][0]=ans.a[1][1]=1;
	ans.a[0][1]=ans.a[1][0]=0;
	while(y){
		if(y&1) ans=mul(ans,x);
		y>>=1;
		x=mul(x,x);
	}
	return ans;
}

void f(ll x){
    cout << x << endl;
	assert(x>=0);
	mat ans;
	ans.a[0][0]=ans.a[0][1]=ans.a[1][0]=1;
	ans.a[1][1]=0;
	ans=qpow(ans,x);
	// printf("%lld\n",(ans.a[0][0]+ans.a[0][1]+mod-1)%mod);
}


int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d%d%d%d",&n,&m,&r1,&c1,&r2,&c2);
		if((r1+c1)%2!=(r2+c2)%2){
			if(n==1){
				if(c1<c2) f(c2-1);
				else f(m-c2);
			}
			else if(m==1){
				if(r1<r2) f(r2-1);
				else f(n-r2);
			}
			else{
				printf("countless\n");
			}
		} else {
			if(r1>r2){
				r1=n+1-r1;
				r2=n+1-r2;
			}
			if(c1>c2){
				c1=m+1-c1;
				c2=m+1-c2;
			}
			if(r2-r1==c2-c1) f(r2+c2-3);
			else if(r2-r1>c2-c1) f(max(r2+c2-3,r2-c2+m-2));
			else f(max(r2+c2-3,c2-r2+n-2));
		}
	}
	return 0;
}