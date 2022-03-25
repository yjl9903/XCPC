#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, a[maxn];

int main(){
    scanf("%d", &n); for (int i = 1; i <= n; i++) scanf("%d", a + i);
    vector<int> v;
    for (int i = 2; i < n; i++) if (a[i] == 0 && a[i - 1] && a[i + 1]) v.push_back(i);
    if (v.size() == 0) return puts("0"), 0;
    int ans = 1, flag = 1;
    for (int i = 1; i < v.size(); i++){
        if (flag && v[i] == v[i - 1] + 2) flag = 0;
        else flag = 1, ans++;
    }
    cout << ans << endl;
    return 0;
}