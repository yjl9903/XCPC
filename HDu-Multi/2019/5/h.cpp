#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1003;

struct point{
    int x,y;
}a[N];

point operator - (const point & a, const point & b){
    return (point){a.x-b.x,a.y-b.y};
}
point operator + (const point & a, const point & b){
    return (point){a.x+b.x,a.y+b.y};
}
ll dot(point a, point b){
    return 1ll*a.x*b.x+1ll*a.y*b.y;
}
ll xmult(point a, point b, point c){
    b=b-a;
    c=c-a;
    return 1ll*b.x*c.y-1ll*b.y*c.x;
}

int t,n;
int l[N],r[N],cnt,tmp;

bool check(point a, point b, point c, point d){
    point cz = a+b-c-d;
    return dot(a-b,cz)==0ll && dot(c-d,cz)==0ll;
}

bool check2(point a, point b, point c, point d){
    point cz=a+b;
    c=c+c;
    d=d+d;
    if(xmult(cz,c,d) && dot(a-b,c-d)==0ll) return true;
    return false;
}

int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=0; i<n; i++){
            scanf("%d%d",&a[i].x,&a[i].y);
        }
        bool flag=0;
        if(n==3){
            printf("Y\n");
        }
        else if(n==4){
            printf("Y\n");
        }
        else if(n%2){
            cnt=(n+1)/2;
            for(int i=0; i<n; i++){
                l[cnt-1]=r[cnt-1]=i;
                for(int j=1; j<=n/2; j++){
                    l[j-1]=(j+i)%n;
                    r[j-1]=(n-j+i)%n;
                }
                /*
                   cout<<cnt<<" : "<<endl;
                   for(int i=0; i<cnt; i++){
                   cout<<i<<" -- "<<l[i]<<" "<<r[i]<<endl;
                   }
                   */
                tmp=0;
                for(int j=0; j<cnt; j++){
                    if(!check(a[l[0]],a[r[0]],a[l[j]],a[r[j]])){
                        tmp++;
                        if(l[j]!=r[j] && check2(a[l[0]],a[r[0]],a[l[j]],a[r[j]])) tmp++;
                    }
                }
                if(tmp<=1){
                    flag=1;
                    break;
                }
                tmp=0;
                for(int j=0; j<cnt; j++){
                    if(!check(a[l[1]],a[r[1]],a[l[j]],a[r[j]])){
                        tmp++;
                        if(l[j]!=r[j] && check2(a[l[0]],a[r[0]],a[l[j]],a[r[j]])) tmp++;
                    }
                }
                if(tmp<=1){
                    flag=1;
                    break;
                }
            }
            if(flag) printf("Y\n");
            else printf("N\n");
        }
        else{
            cnt=n/2;
            for(int i=0; i<n/2; i++){
                for(int j=1; j<=n/2; j++){
                    l[j-1]=(i+j)%n;
                    r[j-1]=(n+1+i-j)%n;
                }
                /*
                   cout<<cnt<<" : "<<endl;
                   for(int i=0; i<cnt; i++){
                   cout<<i<<" -- "<<l[i]<<" "<<r[i]<<endl;
                   }
                   */
                tmp=0;
                for(int j=0; j<cnt; j++){
                    if(!check(a[l[0]],a[r[0]],a[l[j]],a[r[j]])){
                        tmp++;
                        if(l[j]!=r[j] && check2(a[l[0]],a[r[0]],a[l[j]],a[r[j]])) tmp++;
                    }
                }
                if(tmp<=1){
                    flag=1;
                    break;
                }

                tmp=0;
                for(int j=0; j<cnt; j++){
                    if(!check(a[l[1]],a[r[1]],a[l[j]],a[r[j]])){
                        tmp++;
                        if(l[j]!=r[j] && check2(a[l[0]],a[r[0]],a[l[j]],a[r[j]])) tmp++;
                    }
                }
                if(tmp<=1){
                    flag=1;
                    break;
                }
            }
            cnt=n/2+1;
            for(int i=0; i<n/2; i++){
                l[cnt-1]=r[cnt-1]=i;
                l[cnt-2]=r[cnt-2]=(i+n/2)%n;
                for(int j=1; j<n/2; j++){
                    l[j-1]=(i+j)%n;
                    r[j-1]=(n+i-j)%n;
                }
                /*
                   cout<<cnt<<" : "<<endl;
                   for(int i=0; i<cnt; i++){
                   cout<<i<<" -- "<<l[i]<<" "<<r[i]<<endl;
                   }
                   */
                tmp=0;
                for(int j=0; j<cnt; j++){
                    if(!check(a[l[0]],a[r[0]],a[l[j]],a[r[j]])){
                        tmp++;
                        if(l[j]!=r[j] && check2(a[l[0]],a[r[0]],a[l[j]],a[r[j]])) tmp++;
                    }
                }
                if(tmp<=1){
                    flag=1;
                    break;
                }
                tmp=0;
                for(int j=0; j<cnt; j++){
                    if(!check(a[l[1]],a[r[1]],a[l[j]],a[r[j]])){
                        tmp++;
                        if(l[j]!=r[j] && check2(a[l[0]],a[r[0]],a[l[j]],a[r[j]])) tmp++;
                    }
                }
                if(tmp<=1){
                    flag=1;
                    break;
                }
            }
            if(flag) printf("Y\n");
            else printf("N\n");
        }
    }
    return 0;
}