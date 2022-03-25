#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 50 + 5;

int lc[maxn], rc[maxn], len = 0;
char pre[maxn], in[maxn], val[maxn];

void build(int l1, int r1, int l2, int r2){
    if (l1 >= r1 || l2 >= r2)   return;
    //cout << l1 << ' ' << r1 << ' ' << l2 << ' ' << r2 << endl;
    if (l1 + 1 <= r1)
        lc[l1] = l1 + 1;
    int root = 0;
    for (int i = 0; i <= r2 - l2; i++)
        if (pre[l1] == in[i + l2])
            root = i;
    if (root && l1 + root + 1 <= r1)
        rc[l1] = l1 + root + 1;
    build(l1 + 1, l1 + root, l2, l2 + root - 1);
    build(l1 + root + 1, r1, l2 + root + 1, r2);
}

void dfs(int p){
    if (p != -1){
        dfs(lc[p]);
        dfs(rc[p]);
        cout << pre[p];
    }
}

int main(){
    while (cin >> pre >> in){
        memset(lc, -1, sizeof lc);   memset(rc, -1, sizeof rc);
        len = strlen(pre);
        build(0, strlen(pre) - 1, 0, strlen(in) - 1);

        // for (int i = 0; i < len; i++)
        //    cout << lc[i] << ' ' << rc[i] << endl;

        dfs(0);
        cout << endl;
    }
    return 0;
}