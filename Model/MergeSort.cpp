// PKu1804
// 归并排序求逆序对数量

#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a, b) memset(a, b, sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int a[maxn], b[maxn], n, res;

void merge(int l, int r){
    if (l >= r) return;
    int m = (l + r) / 2;
    merge(l, m); merge(m + 1, r);
    int i = l, j = m + 1, k = l;
    while (i <= m && j <= r){
        if (a[i] > a[j]) b[k++] = a[j++], res += m - i + 1;
        else b[k++] = a[i++];
    }
    while (i <= m) b[k++] = a[i++];
    while (j <= r) b[k++] = a[j++];
    for (int i = l; i <= r; i++) a[i] = b[i];
}

int main(){
    int T, kase = 0;
    cin >> T;
    while (T--){
        cin >> n;
        for (int i = 0; i<n; cin>> a[i++]);
        res = 0;
        merge(0, n - 1);
        cout << "Scenario #" << ++kase << ":\n";
        cout << res << endl;
        if (T) cout << endl;
    }
    return 0;
}