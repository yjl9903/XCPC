#include <iostream>
#include <cstring>
#include <utility>
#include <string>
#include <vector>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 1000 + 5;

string s;
vector<PII> v;

int main(){
    int T, kase = 0; cin >> T;
    while (T--){
        cin >> s;
        v.clear();
        for (int i = 0; i < s.length(); i++){
            PII x = {s[i], i};
            v.push_back(x);
        }
        sort(v.begin(), v.end());
        int flag = 0, res = 1 << 30;
        for (int i = 1; i < v.size(); i++){
            if (v[i].first == v[i - 1].first){
                res = min(res, v[i].second - v[i - 1].second);
                flag = 1;
            }
        }
        if (!flag) res = -1;
        cout << "Case #" << ++kase << ": " << res << endl;
    }
    return 0;
}