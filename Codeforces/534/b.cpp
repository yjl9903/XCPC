#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;

int n; char s[maxn];

int main(){
    scanf("%s", s);
    n = strlen(s);
    int cnt = 0;
    vector<char> st;
    for (int i = 0; i < n; i++) {
        if (!st.empty() && st.back() == s[i]) {
            st.pop_back(); cnt++;
        } else {
            st.push_back(s[i]);
        }
    }
    if (cnt % 2) puts("Yes");
    else puts("No");
    return 0;
}