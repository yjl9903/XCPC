#include<stdio.h>
#include<string.h>
using namespace std;
int s[105],mem[105];
int gcd(int a,int b){return b?gcd(b,a%b):a;}
int main(){
	int T; scanf("%d",&T);
	while (T--){
		memset(s,-1,sizeof(s));
		int n,m,i,a,b,k = 1; scanf("%d%d",&n,&m);
	    mem[0]=2;
	    for(i=1;i<=m;i++){
		    scanf("%d%d",&a,&b);s[a]=b;
		    if (a<=2) continue;
		    mem[k++]=a;
	    }
	    if (s[1]==-1) s[1]=100;
		if (s[2]==-1) s[2]=s[1];
		int sum=s[1]+s[2],sum2=sum;
	    for (i=1;i<k;i++) if (mem[i]>2&&mem[i-1]>=2)
			sum2+=(mem[i]-mem[i-1])*s[mem[i]];
		int x=gcd(sum,sum2);
		sum/=x; sum2/=x;
	    printf("%d/%d\n",sum,sum2);
	}
}