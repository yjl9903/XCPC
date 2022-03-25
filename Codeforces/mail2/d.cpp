#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 3000 + 5;

int n;
char s1[maxn][maxn], s2[maxn][maxn];

pair<string,string> cmp(int k){
    int flag = 0, n = strlen(s1[k]), a = 0, b = 0;
    for (int i = 0; i < n; i++){
        if (s1[k][i] != s2[k][i]){
            if (!flag) a = i;
            flag++;
        }
        else if (flag) return make_pair("#", "#");
    }
    string r1, r2;
    for (int i = a; i - a < flag; i++) r1.push_back(s1[k][i]), r2.push_back(s2[k][i]);
    return make_pair(r1, r2);
}

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%s", s1[i]);
    for (int i = 0; i < n; i++) scanf("%s", s2[i]);
    pair<string,string> k = cmp(0);
    if (k.first == "#") return puts("NO"), 0;
    for (int i = 1; i < n; i++){
        pair<string,string> t = cmp(i);
        if (t.first != k.first || t.second != k.second) return puts("NO"), 0;
    }
    puts("YES"); cout << k.first << endl << k.second;
    return 0;
}