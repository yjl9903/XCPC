#include <iostream>
#include <cstring>
#include <utility>
#include <algorithm>
#include <vector>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 1000 + 5;

int n, m;
PII c[maxn];
char res[maxn];
set<int> p;

int main(){
    cin >> n >> m; ms(res, 0);
    for (int i = 0; i < m; i++) cin >> c[i].first >> c[i].second;
    // sort(c, c + m);
    
    for (int i = 0; i < m; i++) p.insert(c[i].first), p.insert(c[i].second);
    set<int>::iterator it = p.begin();

    int a = *it, k = 1, b, t = 0; it++;
    while (k < a) res[k++] = t + '0';
    while (it != p.end()){
        // cout << b << endl;
        b = *it;
        int m = (a + b) / 2;
        // cout << k << ' ' << m << ' ' << b << endl;
        if (k <= m) t ^= 1;
        while (k <= m) res[k++] = t + '0';
        if (k <= b) t ^= 1;
        while (k <= b) res[k++] = t + '0';
        // t ^= 1;
        a = b;
        it++;
    }
    while (k <= n) res[k++] = '0';
    cout << res + 1;

    return 0;
}