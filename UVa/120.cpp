#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;

int a[maxn];
char s[1000];
vector<int> v;

int main(){
    while (cin.getline(s, 1000)){
        v.clear();
        stringstream ss(s);
        int cnt = 0;
        while (ss >> a[cnt++]);
        cnt--;
        for (int i = 0; i < cnt; i++){
            if (i) cout << ' ';
            cout << a[i];
        }
        cout << endl;
        for (int i = cnt - 1; i > 0; i--){
            int t = a[0], k = 0;
            for (int j = 1; j <= i; j++) if (a[j] > t) {
                t = a[j]; k = j;
            }
            if (k == i) continue;
            if (k != 0) v.push_back(cnt - k);
            v.push_back(cnt - i);
            // reverse(a + k, a + cnt);
            if (k != 0) reverse(a, a + k + 1);
            reverse(a, a + i + 1);
        }
        v.push_back(0);
        for (int i = 0; i < v.size(); i++){
            if (i) cout << ' ';
            cout << v[i];
        }
        cout << endl;
    }
    return 0;
}