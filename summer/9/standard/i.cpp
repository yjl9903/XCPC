#include <bits/stdc++.h>
using namespace std;
int n,m;
map<int,int>ma;
map<int,int>tim;
struct node{
	int a,b,c,v,id;
}rec[100003],tmp[100003],b[100003];
int ans[100003];
int v[100003];
int tot,ttot;
bool cmp1(node a,node b){
	if(a.a!=b.a)return a.a>b.a;
	if(a.b!=b.b)return a.b>b.b;
	return a.c>b.c;
}
bool cmp2(node a,node b){
	if(a.b!=b.b)return a.b>b.b;
	return a.c>b.c;
}
void debug(){
	for(int i=1;i<=tot;i++){
		for(int j=1;j<=tot;j++){
			if(j==i)continue;
			if(rec[j].a>=rec[i].a&&rec[j].b>=rec[i].b&&rec[j].c>=rec[i].c)ans[rec[i].id]++;
		}
	}
}
int c[100003];
int lowbit(int x){
	return x&(-x);
}
int query(int x){
	int ret=0;
	while(x<=100000){
		ret+=c[x];
		x+=lowbit(x);
	}
	return ret;
}
void update(int x){
	while(x){
		c[x]++;
		x-=lowbit(x);
	}
}
void reset(int p){
	while(p){
		c[p]=0;
		p-=lowbit(p);
	}
}

void cdq(int l, int r){
	if(l==r)return;
	int m=(l+r)/2;
	cdq(l, m);
	cdq(m+1, r);
	for(int i=l;i<=r;i++){
		b[i]=rec[i];
	}
	sort(b+l, b+m+1, cmp2);
	sort(b+m+1, b+r+1, cmp2);
	int j=l;
	for(int i=m+1;i<=r;i++){
		while(j<=m&&b[j].b>=b[i].b){
			update(b[j++].c);
		}
		ans[b[i].id]+=query(b[i].c);
	}
	for(int i=l;i<=m;i++)reset(b[i].c);
	return;
}
int main(){
	int T;
	scanf("%d",&T);
	for(int tt=1;tt<=T;tt++){
		memset(ans,0,sizeof(ans));
		memset(c,0,sizeof(c));
		scanf("%d%d",&n,&m);
		ma.clear();
		tim.clear();
		for(int i=1;i<=n;i++){
			int a,b;
			scanf("%d%d",&a,&b);
			if(ma.find(b)==ma.end()||ma[b]<a){
				ma[b]=a;
				tim[b]=1;
			}
			else if(ma[b]==a){
				tim[b]++;
			}
		}
		tot=0,ttot=0;
		for(int i=1;i<=m;i++){
			int c,d,e;
			scanf("%d%d%d",&c,&d,&e);
			if(ma.find(e)==ma.end())continue;
			++ttot;
			tmp[ttot].a=c;
			tmp[ttot].b=d;
			tmp[ttot].c=ma[e];
			tmp[ttot].v=tim[e];
			tmp[ttot].id=tot;
		}
		sort(tmp+1,tmp+1+ttot,cmp1);
		for(int i=1;i<=ttot;i++){
			if(tot&&tmp[i].a==rec[tot].a&&tmp[i].b==rec[tot].b&&tmp[i].c==rec[tot].c)rec[tot].v+=tmp[i].v;
			else {
				++tot;
				rec[tot]=tmp[i];
				rec[tot].id=tot;
			}
		}
		for(int i=1;i<=tot;i++){
			v[i]=rec[i].v;
		}

		sort(rec+1,rec+1+tot,cmp1);
		cdq(1,tot);
		int ret=0;
		for(int i=1;i<=tot;i++){
			if(!ans[i]){
				ret+=v[i];
			}
		}
		printf("Case #%d: %d\n",tt,ret);
	}
}