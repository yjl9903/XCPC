#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxq = 50000 + 5;
const int maxz = 100000 + 5;

struct Ope{
    int x, y, z;
    int ty, id;
    Ope(int xx, int yy, int zz, int tt, int ii): x(xx), y(yy), z(zz), ty(tt), id(ii){}
    Ope(){}
};
vector<Ope> ope1, ope2, ope3;
vector<int> allZ;
int Q, ans[maxq], tree[maxz];
bool isQ[maxq];

inline int lowbit(int x){return x & -x;}
inline void update(int i, int x){
    while (i < maxz){
        tree[i] += x;
        i += lowbit(i);
    }
}
inline int query(int i){
    int s = 0;
    while (i > 0){
        s += tree[i];
        i -= lowbit(i);
    }
    return s;
}

bool cmp1(Ope a, Ope b){
    if (a.x == b.x) return a.id < b.id;
    return a.x < b.x;
}
bool cmp2(Ope a, Ope b){
    if (a.y == b.y) return a.id < b.id;
    return a.y < b.y;
}

void cdq2(int l, int r){
    if (l >= r) return;
    int m = (l + r) / 2;
    cdq2(l, m);
    ope3.clear();
    for (int i = l; i <= m; i++) if (ope2[i].ty == 0) ope3.push_back(ope2[i]);
    for (int i = m + 1; i <= r; i++) if (ope2[i].ty != 0) ope3.push_back(ope2[i]);
    sort(ope3.begin(), ope3.end(), cmp2);
    for (int i = 0; i < ope3.size(); i++){
        if (ope3[i].ty == 0) update(ope3[i].z, 1);
        else {
            int t = query(ope3[i].z);
            ans[ope3[i].id] += t * ope3[i].ty;
        }
    }
    for (int i = 0; i < ope3.size(); i++) if (ope3[i].ty == 0) update(ope3[i].z, -1);
    cdq2(m + 1, r);
}
void cdq(int l, int r){
    if (l >= r) return;
    int m  = (l + r) / 2;
    cdq(l, m);
    ope2.clear();
    for (int i = l; i <= m; i++) if (ope1[i].ty == 0) ope2.push_back(ope1[i]);
    for (int i = m + 1; i <= r; i++) if (ope1[i].ty != 0) ope2.push_back(ope1[i]);
    sort(ope2.begin(), ope2.end(), cmp1);
    cdq2(0, ope2.size() - 1);
    cdq(m + 1, r);
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        allZ.clear(); ope1.clear(); ms(isQ, 0); ms(tree, 0); ms(ans, 0);
        scanf("%d", &Q);
        int t, x1, y1, z1, x2, y2, z2;
        for (int i = 0; i < Q; i++){
            scanf("%d", &t);
            if (t == 1){
                scanf("%d%d%d", &x1, &y1, &z1);
                ope1.push_back(Ope(x1, y1, z1, 0, i));
                allZ.push_back(z1);
            }
            else if (t == 2){
                isQ[i] = 1;
                scanf("%d%d%d%d%d%d", &x1, &y1, &z1, &x2, &y2, &z2);
                ope1.push_back(Ope(x1 - 1, y1 - 1, z1 - 1, -1, i));
                ope1.push_back(Ope(x1 - 1, y1 - 1, z2, 1, i));
                ope1.push_back(Ope(x1 - 1, y2, z1 - 1, 1, i));
                ope1.push_back(Ope(x1 - 1, y2, z2, -1, i));
                ope1.push_back(Ope(x2, y1 - 1, z1 - 1, 1, i));
                ope1.push_back(Ope(x2, y1 - 1, z2, -1, i));
                ope1.push_back(Ope(x2, y2, z1 - 1, -1, i));
                ope1.push_back(Ope(x2, y2, z2, 1, i));
                allZ.push_back(z1 - 1);
                allZ.push_back(z2);
            }
        }  
        sort(allZ.begin(), allZ.end());
        vector<int>::iterator it = unique(allZ.begin(), allZ.end());
        allZ.resize(distance(allZ.begin(), it));
        for (int i = 0; i < ope1.size(); i++) ope1[i].z = lower_bound(allZ.begin(), allZ.end(), ope1[i].z) - allZ.begin() + 1;
        cdq(0, ope1.size() - 1);
        for (int i = 0; i < Q; i++) if (isQ[i]){
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}