#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#ifdef XLor
  #define dbg(args...) do {cout << "debug -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

int n, a[maxn]; ll t;
vector<int> v;

struct bit{
    ll tree[maxn];
    inline int lowbit(int x){return x & -x;}
    void update(int i, ll x){
        while (i < maxn) tree[i] += x, i += lowbit(i);
    }
    ll query(int i){
        ll ans = 0;
        while (i) ans += tree[i], i -= lowbit(i);
        return ans;
    }
}b1, b2;

inline int getid(int x){
    return lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
}

int main(){
    scanf("%d%I64d", &n, &t); 
    int mn = 1e9 + 7; ll sum = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]); v.push_back(a[i]);
    }
    sort(v.begin(), v.end()); v.resize(unique(v.begin(), v.end()) - v.begin());
    for (int i = 0; i < n; i++){
        b1.update(getid(a[i]), a[i]);
        b2.update(getid(a[i]), 1);
    }

    while (true){
        int id = getid(t);
        ll sum = b1.query(id), cnt = b2.query(id);

    }

    printf("%I64d", ans);

    return 0;
}