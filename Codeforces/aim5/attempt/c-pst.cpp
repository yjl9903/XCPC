#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
// const int maxn = 132674 + 5;
const int maxn = 200000 + 5;

struct node{
    int x1, y1, x2, y2;
}a[maxn];
bool cmp(node& a, node& b){
    if (a.x2 != b.x2) return a.x2 < b.x2;
    if (a.y2 != b.y2) return a.y2 < b.y2;
    if (a.x1 != b.x1) return a.x1 < b.x1;
    return a.y1 < b.y2;
}

int tree[2][2 * maxn];
inline int lowbit(int x){return x & -x;}
inline void update(int i, int x, int t){
    while (i < 2 * maxn) tree[t][i] += x, i += lowbit(i);
}
inline int query(int i, int t){
    int s = 0;
    while (i > 0) s += tree[t][i], i -= lowbit(i);
    return s;
}

int n;
vector<int> v, v2;

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d%d", &a[i].x1, &a[i].y1, &a[i].x2, &a[i].y2);
        v.push_back(a[i].x1), v.push_back(a[i].x2);
        v2.push_back(a[i].y1), v2.push_back(a[i].y2);
    }
    sort(a, a + n, cmp);
    sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end());
    sort(v2.begin(), v2.end()); v2.erase(unique(v2.begin(), v2.end()), v2.end());
    for (int i = 0; i < n; i++) {
        int lp = lower_bound(v.begin(), v.end(), a[i].x1) - v.begin() + 1;
        int rp = lower_bound(v.begin(), v.end(), a[i].x2) - v.begin() + 1;
        update(lp, 1, 0); update(rp + 1, -1, 0);
        lp = lower_bound(v2.begin(), v2.end(), a[i].y1) - v2.begin() + 1;
        rp = lower_bound(v2.begin(), v2.end(), a[i].y2) - v2.begin() + 1;
        update(lp, 1, 1); update(rp + 1, -1, 1);
    }
    for (int i = 0; i < v.size(); i++){
        int s = query(i + 1, 0);
        if (s >= n - 1){
            for (int j = 0; j < v2.size(); j++){
                int s2 = query(j + 1, 1);
                if (s2 >= n - 1){
                    int c = 0, tx = v[i], ty = v2[j];
                    for (int k = 0; k < n; k++){
                        if (a[k].x1 <= tx && tx <= a[k].x2 && a[k].y1 <= ty && ty <= a[k].y2) c++;
                    }
                    if (c >= n - 1){
                        printf("%d %d\n", tx, ty);
                        return 0;
                    }
                }
            }
        }
    }
    return 0;
}