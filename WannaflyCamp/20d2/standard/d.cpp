#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define db(x) cout<<#x<<":"<<x<<endl;
const int M=1e6+20;
char s[M],s2[M];
struct SAM{
    int last,cnt,ch[M<<1][26],fa[M<<1],len[M<<1];
    int mex;
    void ins(int c){
        int p=last,np=++cnt;
        last=np,len[np]=len[p]+1;
        for(;p&&!ch[p][c];p=fa[p])
            ch[p][c]=np;
        if(!p)
            fa[np]=1;
        else{
            int q=ch[p][c];
            if(len[p]+1==len[q])
                fa[np]=q;
            else{
                int nq=++cnt;
                len[nq]=len[p]+1;
                memcpy(ch[nq],ch[q],sizeof(ch[q]));
                fa[nq]=fa[q],fa[q]=fa[np]=nq;
                for(;ch[p][c]==q;p=fa[p])
                    ch[p][c]=nq;
            }
        }
    }
    void build(){
        scanf("%s",s+1);
        int lenn=strlen(s+1);
        last=cnt=1;
        printf("0"),ins(s[1]-'a');
        int p=2;
        while(p<=lenn&&s[p]==s[1])
            ins(s[p]-'a'),printf(" 0"),++p;
        if (p>lenn){
            putchar('\n');
            for(int i=1;i<=cnt;++i)
                fa[i]=len[i]=0,memset(ch[i],0,sizeof(ch[i]));
            return;
        }
        mex=p-2;
        for(int i=p;i<=lenn;i++){
            ins(s[i]-'a');
            if(len[fa[last]]>mex)
                ++mex;
            printf(" %d",mex+1);
        }
        putchar('\n');
        for(int i=1;i<=cnt;++i)
            fa[i]=len[i]=0,memset(ch[i],0,sizeof(ch[i]));
    }
}sam;
int main(){
    int T;
    scanf("%d",&T);
    for(int i=1;i<=T;++i)
        sam.build();
    return 0;
}