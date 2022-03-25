#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 5000 + 5;

int a[maxn], n, bit[maxn], k;

inline int lowbit(int x){return x & (-x);}
void add(int x, int y){
    for (int i = x; i <= n; i += lowbit(i))
        bit[i] += y;
}
int getSum(int x){
    int sum = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        sum += bit[i];
    return sum; 
}

int main(){
    cin >> n >> k;
    double res = 0;
    for (int i = 1; i <= n; cin >> a[i], add(i, a[i]), i++);
    for (int i = 1; i <= n; i++){
        int s1 = 0;
        for (int j = 0; j < k - 1 && i + j <= n; j++) s1 += a[i + j];
        for (int j = i + k - 1; j <= n; j++){
            s1 += a[j];
            double t = double(s1) / double(j - i + 1);
            res = max(res, t);
        }
    }
    printf("%.6f", res);
    return 0;
}