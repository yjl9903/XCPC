#include<cstdio>
#include<algorithm>
#include<cmath>
#include<iostream>
#include<set>
#include<cstring>
using namespace std;
typedef long long ll;
int n;
double damage;
int main()
{
    while(scanf("%d",&n)!=EOF){
    	if(n>100){
    		damage=(100+2*(n-50))*2;
    		printf("%.2lf\n",damage);
		}
    	else{
    		damage=(100+(n/2)*2)*2*0.02*(n-n/2)+(100+(n/2)*2)*(1-0.02*(n-n/2));
    		printf("%.2lf\n",damage);
		}
	}
	return 0;
}
