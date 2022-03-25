#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n;
vector<int> v;

int main(){
    while (cin >> n){
        v.clear();
        int s = 0, i = 2;
        for (; s + i <= n; i++){
            s += i;
            v.push_back(i);
        }
        int k = n - s; i--;
        if (k == i) v.back()++, k--;
        for (int i = 0; i < k; i++) v[v.size() - 1 - i]++;
        for (int i = 0; i < v.size(); i++) {
            if (i) cout << ' ';
            cout << v[i];
        }
        cout << endl;
    }
    return 0;
}