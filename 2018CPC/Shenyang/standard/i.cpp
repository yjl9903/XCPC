#include <bits/stdc++.h>
using namespace std;
const int maxn=3007;
struct Trie{
	int ch[maxn][2];
	int end[maxn];
	int sz;
	int newnode(){
		ch[sz][0]=ch[sz][1]=-1;
		end[sz]=-1;
		return sz++;
	}
	void init(){
		sz=0;
		newnode();
	}
	void insert(char s[],int x){
		int len=strlen(s);
		int u=0;
		for(int i=0;i<len;i++){
			int c=s[i]-'0';
			if(ch[u][c]==-1){
				ch[u][c]=newnode();
			}
			u=ch[u][c];
		}
		end[u]=x;
	}
	void print(char s[],int num){
		int p=0;
		while(num){
			int u=0;
			for(p;;p++){
				int c=s[p]-'0';
				u=ch[u][c];
				if(end[u]!=-1){
					printf("%c",(char)end[u]);
					num--;
					p++;
					break;
				}
			}
		}
		printf("\n");
	}
}trie;
int n,m;
char str[200003];
char s[1000003];
char s2[1000003];
int tot;
int tot2;
char tmp[20];
int x;
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		trie.init();
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++){
			scanf("%d%s",&x,tmp);
			trie.insert(tmp,x);
		}
		scanf("%s",str);
		tot=tot2=0;
		for(int i=0;str[i];i++){
			int num;
			if(str[i]>='A'&&str[i]<='F'){
				num=str[i]-'A'+10;
			}
			else if(str[i]>='a'&&str[i]<='f'){
				num=str[i]-'a'+10;
			}
			else num=str[i]-'0';
			for(int j=3;j>=0;j--){
				if((1<<j)&num){
					s[tot++]='1';
				}
				else s[tot++]='0';
			}
		}
		for(int i=0;i<tot;i++){
			if(i%9==8){
				int op=0;
				for(int j=1;j<=8;j++){
					op^=(s2[tot2-j]-'0');
				}
				if(op==s[i]-'0'){
					tot2-=8;
				}
			}
			else s2[tot2++]=s[i];
		}
		trie.print(s2,n);
	}
}