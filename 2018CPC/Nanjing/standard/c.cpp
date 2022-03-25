#include <bits/stdc++.h>
using namespace std;

int t,n,m,tot;
int v[20]={0,0,0,3,4,5,6,7,8,9,10,11,12,13,1,2};
int num[202][20],sum[202],a[20010];

void init (){
	int x;
	memset (num,0,sizeof (num));
	memset (sum,0,sizeof (sum));
	scanf ("%d%d",&n,&m);
	for (int i=1;i<=m;i++){
		scanf ("%d",&a[i]);
		if (a[i]==1)a[i]=14;
		else if (a[i]==2)a[i]=15;
		x=(i-1)/5;
		// cout<<i<<' '<<a[i]<<' '<<x<<endl;
		if (x<n){
			num[x][a[i]]++;
			sum[x]+=v[a[i]];
		}
	}
	tot=n*5+1;
	// for (int i=0;i<n;i++)cout<<"==="<<sum[i]<<endl;
}

int work (){
	int i,j,st,pai;
	st=0;
	while (1){
		for (i=3;i<=15;i++){
			if (num[st][i]>0){
				pai=i;
				num[st][i]--;sum[st]-=v[i];
				if (sum[st]==0){return st;}
				break;
			}
		}

		for (i=(st+1)%n;i!=st;i=(i+1)%n){//0~n-1
			if (num[i][pai+1]){
				pai++;
				num[i][pai]--;sum[i]-=v[pai];
				st=i;
			}
			else if (pai!=15&&num[i][15]){
				pai=15;
				num[i][pai]--;sum[i]-=v[pai];
				st=i;
			}
			if (sum[i]==0){return i;}
		}
		int tt=tot;
		for (i=st;tot<=m&&!(i==st&&tot>tt);i=(i+1)%n){
			num[i][a[tot]]++;sum[i]+=v[a[tot]];
			tot++;
		}
	}
}

int main (){
	int cas=0,win;
	cin>>t;
	while (t--){
		init ();
		win=work ();
		printf("Case #%d:\n",++cas);
		for (int i=0;i<n;i++){
			if (i==win){
				printf("Winner\n");
			}
			else printf("%d\n",sum[i]);
		}
	}
	return 0;
}