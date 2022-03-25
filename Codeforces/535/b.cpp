#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;

int n, d[maxn];
multiset<int> st;

int main(){
    scanf("%d", &n); 
    for (int i = 1, x; i <= n; i++) {
        scanf("%d", &x); st.insert(x);
    }
    int ansy = *st.rbegin();
    for (int i = 1; i * i <= ansy; i++) {
        if (ansy % i) continue;
        st.erase(st.find(i));
        if (i * i != ansy) st.erase(st.find(ansy / i));
    }
    cout << *st.rbegin() << ' ' << ansy << endl;
    return 0;
}