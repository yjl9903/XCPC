#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

char a[maxn], b[maxn];
int n, res = 0, vis[30];

int main(){
    cin >> n >> a >> b;
    for (int i = 0; i < n / 2; i++){
        // vector<char> v;
        // v.push_back(a[i]); v.push_back(b[i]); v.push_back(a[n - 1 - i]); v.push_back(b[n - 1 - i]);
        // sort(v.begin(), v.end());
        // if (v[0] == v[1] && v[2] == v[3]) continue;
        ms(vis, 0);
        vis[a[i] - 'a']++; vis[b[i] - 'a']++; vis[a[n - 1 - i] - 'a']++; vis[b[n - 1 - i] - 'a']++;
        vector<int> v;
        for (int i = 0; i < 26; i++){
            if (vis[i]) v.push_back(vis[i]);
        }
        if (v.size() == 2 && v[0] != 2) res++;
        else if (v.size() == 3){
            if (a[i] == a[n - 1 - i]) res += 2;
            else res++;
        }
        else if (v.size() == 4) res += 2;
    }
    if (n % 2){
        if (a[n / 2] != b[n / 2]) res++;
    }
    cout << res;
    return 0;
}