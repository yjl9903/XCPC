#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

char s[maxn];
int n, m, vis[maxn];

int main(){
    scanf("%d%d", &n, &m);
    string str = "";
    for (int i = 1, x; i <= m; i++){
        scanf("%d%s",&x, s);
        string t(s);
        if (t != str){
            str = t; vis[x] = 1;
        }
    }
    vector<int> v;
    for (int i = 1; i <= n; i++) if (!vis[i]) v.push_back(i);
    for (int i = 0; i < v.size(); i++){
        if (i) putchar(' ');
        printf("%d", v[i]);
    }
    return 0;
}