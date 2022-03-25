#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod=998244353;
struct mat{
	ll a[3][3];
};

mat mul(mat x, mat y){
	mat ans;
	memset(ans.a,0,sizeof(ans.a));
	for(int i=0; i<3; i++)
		for(int j=0; j<3; j++)
			for(int k=0; k<3; k++)
				ans.a[i][j]=(ans.a[i][j]+x.a[i][k]*y.a[k][j])%mod;
	return ans;
}

mat qpow(mat x, ll y){
	mat ans;
	memset(ans.a,0,sizeof(ans.a));
	ans.a[0][0]=ans.a[1][1]=ans.a[2][2]=1;
	while(y){
		if(y&1){
			ans=mul(ans,x);
		}
		y>>=1;
		x=mul(x,x);
	}
	return ans;
}

int main(){
	
	return 0;
}
