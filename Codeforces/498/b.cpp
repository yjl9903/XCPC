#include <iostream>
#include <cstring>
#include <utility>
#include <vector>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 2000 + 5;

int n, k, t[maxn];
PII a[maxn];
vector<int> v;

int main(){
    ios::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> a[i].first, a[i].second = i;
    sort(a, a + n); reverse(a, a + n);
    int res = 0;
    for (int i = 0; i < k; i++){
        res += a[i].first;
        v.push_back(a[i].second);
    }
    cout << res << endl;
    sort(v.begin(), v.end());
    // for (int i = 0; i < v.size(); i++) cout << v[i] << ' '; cout << endl;
    if (v.size() == 1){
        cout << n; return 0;
    }
    cout << v[0] + 1;
    // if (v.size() == 1) return 0;
    for (int i = 1; i < v.size() - 1; i++){
        cout << ' ' << v[i] - v[i - 1];
    }
    cout << ' ' << n - 1 - v[v.size() - 2];
    return 0;
}