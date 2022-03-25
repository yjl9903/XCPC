#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<algorithm>
using namespace std;
const long long mod=1e9+7;
struct jz
{
	long long num[3][3];
	jz() { memset(num,0,sizeof(num)); }
	jz operator*(const jz &P)const
	{
		jz ans;
		for(int k=0;k<3;k++)
			for(int i=0;i<3;i++)
				for(int j=0;j<3;j++)
					ans.num[i][j]=(ans.num[i][j]+num[i][k]*P.num[k][j]%mod)%mod;
		return ans;
	}
}COE,ans,unit;
int T_T;
long long A,B,C,D,P,n;
jz pOw(jz X,long long m)
{
	jz ans;
	for(ans=unit;m;m>>=1,X=X*X)
		if(m&1)
			ans=ans*X;
	return ans;
}
void init(long long A,long long B,long long C,long long D,long long x)
{
	COE.num[0][0]=0;
	COE.num[0][1]=1;
	COE.num[0][2]=0;
	COE.num[1][0]=C;
	COE.num[1][1]=D;
	COE.num[1][2]=x; // this element need to be changed each step.
	COE.num[2][0]=0;
	COE.num[2][1]=0;
	COE.num[2][2]=1;
	return;
}
int main()
{
	for(int i=0;i<3;i++) unit.num[i][i]=1;
	scanf("%d",&T_T);
	while(T_T--)
	{
		scanf("%lld%lld%lld%lld%lld%lld",&A,&B,&C,&D,&P,&n);
		if(n==1) printf("%lld\n",A);
		else if(n<P)
		{
			ans.num[0][0]=A;
			ans.num[1][0]=B;
			ans.num[2][0]=1;
			for(long long i=3;i<=n;i=P/(P/i)+1)
			{
				init(A,B,C,D,P/i);
				if(n<=P/(P/i)) COE=pOw(COE,n-i+1);
				else COE=pOw(COE,P/(P/i)+1-i);
				ans=COE*ans;
			}
			printf("%lld\n",ans.num[1][0]);
		}
		else if(P<=n)
		{
			ans.num[0][0]=A;
			ans.num[1][0]=B;
			ans.num[2][0]=1;
			for(long long i=3;i<=P;i=P/(P/i)+1)
			{
				init(A,B,C,D,P/i);
				COE=pOw(COE,P/(P/i)+1-i);
				ans=COE*ans;
			}
			init(A,B,C,D,0);
			COE.num[1][2]=0;
			COE=pOw(COE,n-max(P,2LL));
			ans=COE*ans;
			printf("%lld\n",ans.num[1][0]);
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}

