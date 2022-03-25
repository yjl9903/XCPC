#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5+10;
const int D = 19;
const int MOD = 998244353;
struct PAM{
    int next[N][4],go[N][4],fail[N],len[N],pre[N][D],dep[N],val[N],dp[N],mx[N];
    int txt[N],cnt[N],w[4],o;
    int tot,root0,root1,last,size;
    void init(){
        last=tot=size=0; txt[size]=-1; o=0;
        for(int i=0;i<D;++i) pre[size][i]=0; dep[size]=0;
        root0=newnode(0); root1=newnode(-1);
        fail[root0]=1; fail[root1]=0;
        for(int i=0;i<4;++i) go[root0][i]=root1;
    }
    int newnode(int l){
        len[tot]=l; cnt[tot]=val[tot]=dp[tot]=mx[tot]=0;
        memset(next[tot],0,sizeof(next[tot]));
        tot++; return tot-1;
    }
    int getfail(int x){
        if(txt[get(size,dep[size]-len[x]-1)]==txt[size]) return x;
        else return go[x][txt[size]];
    }
    int get(int x,int l){
        for(int i=D-1;i>=0;--i)
            if(dep[pre[x][i]]>=l) x=pre[x][i];
        return x;
    }
    void extend(int c,int p){
        txt[++size]=c; dep[size]=dep[p]+1; pre[size][0]=p;
        for(int i=1;i<D;++i) pre[size][i]=pre[pre[size][i-1]][i-1];
        int now=getfail(last);
        if(!next[now][c]){
            int tmp=newnode(len[now]+2);
            fail[tmp]=next[getfail(fail[now])][c];
            next[now][c]=tmp;
            if(len[tmp]==1) val[tmp]=w[c];
            else val[tmp]=val[now]+w[c]*2;
            dp[tmp]=(val[tmp]+dp[fail[tmp]])%MOD;
            mx[tmp]=max(val[tmp],mx[fail[tmp]]);
            memcpy(go[tmp],go[fail[tmp]],sizeof(go[tmp]));
            go[tmp][txt[get(size,dep[size]-len[fail[tmp]])]]=fail[tmp];
            //printf("%d %d %d %d %d %d\n",tmp,fail[tmp],go[tmp][0],go[tmp][1],go[tmp][2],go[tmp][3]);
        }
        last=next[now][c]; cnt[last]++;
    }
    void count(){
        for(int i=tot-1;~i;--i) cnt[fail[i]]+=cnt[i];
    }
}pam;
int flx(char c){
    if(c=='A') return 0;
    else if(c=='C') return 1;
    else if(c=='G') return 2;
    else return 3; 
}
char read_char(){
    char ch=getchar();
    while(ch<'A'||ch>'Z') ch=getchar();
    return ch;
}
int p[N],f,n,ans; char c;
int main(){
    //freopen("D:\\in.txt","r",stdin);
    //freopen("D:\\out.txt","r",stdout);
    scanf("%d %d %d %d",&pam.w[0],&pam.w[1],&pam.w[2],&pam.w[3]);
    c=read_char(); pam.init(); pam.extend(flx(c),0);
    printf("%d\n",ans=pam.mx[p[1]=pam.last]);
    for(int i=2;i;i++){
        int code = scanf("%d",&f);
        if (code < 1) break;
        // f^=ans;
        if(!f) break; c=read_char();
        pam.last=p[f]; pam.extend(flx(c),f);
        printf("%d\n",ans=pam.mx[p[i]=pam.last]);
    }
    //cerr<<pam.tot<<endl;
    ans=0;
    for(int i=2;i<pam.tot;++i) ans=(ans+1LL*pam.dp[i]*pam.cnt[i])%MOD;
    printf("%d\n",ans);
}