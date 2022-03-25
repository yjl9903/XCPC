#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 200000 + 5;

int n; PII a[maxn];
ll sum = 0;

int main(){
    scanf("%d", &n); for (int i = 1; i <= n; i++) scanf("%d", &a[i].first), sum += a[i].first, a[i].second = i;
    sort(a + 1, a + 1 + n); 
    vector<int> v;
    for (int i = 1; i <= n; i++){
        // cout << a[i] << endl;
        ll x = sum - a[i].first;
        if (i < n && a[n].first + a[n].first == x) v.push_back(a[i].second);
        else if (i == n && a[n - 1].first + a[n - 1].first == x) v.push_back(a[i].second);
    }
    printf("%d\n", v.size());
    for (int x : v) printf("%d ", x);
    return 0;
}