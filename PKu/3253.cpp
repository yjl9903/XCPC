#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <functional>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 20000 + 5;

int len[maxn], n;

int main(){
    while (cin >> n){
        priority_queue<ll, vector<ll>, greater<int> > q;
        for (int i = 0, x; i < n; cin >> x, q.push(x), i++);
        ll res = 0;
        while (q.size() > 1){
            ll x = q.top(); q.pop();
            ll y = q.top(); q.pop();
            res += x + y;
            q.push(x + y);
        }
        cout << res << endl;
    }
    return 0;
}