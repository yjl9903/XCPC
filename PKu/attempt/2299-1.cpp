#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 500005;

ll a[maxn], b[maxn], tree[maxn];
int n;

inline int lowbit(int x){return x & (-x);}

void add(int x, int y){
    for (int i = x; i <= n; i += lowbit(i))
        tree[i] += y;
}

int getSum(int x){
    int sum = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        sum += tree[i];
    return sum;
}

int main(){
    while (cin >> n && n){
        for (int i = 1; i <= n; cin >> a[i], b[i] = a[i], i++);
        memset(tree, 0, sizeof tree);
        sort(b + 1, b + n + 1);

        ll res = 0;
        for (int i = 1; i <= n; i++){
            res += i - getSum(a[i]);
            add(a[i], 1);
        }
        cout << res << endl;
    }
    return 0;
}