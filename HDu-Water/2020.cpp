#include <iostream>
#include <cstring>
#include <utility>
#include <cmath>
#include <functional>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef pair<int, int> PII;
typedef long long ll;
const int maxn = 1000 + 5;

int n;
PII a[maxn];

bool cmp(PII a, PII b){
    if (a.first == b.first) return a.second > b.second;
    return a.first > b.first;
}

int main(){
    while (cin >> n && n){
        for (int i = 0; i < n; i++){
            cin >> a[i].second;
            a[i].first = abs(a[i].second);
        }
        sort(a, a + n, cmp);
        for (int i = 0; i < n; i++){
            if (i) cout << ' ';
            cout << a[i].second;
        }
        cout << endl;
    }
    return 0;
}