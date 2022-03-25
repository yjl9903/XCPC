#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <queue>
#include <bits/stdc++.h>
#include <stack>

using namespace std;

#define FOR(i,n,m) for(int i=n; i<m; i++)
#define ROF(i,n,m) for(int i=n; i>m; i--)
#define pb push_back
#define ri(a)  scanf("%d",&a)
#define rii(a,b)  scanf("%d %d",&a,&b)
#define riii(a,b,c) scanf("%d %d %d",&a,&b,&c)
#define lri(a) scanf("%lld",&a)
#define lrii(a,b) scanf("%lld %lld",&a,&b)
#define F first
#define S second

typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

const int INF = 0x3f3f3f3f;

/*--------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------*/

int n,k;
int a[3000];
int s[3000];
int v[3000];

int main(){

	//ios_base::sync_with_stdio(false);
	//cin.tie(NULL);

	cin>>n>>k;
	FOR(i,0,n){
		cin>>a[i];
		s[i]=a[i];
	}
	
	sort(s,s+n);

	int sum=0;

	ROF(i,n-1,n-k-1){
		v[s[i]]=1;
		sum+=s[i];
	}

	cout<<sum<<endl;

	int ki=0,j=0;
	FOR(i,0,n){
		j++;
		if(v[a[i]] && ki<k-1){
			cout<<j<<" ";
			j=0;
			ki++;
		}
	}

	cout<<j<<endl;

	return 0;
}