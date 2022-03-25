#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2005;
struct point{
	ll x,y,typ;
}a[N],b[N],tmp[N*4];
int st[N*2],en[N*2];
point operator - (const point &a, const point &b){
	return(point){a.x-b.x,a.y-b.y,a.typ};
}

ll xmult(point p1, point p2){
	return p1.x*p2.y-p2.x*p1.y;
}

ll dmult(point p1, point p2){
	return p1.x*p2.x+p1.y*p2.y;
}

ll fp(point x){
	if(x.y<0) return -1;
	if(x.y==0 && x.x>=0) return 0;
	if(x.y>0) return 1;
	return 2;
}

int n,q,cnt;

bool cmp(point a, point b){
	if(fp(a)!=fp(b)) return fp(a)<fp(b);
	return xmult(a,b)>0;
}

int ans[N];

int add(int p){
	return (p==cnt-1)?0:p+1;
}

vector<int> vec;

int main(){
	while(~scanf("%d%d",&n,&q)){
		for(int i=0; i<n; i++){
			scanf("%lld%lld",&a[i].x,&a[i].y);
			a[i].typ=0;
		}
		for(int i=0; i<q; i++){
			scanf("%lld%lld",&b[i].x,&b[i].y);
			b[i].typ=i+1;
			ans[i+1]=0;
		}
		for(int i=0; i<n; i++){
			//cout<<i<<endl;
			cnt=0;
			for(int j=0; j<n; j++){
				if(j==i) continue;
				tmp[cnt++]=a[j]-a[i];
			}
			for(int j=0; j<q; j++){
				tmp[cnt++]=b[j]-a[i];
			}
			sort(tmp,tmp+cnt,cmp);
			/*
			for(int i=0; i<cnt; i++){
				cout<<"dian"<<tmp[i].x<<" "<<tmp[i].y<<" "<<tmp[i].typ<<endl;
			}
			*/
			int p=0,num=0;
			for(int j=0; j<cnt; j++){
				if(j && xmult(tmp[j],tmp[j-1])==0 && dmult(tmp[j],tmp[j-1])>0){
					//cout<<i<<" "<<j<<" "<<num<<" "<<tmp[j].typ<<endl;
					if(tmp[j].typ) ans[tmp[j].typ]+=num;
					else{
						for(int i:vec) ans[i]++;
						/*
						if(vec.size()){
							for(int i:vec) cout<<"pu"<<i<<endl;
						}
						*/
					}
				}
				else{
					num=0;
					vec.clear();
					while(true){
			//cout<<p<<endl;
						if(xmult(tmp[j],tmp[p])<0 || dmult(tmp[j],tmp[p])<0) break;
						if(dmult(tmp[j],tmp[p])==0){
							if(tmp[p].typ){
								vec.push_back(tmp[p].typ);
							}
							else num++;
						}
						p=add(p);
						if(p==j) break;
					}
					//cout<<i<<" "<<j<<" "<<num<<" s"<<tmp[j].typ<<endl;
					if(tmp[j].typ) ans[tmp[j].typ]+=num;
					else{
						for(int i:vec) ans[i]++;
						/*
						if(vec.size()){
							for(int i:vec) cout<<"pu"<<i<<endl;
						}
						*/
					}
				}
				//if(i==1 && j==1) cout<<"ans"<<ans[2]<<endl;
			}
		}
		
		for(int i=0; i<q; i++){
			cnt=0;
			for(int j=0; j<n; j++){
				tmp[cnt++]=a[j]-b[i];
			}
			sort(tmp,tmp+cnt,cmp);
			int p=0,num=0;
			for(int j=0; j<cnt; j++){
				if(j && xmult(tmp[j],tmp[j-1])==0 && dmult(tmp[j],tmp[j-1])>0){
					ans[i+1]+=num;
				}
				else{
					num=0;
					while(true){
						if(xmult(tmp[j],tmp[p])<0 || dmult(tmp[j],tmp[p])<0) break;
						if(dmult(tmp[j],tmp[p])==0){
							num++;
						}
						p=add(p);
						if(p==j) break;
					}
					//cout<<p<<" "<<j<<endl;
					//if(i==1) cout<<"haha"<<j<<" "<<num<<endl;
					ans[i+1]+=num;
				}
			}
		}
		for(int i=1; i<=q; i++){
			printf("%d\n",ans[i]);
		}
	}
	return 0;
}
