#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int x;
set<int> st;

int main() {
    cin >> x;
    st.insert(x); x++;
    while (true) {
        while (x % 10 == 0) x /= 10;
        if (st.count(x)) break;
        st.insert(x);
        x++;
    }
    cout << (int)st.size();
    return 0;
}