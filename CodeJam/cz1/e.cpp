using namespace std;
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cmath>
#ifdef XLor
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
typedef pair<int,char> P;
int n,k;int a[1005];char b[1005];
int c[30][30];int tem[30][10];
int ans[1005];
void dfs ()
{
	for (int i=0;i<k;i++)
	{
		for (int j=0;j<k;j++)
		{
			tem[i][0]+=c[j][i];
		}
		tem[i][1]=k;
	}
	for (int i=0;i<k;i++)
	{
	    int temp=tem[i][0];
		for(int j=0;j<k;j++) 
		{
		    if (abs(temp-k*c[j][i])>15*k)
    		{
	    		tem[i][0]-=c[j][i];
		    	tem[i][1]--;
    		}
		}
		//cout<<'t'<<tem[i][0]<<' '<<tem[i][1]<<'\n';
	}
	for (int i=0;i<k;i++)
	{
	    tem[i][2]=tem[i][0]/tem[i][1];
	    if (tem[i][0]%tem[i][1]>=(tem[i][1]+1)/2)tem[i][2]++;
		//cout<<"tt"<<tem[i][1]<<' '<<tem[i][2]<<'\n';
	}
	/*t70 1 t89 2 t95 3*/
	priority_queue<P ,vector<P >,greater <P > > que;
	for (int i=0;i<n;i++)
	{
    dbg(a[i], b[i]);
		for (int j=0;j<k;j++)
		{
			if (b[i]=='A'+j)
			{
				int temp=0;
				temp=a[i]*6+tem[j][2]*4;
				if (temp%10<5)
				temp/=10;
				else
				temp=temp/10+1;
				que.push(P(-temp,char('A'+j))) ;
			}
		}
	}
	for (int i=0;i<n;i++)
	{
		P p=que.top();que.pop();
		cout<<-p.first<<' '<<p.second<<'\n';
	}
}
int main (void)
{
	
	cin>>n>>k;
	for (int i=0;i<n;i++)
	{
		cin>>a[i]>>b[i];
	}
	for (int i=0;i<k;i++)
	for (int j=0;j<k;j++)
	    cin>>c[i][j];
	dfs ();
	return 0;
}