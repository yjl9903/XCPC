#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 100000 + 5;

int n, m, cnt = 0;
vector<PII> v;
int gcd(int a, int b){ return b == 0 ? a : gcd(b, a % b); }

int main(){
    ios::sync_with_stdio(false);
    cin >> n >> m; v.clear();
    if (m < n - 1){
        cout << "Impossible"; return 0;
    }
    for (int i = 1; i <= n; i++){
        for (int j = i + 1; j <= n; j++){
            if (gcd(i, j) == 1) v.emplace_back(i, j), cnt++;
        }
        if (cnt >= m) break;
    }
    if (cnt < m) {cout << "Impossible"; return 0;}
    cout << "Possible\n";
    for (int i = 0; i < m; i++) cout << v[i].first << ' ' << v[i].second << endl;
    return 0;
}