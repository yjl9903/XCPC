#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int T;
ll a,b,k;
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%lld%lld%lld",&a,&b,&k);
        k++;
        double x=(sqrt((k)*(k)+4.0)-k+2.0)/2.0;
        if(a>b)swap(a,b);
        
        ll xk=floor(((b-a)*1.0)*x);
        if(xk==a) printf("0\n");
        else printf("1\n");
    }
    return 0;
}