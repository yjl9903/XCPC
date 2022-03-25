#include <iostream>
#include <cstring>
#include <algorithm>
#include <utility>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 10000 + 5;

int n, l, p, vis[maxn];
PII stop[maxn];

int main(){
    while (cin >> n){
        for (int i = 0; i < n; i++)
            cin >> stop[i].first >> stop[i].second;
        cin >> l >> p;
        for (int i = 0; i < n; i++)
            stop[i].first = l - stop[i].first;
        stop[n] = make_pair(l, 0);
        sort(stop, stop + n);
        priority_queue<int> q; int res = 0, pos = 0, flag = 0;
        for (int i = 0; i <= n; i++){
            // if (p >= l) break;
            // if (stop[i].first <= p){
            //     q.push(stop[i].second);
            // }
            // else{
            //     while (p < stop[i].first){
            //         if (!q.empty()) break;
            //         p += q.top(); 
            //         q.pop();
            //         res++;
            //     }
            //     q.push(stop[i].second);
            // }
            // ↑ 忽略了节点之间的距离和费用，故WA
            int d = stop[i].first - pos;
            // cout << pos << ' ' << d << endl;
            while (p < d){
                if (q.empty()){
                    cout << -1 << endl;
                    flag = 1; break;
                }
                // cout << p << ' ' << q.top() << endl;
                p += q.top(); q.pop(); res++;
            }
            p -= d; pos = stop[i].first;
            q.push(stop[i].second);
        }
        if (!flag) cout << res << endl;
    }
    return 0;
}