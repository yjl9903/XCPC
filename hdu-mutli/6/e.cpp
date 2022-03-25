#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int max_n=5005;

int s[21];
int val[21][21];
bool dp[21][21][5001];
int ans[5001];
void work(int n){
    s[1]=1,s[2]=1,s[3]=4,s[4]=5,s[5]=1,s[6]=4,s[7]=1,s[8]=9,s[10]=1,s[11]=9;
    for(int i=12;i<=n;i++)s[i]=s[i-11];
    for(int i=1;i<=n;i++){
        int res=0;
        for(int j=i;j<=n;j++){
            res=res*10+s[j];
            if(res>5000)break;
            dp[i][j][res]=true;
        }
    }
    //cout<<"fuck"<<endl;
    for(int len=2;len<=n;len++){
      for(int i=1;i+len-1<=n;i++){
        int j=i+len-1;
        for(int o=i;o<j;o++){
          for(int s=1;s<=5000;s++){
            for(int t=1;t<=s;t++){
              if(dp[i][o][t]&&dp[o+1][j][s-t])dp[i][j][s]=true;
              if(dp[i][o][t]&&s%t==0&&dp[o+1][j][s/t])dp[i][j][s]=true;
            }
          }
        }
      }
    }
    //cout<<"fuck"<<endl;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=5000;j++){
            if(dp[1][i][j]){
                if(ans[j]==0)ans[j]=i;
            }
        }
    }
    cout<<'{';
    for(int i=1;i<=5000;i++){
        cout<<ans[i];
        if(i!=5000)cout<<',';
        else cout<<'}';
    }
    cout<<endl;
}

int main(){
    //work(20);
    /*
    for(int i=1;i<=5000;i++){
        if(ans[i]==0)cout<<i<<endl;
    }
    */
    int T;scanf("%d",&T);
    while(T--){
        int n;scanf("%d",&n);
        if(ans[n]==0)printf("-1\n");
        else printf("%d\n",ans[n]);
    }
    return 0;
}