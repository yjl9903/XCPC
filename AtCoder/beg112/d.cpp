#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

vector<int> v;
int n, m;

int main(){
    cin >> n >> m;
    int ans = 0;
    for (int i = 1; i * i <= m; i++){
        if (m % i) continue;
        v.push_back(i);
        if (i * i != m) v.push_back(m / i);
    }
    sort(v.begin(), v.end());
    int k = lower_bound(v.begin(), v.end(), n) - v.begin();
    cout << m / v[k];
    return 0;
}