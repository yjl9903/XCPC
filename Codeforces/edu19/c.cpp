#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

char s[maxn], m[maxn];
int n, p[maxn];

int main(){
    scanf("%s", s); n = strlen(s);
    string tmp, ans;
    m[n - 1] = s[n - 1]; p[n - 1] = n - 1;
    for (int i = n - 2; i >= 0; i--){
        if (s[i] <= m[i + 1]){
            m[i] = s[i]; p[i] = i;
        }
        else {
            m[i] = m[i + 1]; p[i] = p[i + 1];
        }
    }
    for (int i = 0; i < n;){
        char ch = m[i]; int pos = p[i];
        while (tmp.size() && ch >= tmp.back()){
            ans.push_back(tmp.back()); tmp.pop_back();
        }
        for (; i <= pos; i++) tmp.push_back(s[i]);
        ans.push_back(tmp.back()); tmp.pop_back();
    }
    while (!tmp.empty()){
        char ch = tmp.back(); 
        tmp.pop_back(); ans.push_back(ch);
    }
    cout << ans;
    return 0;
}