#include <iostream>
#include <map>
#include <utility>
#define PII pair<int,int>
using namespace std;
const int maxn = 500005;

int n;
map<PII, int> f;

int main(){
    while (cin >> n && n){
        f.clear();
        int x, y;
        while (n--){
            cin >> x >> y;
            f[make_pair(x, y)]++;
        }
        bool res = true;
        for (const auto& p : f){
            PII p2 = make_pair(p.first.second, p.first.first);
            if (p.second != f[p2]){
                res = false;
                break;
            }
        }
        cout << (res ? "YES" : "NO") << endl;
    }
    return 0;
}