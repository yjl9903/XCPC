#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

struct node{
    ll a, b, c;
    int id;
    bool operator < (const node &p) const{
        ll x = (a + b) * p.c;
        ll y = (p.a + p.b) * c;
        // return x < y;
        if (x != y) return x < y;
        return id < p.id; 
    }
}f[maxn];

int n;

// ci/(ai+bi+ci) > ci-1/(ai-1 + bi-1 + ci-1)

int main(){
    while (~scanf("%d", &n)){
        for (int i = 0; i < n; i++) scanf("%lld%lld%lld", &f[i].a, &f[i].b, &f[i].c), f[i].id = i + 1;
        sort(f, f + n);
        for (int i = 0; i < n; i++){
            printf("%d%c", f[i].id, i == n - 1 ? '\n' : ' ');
        }
    }
    return 0;
}