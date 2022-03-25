#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 300 + 5;

string map[maxn][maxn];
int n, m;
vector< pair<PII,PII> > v;

void change(string& s1, string& s2){

}

int dfs(int d){
    
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> map[i][j];
    dfs(0);

    return 0;
}