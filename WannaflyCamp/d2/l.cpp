#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
// typedef long long ll;
typedef __int128 ll;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;

inline void read(__int128 &x){
	char ch;
	bool flag=false;
	for (ch=getchar();!isdigit(ch);ch=getchar())if (ch=='-') flag=true;
	for (x=0;isdigit(ch);x=x*10+ch-'0',ch=getchar());
	x=flag?-x:x;
}
inline void write(__int128 x){
	static char s[100];
	if (x<0)    {    putchar('-'); x=-x;}
	if(!x){ putchar('0'); return; }
	__int128 len=0; for(;x;x/=10) s[len++]=x % 10+'0';
	for(__int128 i=len-1;i>=0;--i) putchar(s[i]);
}

ll l, r;
ll cal(ll x) {
    return (x + 2) * (x + 1) * x * (x - 1) / 24;
}

int main(){
    int T, kase = 0; scanf("%d", &T);
    while (T--){
        // scanf("%d%d", &l, &r);
        read(l); read(r);
        ll ans = cal(r) - cal(l) - (r - l) * (l - 1) * l * (2 * l - 1) / 6;
        // printf("Case #%d: %lld\n", ++kase, ans);
        printf("Case #%d: ", ++kase);
        write(ans);
        puts("");
    }
    return 0;
}