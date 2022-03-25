#include<bits/stdc++.h>
using namespace std;
const int N=1e4+4;
int n,m;
char s[10][10][N];
int sum[10][10][N][2],len[10][10],a,b,cnt;
int vis[10];
int numofc[10];
char tmpc[4];
 
struct node{
    int x,id;
}ans[N],tmp[N];
 
bool add(int x, int num){
    if(vis[x]) return numofc[x]==num;
    vis[x]=1;
    numofc[x]=num;
    for(int i=1; i<=num; i++){
        ans[cnt++]=(node){x,i};
    }
    return true;
}
 
bool operator < (const node & a, const node & b){
    if(a.x==b.x) return a.id<b.id;
    if(a.x>b.x) return !(b<a);
    int l=1, r=len[a.x][b.x],m;
    while(l<r){
        m=(l+r)/2;
        if(sum[a.x][b.x][m][0]<a.id) l=m+1;
        else r=m;
    }
    if(sum[a.x][b.x][r][1]<b.id) return true;
    else return false;
}
 
bool check(){
    for(int i=0; i<m; i++){
        for(int j=i+1; j<m; j++){
            int p=1;
            for(int k=0; k<n; k++){
                if(ans[k].x==i || ans[k].x==j){
                    if(s[i][j][p]!=ans[k].x+'a') return false;
                    else p++;
                }
            }
        }
    }
    return true;
}
 
void mysort(int l, int r){
    if(r<=l+1) return;
    int m=(l+r)/2;
    //cout<<l<<" "<<m<<" "<<r<<endl;
    mysort(l,m);
    mysort(m,r);
    int p1=l,p2=m;
    for(int i=l; i<r; i++){
        if(p1==m) tmp[i]=ans[p2++];
        else if(p2==r) tmp[i]=ans[p1++];
        else if(ans[p1]<ans[p2]) tmp[i]=ans[p1++];
        else tmp[i]=ans[p2++];
    }
    for(int i=l; i<r; i++) ans[i]=tmp[i];
    return;
}
 
int main(){
    bool flag=1;
    scanf("%d%d",&n,&m);
    for(int i=1; i<=m*(m-1)/2; i++){
        scanf("%s",tmpc);
        a=tmpc[0]-'a';
        b=tmpc[1]-'a';
        if(a>b) swap(a,b);
        scanf("%d",&len[a][b]);
        if(len[a][b]) scanf("%s",s[a][b]+1);
        for(int i=1; i<=len[a][b]; i++){
            sum[a][b][i][0]=sum[a][b][i-1][0];
            sum[a][b][i][1]=sum[a][b][i-1][1];
            if(s[a][b][i]==a+'a') sum[a][b][i][0]++;
            else sum[a][b][i][1]++;
        }
        flag=flag&&add(a,sum[a][b][len[a][b]][0]);
        flag=flag&&add(b,sum[a][b][len[a][b]][1]);
    }
    //cout<<cnt<<endl;
    //assert(cnt==n);
    flag=flag&&(cnt==n);
    if(!flag){
        printf("-1\n");
        return 0;
    }
    mysort(0,n);
    if(check()){
        for(int i=0; i<n; i++) putchar(ans[i].x+'a');
        putchar('\n');
    }
    else printf("-1\n");
    return 0;
}