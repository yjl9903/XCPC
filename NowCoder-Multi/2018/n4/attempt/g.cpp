#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <utility>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 100000 + 5;

map<int, int> mp;
map<int, int>::iterator it;
vector<PII> v;
int n, m, a[maxn];

int main(){
    int T; scanf("%d", &T);
    while (T--){
        mp.clear(); v.clear();
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) scanf("%d", &a[i]), mp[a[i]]++;

        int tot = 0;
        for (it = mp.begin(); it != mp.end(); it++){
            if (it -> second > tot){
                v.clear(); v.push_back(*it);
            }
            else if (it -> second == tot){
                v.push_back(*it);
            }
        }
        for (int i = 0; i < v.size() - 1; i++){
            mp[v[i].first]--; m--;
        }
        if (m < 0){
            printf("-1\n"); continue;
        }
        PII res = v.back();

        for (it = mp.begin(); it != mp.end(); it++){
            if (it -> second <= m) m -= it -> second, it -> second = 0;
            else break;
        }
        v.clear(); int k = 0;
        for (; it != mp.end(); it++){
            v.push_back(*it);
            if (it -> second > k) res = *it, k = it -> second;
        }

        if (v[0] != res || m == 0){
            printf("%d\n", res.first);
        }
        else{
            k = 0; PII t;
            for (int i = 1; i < v.size(); i++){
                if (v[i].second > k) k = v[i].second, t = v[i];
            }
        }
    }
    return 0;
}