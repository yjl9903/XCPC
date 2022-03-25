#include<iostream>
#include<cstdio>
#include<algorithm>
#define N 2200001
using namespace std;
int n,m,tot,top,sz;
int v[10001],num[20001],hhh[20001];
int flag[10001],A[10001],B[10001],K[10001],root[10001];
int sum[N],ls[N],rs[N];
int L[30],R[30],a,b;
int lowbit(int x)
{return x&(-x);}
int find(int x)
{
    // cout << "? " << x << endl;
    int l=1,r=tot,mid;
    while(l<=r)
    {
         int mid=(l+r)>>1;
         if(hhh[mid]<x)l=mid+1;
         else r=mid-1;
        } 
    return l;
}
void updata(int last,int l,int r,int &rt,int w,int x)
{
     rt=++sz;
     sum[rt]=sum[last]+x;ls[rt]=ls[last];rs[rt]=rs[last];
     if(l==r)  return;
     int mid=(l+r)>>1;
     if(w<=mid)  updata(ls[last],l,mid,ls[rt],w,x);
     else  updata(rs[last],mid+1,r,rs[rt],w,x);
}
int query(int l, int r, int k) {
    if (l == r) return l;
    int m = (l + r) >> 1, c = 0;
    for (int i = 1; i <= a; i++) c -= sum[ls[L[i]]];
    for (int i = 1; i <= b; i++) c += sum[ls[R[i]]];
    // dbg(k, l, r, sum);
    if (k <= c) {
        for (int i = 1; i <= a; i++) L[i] = ls[L[i]];
        for (int i = 1; i <= b; i++) R[i] = ls[R[i]];
        return query(l, m, k);
    } else {
        for (int i = 1; i <= a; i++) L[i] = rs[L[i]];
        for (int i = 1; i <= b; i++) R[i] = rs[R[i]];
        return query(m + 1, r, k - c);
    }
}

int main()
{
	char s[3];
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
	    scanf("%d",&v[i]);
	    num[++top]=v[i];
    }
    for(int i=1;i<=m;i++)
    {
    	scanf("%s",s);
    	scanf("%d%d",&A[i],&B[i]);
    	if(s[0]=='Q'){scanf("%d",&K[i]);flag[i]=1;}
    	else num[++top]=B[i];
    }
    sort(num+1,num+top+1);
    hhh[++tot]=num[1];
    for(int i=2;i<=top;i++)
       if(num[i]!=num[i-1])
          hhh[++tot]=num[i];
    for(int i=1;i<=n;i++)
    {
    	int t=find(v[i]);
    	for(int j=i;j<=n;j+=lowbit(j))
    	    updata(root[j],1,tot,root[j],t,1);
    }
    for(int i=1;i<=m;i++)
    	if(flag[i])
    	{
    		a=0;b=0;A[i]--;
    		for(int j=A[i];j>0;j-=lowbit(j))
    		   L[++a]=root[j];
 		    for(int j=B[i];j>0;j-=lowbit(j))
 		       R[++b]=root[j];
            printf("%d\n",hhh[query(1,tot,K[i])]);
    	}
    	else
        {
             int t=find(v[A[i]]);
             for(int j=A[i];j<=n;j+=lowbit(j))
			     updata(root[j],1,tot,root[j],t,-1);
             v[A[i]]=B[i];
             t=find(B[i]);
             for(int j=A[i];j<=n;j+=lowbit(j))
                 updata(root[j],1,tot,root[j],t,1);
        }
	return 0;
}