#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int main(){
   int T=0;
    scanf("%d",&T);
    while(T--){
        int n=0;
        scanf("%d",&n);
        long long price[n];
        for(int i=0;i<n;i++){
            scanf("%lld",&price[i]);
        }
        long long cnt_N=0,profit=0;
        for(int i=0;i<n-1;i++){
                if(price[i]<price[i+1]){
                    for(int j=i+1;j<n;j++){
                        if(j==n-1){
                            profit=price[j]-price[i]+profit;
                            cnt_N++;
                            i=j;
                            break;
                        }
                        else if(price[j]>price[j+1]){
                            profit=price[j]-price[i]+profit;
                            cnt_N++;
                            i=j;
                            break;
                        }
                    }
                }
            }
        printf("%lld %lld\n",profit,2*cnt_N);
 
        }
    }
