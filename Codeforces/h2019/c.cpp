#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;

int n, l[maxn], r[maxn];
char s[maxn * 5];
map<int,int> mp1, mp2;

int main(){
    scanf("%d", &n);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        scanf("%s", s);
        vector<char> st;
        int len = strlen(s), l = 0, r = 0;
        for (int i = 0; i < len; i++) {
            if (s[i] == '(') {
                st.push_back('(');
                r++;
            } else if (s[i] == ')') {
                if (st.size() && st.back() == '(') st.pop_back(), r--;
                else l++;
            }
        } 
        if (l && r) continue;
        if (l) mp2[l]++;
        else if (r) mp1[r]++;
        else ans++;
    }
    ans /= 2;
    for (auto& x: mp1) {
        ans += min(x.second, mp2[x.first]);
    }
    cout << ans;
    return 0;
}