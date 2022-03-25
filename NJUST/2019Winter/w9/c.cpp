#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int mod = 998244353;
const int maxn = 500000 + 5;

vector<int> v;
struct fhqTreap{
    int ch[maxn][2], size[maxn], key[maxn], val[maxn], rnd[maxn], rev[maxn], root, tot;
    fhqTreap(){ root = tot = 0; }
    void clear(){ root = tot = 0; }
    int node(int v, int x){
        key[++tot] = v; rnd[tot] = rand(); val[tot] = x;
        size[tot] = 1; ch[tot][0] = ch[tot][1] = rev[tot] = 0;
        return tot;
    }
    void pushup(int x){size[x] = size[ch[x][0]] + size[ch[x][1]] + 1;}
    void pushdown(int x){
        if (!rev[x]) return;
        swap(ch[x][0], ch[x][1]);
        if (ch[x][0]) rev[ch[x][0]] ^= 1; 
        if (ch[x][1]) rev[ch[x][1]] ^= 1;
        rev[x] = 0;
    }
    void split(int now, int k, int &x, int &y){
        if (!now) {
            x = y = 0; return;
        }
        pushdown(now);
        if (size[ch[now][0]] < k){
            x = now; 
            split(ch[now][1], k - size[ch[now][0]] - 1, ch[now][1], y);
        }
        else {
            y = now; 
            split(ch[now][0], k, x, ch[now][0]);
        }
        pushup(now);
    }
    int merge(int x, int y){
        if (!x || !y) return x + y;
        if (rnd[x] < rnd[y]){
            pushdown(x);
            ch[x][1] = merge(ch[x][1], y);
            pushup(x); return x;
        }
        else {
            pushdown(y);
            ch[y][0] = merge(x, ch[y][0]);
            pushup(y); return y;
        }
    }
    void reverse(int l, int r){
        int x, y, z;
        split(root, l - 1, x, y);
        split(y, r - l + 1, y, z);
        rev[y] ^= 1;
        root = merge(x, merge(y, z));
    }
    void print(int x){
        if (!x) return;
        pushdown(x);
        print(ch[x][0]);
        v.push_back(val[x]);
        print(ch[x][1]);
    }
}f;

int n, m, a[maxn], tag[maxn];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    set<PII> st;
    for (int q = 0, t, r; q < m; q++) {
        scanf("%d%d", &t, &r);
        if (st.empty()) {
            st.insert({r, t}); continue;
        }
        for (auto it = st.begin(); it != st.end(); ) {
            if (it->first <= r) st.erase(it++);
            else {
                st.insert({r, t}); break;
            }
        }
        if (st.empty()) st.insert({r, t});
    }
    auto it = st.rbegin(); int last = 1;
    // cout << st.size() << endl;
    sort(a, a + it->first); if (it->second == 2) reverse(a, a + it->first), last = 2;
    it++;
    for (int i = 0; i < n; i++) f.root = f.merge(f.root, f.node(i + 1, a[i]));
    for (; it != st.rend(); it++) {
        if (it->second == last) continue;
        last = it->second;
        f.reverse(1, it->first);
    }
    f.print(f.root);
    for (int& x: v) printf("%d ", x);
    return 0;
}