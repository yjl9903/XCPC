#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <map>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 100000 + 5;

int n;

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d", &n);
        map<PII, int> mp;
        set<PII> st;
        int ans = 0;
        for (int i = 0, tot = 0, k, x, y; i < n; i++, tot ^= 1){
            scanf("%d", &k);
            set<PII> tmp;
            map<PII, int> tmp2;
            while (k--){
                scanf("%d%d", &x, &y);
                tmp.insert(make_pair(x, y));
            }
            // set_intersection(st.begin(), st.end(), tmp.begin(), tmp.end(), inserter(tmp2, tmp2.begin()));
            // st = tmp2;
            for (auto &x : tmp){
                // printf("%d %d\n", x.first, x.second);
                int k = mp[x] + 1;
                tmp2[x] = k;
                ans = max(ans, k);
            }
            mp = tmp2;
        }
        printf("%d\n", ans);
    }
    return 0;
}