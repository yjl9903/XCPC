#include <bits/stdc++.h>
using namespace std;
int n,k;
int a[200005];
int main()
{
	
	int cas;
	cin>>cas;
	while (cas--)
	{
		cin>>n>>k;	
		for (int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
		}
		int ans=-1,mx=1e9+7;
		if (k==0)
		{
			ans=a[1];
		} 
		else
		{
			int limit=n-k;
			for (int i=1;i<=limit;i++)
			{
				if(mx>a[i+k]-a[i])
				{
					mx=a[i+k]-a[i];
					if ((a[i]+a[k])%2==0)
					ans=(a[i]+a[i+k])/2;
					else
					{
						ans=(a[i]+a[i+k]+1)/2;
					}
				}
			}
		}
		cout<<ans<<endl;
	}
}