#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;

int n, m, a[maxn], b[maxn];
vector<int> v;

int check(int x){
    int cnt = 0;
    for (int i = 0; i < v.size(); i++) cnt += v[i] / x;
    return cnt >= n;
}

int main(){
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0, x; i < m; i++) cin >> x, a[x]++;
    for (int i = 1; i <= 100; i++) if (a[i]) v.push_back(a[i]);
    sort(v.begin(), v.end());

    int cnt = 0;
    for (int i = v.back(); i > 0; i--){
        if (check(i)) {
            cnt = i; 
            break;
        }
    }
    cout << cnt;
    return 0;
}