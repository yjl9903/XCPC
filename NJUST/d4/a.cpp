#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <iostream>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 20 + 5;

int n, m, r, course[maxn];
map<string, int> cid, sid;
set<int> time[maxn], stu[maxn];
set<int>::iterator it;
bool stuc[maxn][40];

struct request{
    string st, ct;
    int id;
}re[500];
bool cmp(request &a, request &b){
    int x = cid[a.ct], y = cid[b.ct];
    if (x != y) return x < y;
    return a.id < b.id;
}

int main(){
    int kase = 0;
    while (~scanf("%d%d%d", &n, &m, &r)){
        cid.clear(); sid.clear();
        ms(stuc, 0);
        for (int i = 1; i <= n; i++){
            string x; cin >> x; sid[x] = i;
            stu[i].clear();
        }
        for (int i = 1; i <= m; i++){
            string y; cin >> y; cid[y] = i;
            int x;
            scanf("%d", &x); course[i] = x;
            scanf("%d", &x); time[i].clear();
            for (int k = 1, j; k <= x; k++){
                scanf("%d", &j); time[i].insert(j);
            }
        }
        string st, ct;
        for (int i = 0; i < r; i++){
            cin >> st >> ct;
            re[i].st = st; re[i].ct = ct;
            re[i].id = i;
        }
        sort(re, re + r, cmp);
        int ans = 0, s, c;
        for (int i = 0; i < r; i++){
            s = sid[re[i].st]; c = cid[re[i].ct];
            if (course[c] == 0) continue;
            if (stuc[s][c]) continue;
            int flag = 1;
            for (it = time[c].begin(); it != time[c].end(); it++){
                if (stu[s].count(*it)) {
                    flag = 0; break;
                }
            }
            if (flag){
                for (it = time[c].begin(); it != time[c].end(); it++){
                    stu[s].insert(*it);
                }
                stuc[s][c] = 1;
                course[c]--; ans++;
            }
        }
        printf("Case %d: %d\n", ++kase, ans);
    }
    return 0;
}