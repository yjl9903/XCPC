#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 10000 + 5;

int sum[maxn << 2], n;
PII que[maxn];
vector<int> all;

void pushup(int rt){ sum[rt] = sum[rt << 1] + sum[rt << 1 | 1]; }
void build(int l, int r, int rt){
    if (l == r){
        sum[rt] = 0;
        return;
    }
    int m = (l + r) >> 1;
    build(lson); build(rson);
    pushup(rt);
}
void update(int i, int x, int l, int r, int rt){
    if (l == r){
        sum[rt] += x;
        return;
    }
    int m = (l + r) >> 1;
    if (i <= m) update(i, x, lson);
    else update(i, x, rson);
    pushup(rt);
}
int query(int k, int l, int r, int rt){
    if (l == r){
        return l;
    }
    int m = (l + r) >> 1;
    if (k <= sum[rt << 1]) return query(k, lson);
    else return query(k - sum[rt << 1], rson);
}

int main(){
    int kase = 0;
    while (~scanf("%d", &n)){
        char cmd[10]; all.clear();
        for (int i = 0; i < n; i++) {
            scanf("%s", cmd);
            if (cmd[0] == 'q'){
                que[i].first = 0;
            } 
            else if (cmd[0] == 'i'){
                que[i].first = 1;
                int x; scanf("%d", &x);
                que[i].second = x;
                all.push_back(x);
            }
            else if (cmd[0] == 'o'){
                que[i].first = -1;
            }
        }
        sort(all.begin(), all.end()); /* all.erase(unique(all.begin(), all.end()), all.end()); */
        auto it = unique(all.begin(), all.end());
        all.resize(distance(all.begin(), it));
        printf("Case #%d:\n", ++kase);
        
        queue<int> q; 
        if(all.size()) build(1, all.size(), 1);
        for (int i = 0; i < n; i++){
            if (que[i].first == 1){
                q.push(que[i].second);
                int t = lower_bound(all.begin(), all.end(), que[i].second) - all.begin() + 1;
                // printf("+%d\n", t);
                update(t, 1, 1, all.size(), 1);
            }
            else if (que[i].first == -1){
                int t = lower_bound(all.begin(), all.end(), q.front()) - all.begin() + 1;
                q.pop();
                // printf("-%d\n", t);
                update(t, -1, 1, all.size(), 1);
            }
            else if (que[i].first == 0){
                int k = query(q.size() / 2 + 1, 1, all.size(), 1);
                // printf("%d %d ", q.size(), k);
                printf("%d\n", all[k - 1]);
            }
        }
    }
    return 0;
}