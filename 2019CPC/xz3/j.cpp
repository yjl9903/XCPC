#include<bits/stdc++.h>
using namespace std;
const int N=1003;
int n;
bool vis[N][N];
int ans[N*N/2],cnt;
int tmpans[N][N];

void dfs(int x){
	for(int i=1; i<=n; i++){
		if(!vis[x][i]){
			vis[x][i]=vis[i][x]=1;
			dfs(i);
		}
	}
	ans[cnt++]=x;
	return;
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++) vis[i][i]=1;
	if(n%2){
		dfs(n);
		int p=0;
		for(int i=1; i<n; i++){
			for(int j=0; j<i; j++)
				printf("%d ",ans[p++]);
			printf("%d\n",ans[p]);
		}
	}
	else{
		int p=1;
		for(int i=1; i<n; i+=2){
			for(int j=0; j<p; j++){
				if(j%4==0) tmpans[p][j]=i;
				else if(j%4==2) tmpans[p][j]=i+1;
				else tmpans[p][j]=(j+1)/2;
			}
			tmpans[p][p]=i+1;
			for(int j=0; j<p; j++){
				vis[tmpans[p][j]][tmpans[p][j+1]]=1;
				vis[tmpans[p][j+1]][tmpans[p][j]]=1;
			}
			if(p%4==1){
				p++;
			}
			else{
				p+=3;
			}
		}
		dfs(n);
		p=0;
		for(int i=1; i<n; i++){
			if(tmpans[i][0]){
				for(int j=0; j<=i; j++){
					printf("%d%c",tmpans[i][j],j==i?'\n':' ');
				}
			}
			else{
				for(int j=0; j<i; j++)
					printf("%d ",ans[p++]);
				printf("%d\n",ans[p]);
			}
		}
	}
	return 0;
}