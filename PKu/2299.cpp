#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
const int maxn = 500000 + 5;

struct Node{int pos; ll data;
    bool operator <(const Node& x)const{
        return data < x.data;
    }
}a[maxn];
int n, bit[maxn], b[maxn];

inline  int lowbit(int x){return x & (-x);}
void add(int x, int y){
    for (int i = x; i <= n; i += lowbit(i))
        bit[i] += y;
}
ll getSum(int x){
    ll sum = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        sum += bit[i];
    return sum; 
}

int main(){
    while (~scanf("%d", &n) && n){
        for (int i = 1; i <= n; scanf("%lld", &a[i].data), a[i].pos = i, i++);
        sort(a + 1, a + 1 + n);
        memset(bit, 0, sizeof bit);

        for (int i = 1; i <= n; i++)
            b[a[i].pos] = i;

        ll res = 0;
        
        for (int i = 1; i <= n; i++){
            res += i - getSum(b[i]) - 1;
            add(b[i], 1);
        }
        printf("%lld\n", res);
    }
    return 0;
}