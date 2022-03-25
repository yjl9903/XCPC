#include <iostream>
#include <cstring>
#include <queue>
#include <utility>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 10000 + 5;

int mark[maxn], prime[maxn], cnt = 0, vis[maxn];

void sieve(){
    for (int i = 2; i <= maxn; i++){
        if (!mark[i]) prime[cnt++] = i;
        for (int j = 0; j < cnt && prime[j] * i < maxn; j++){
            mark[prime[j] * i] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

int bfs(int a, int b){
    if (mark[b]) return -1;
    queue<PII> q; ms(vis, 0);
    vis[a] = 1; q.push(make_pair(a, 0));
    while (!q.empty()){
        PII t = q.front(); q.pop();
        if (t.first == b) return t.second;
        int c[4], d = 0, m = t.first;
        while (m) c[d] = m % 10, d++, m /= 10;
        for (int i = 0; i < 4; i++){
            for (int j = (i == 3 ? 1 : 0); j < 10; j++) if (j != c[i]){
                int x = c[i]; c[i] = j;
                int s = c[0] + 10 * c[1] + 100 * c[2] + 1000 * c[3];
                // cout << s << endl;
                c[i] = x;
                if (mark[s] || vis[s]) continue;
                // cout << s << endl;
                vis[s] = 1; q.push(make_pair(s, t.second + 1));
            }
        }
    }
    return -1;
}

int main(){
    sieve();
    int a, b, T; cin >> T;
    while (T--){
        cin >> a >> b;
        int res = bfs(a, b);
        if (res == -1) cout << "Impossible\n";
        else cout << res << endl;
    }
    return 0;
}