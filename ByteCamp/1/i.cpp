#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
#ifdef XLor
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define IOS ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define ms(a,b) memset(a,b,sizeof(a))
#define msn(a,n,b) for(int i=0;i<=n;i++)a[i]=b
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
#define fi first
#define se second
using namespace std;
mt19937 rng_32(chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;
typedef long double ld;
typedef pair<int,int> P;
typedef double db;
const int mod=1e9+7;
const int seed=233;
const double PI=acos(-1.0);
const double eps=1e-7;
const int inf=0x3f3f3f3f;
const int max_n=100005;
ll ceil(ll x,ll y){if(x==0)return 0;if(y<0)x=-x,y=-y;bool sign=x>0;x=abs(x);return sign?(x+y-1)/y:-x/y;}
ll floor(ll x,ll y){if(x==0)return 0;if(y<0)x=-x,y=-y;bool sign=x>0;x=abs(x);return sign?x/y:-(x+y-1)/y;}
char str[max_n];
void rs(string& s){scanf(" %s",str);s=str;}
namespace {
    inline int Add(int x,int y){return (x+=y)>=mod?x-mod:x;}
    inline int Sub(int x,int y){return (x-=y)<0?x+mod:x;}
    inline int Mul(int x,int y) {return 1ll*x*y%mod;}
    inline int Pow(int x,int y=mod-2){int res=1;while(y){if(y&1)res=1ll*res*x%mod;x=1ll*x*x%mod;y>>=1;}return res;}
}
/**********************head************************/
ll toi(string s){
    ll res=0;
    for(auto x:s)res=res*10+x-'0';
    return res;
}
bool check1(string s){
    if(s.size()>=11)return false;
    for(auto x:s){
        if(x=='0')return false;
        else break;
    }
    ll val=toi(s);
    return val>=1&&val<=1000000000;
}
bool check2(string opt){
    if(opt=="-"||opt=="*"||opt=="/"||opt=="+")return true;
    return false;
}
char charset[100]={'0','1','2','3','4','5','6','7','8','9','+','*','-','/','='};
string s;
string x[100],eq,opt;
int now=0;
ll val[100];
bool check3(string opt){
    if(opt=="+")return val[0]+val[1]==val[2];
    if(opt=="-")return val[0]-val[1]==val[2];
    if(opt=="*")return val[0]*val[1]==val[2];
    if(opt=="/")return val[0]==val[1]*val[2];
    return false;
}
int check(string s){
    now=0;
    bool f=true;
    string res="";
    for(int i=0;i<s.size();i++){
        if(s[i]>='0'&&s[i]<='9')res+=s[i];
        else{
            x[now++]=res;
            res="";
            if(now==1){
                if(check2(s.substr(i,1)))opt=s.substr(i,1);
                else{
                    f=false;
                    break;
                }
            }
            else if(now==2){
                if(s[i]!='='){
                    f=false;
                    break;
                }
            }
            else if(now>=3){
                f=false;
                break;
            }
        }
    }
    x[now++]=res;
    for(int i=0;i<3;i++){
        f&=check1(x[i]);
    }
    f&=check2(opt);
    f&=now==3;
    /*
    cout<<now<<endl;
    for(int i=0;i<3;i++)cout<<i<<' '<<x[i]<<endl;
    cout<<opt<<endl;
    */
    if(f==false)return -1;
    for(int i=0;i<3;i++)val[i]=toi(x[i]);
    return check3(opt);
}
int main(){
    rs(s);
    if(check(s)==-1)printf("Format Error\n");
    else if(check(s)==1)printf("Correct\n");
    else{
        string t;
        for(int i=0;i<s.size();i++){
            for(int j=i+1;j<s.size();j++){
                for(int ic=0;ic<15;ic++){
                    for(int jc=0;jc<15;jc++){
                        t=s;
                        t[i]=charset[ic],t[j]=charset[jc];
                        if(check(t)==1){
                            printf("Typo: %s instead of %s\n",s.c_str(),t.c_str());
                            return 0;
                        }
                    }
                }
            }
        }
        printf("Math Error\n");
    }
    return 0;
}