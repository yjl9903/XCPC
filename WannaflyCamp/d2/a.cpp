#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef __int128 ll;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;

int n;
ll a[maxn], suf[maxn];

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

ll join(ll a, ll b) {
    if (a == 0) return b;
    if (b == 0) return a * 10;
    ll x = b;
    while (x) x /= 10, a *= 10;
    return a + b;
}

int main(){
    int T, kase = 0; scanf("%d", &T);
    while (T--){
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            // scanf("%d", a + i);
            read(a[i]);
        }
        suf[n + 1] = 0;
        for (int i = n; i >= 1; i--) {
            suf[i] = max(suf[i + 1], a[i]);
        }
        ll ans = a[n];
        for (int i = 1; i < n; i++) {
            // dbg(a[i], suf[i + 1], join(a[i], suf[i + 1]));
            ans = max(join(a[i], suf[i + 1]), ans);
        }
        printf("Case #%d: ", ++kase);
        write(ans);
        puts("");
    }
    return 0;
}