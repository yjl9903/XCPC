#include <iostream>
#include <cstring>
#include <utility>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 100000 + 5;

int n;
PII a[maxn];

int main(){
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
    if (a[0].first < a[0].second) swap(a[0].first, a[0].second);
    for (int i = 1; i < n; i++){
        if (a[i].first < a[i].second) swap(a[i].first, a[i].second);
        if (a[i].second > a[i - 1].first) {
            cout << "NO"; return 0;
        }
        if (a[i].first > a[i - 1].first){
            swap(a[i].first, a[i].second);
        }
    }
    cout << "YES";
    return 0;
}