#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 200000 + 5;

int n, a[maxn];
vector<int> v;

int main(){
    int T; scanf("%d", &T);
    while (T--){
        v.clear();
        scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%d", &a[i]);
        for (int i = 0; i < n; i++){
            if (a[i] != -1 && a[i] % n == i)
                v.push_back(a[i]);
            else if (a[i] != -1){
                
            }
        }
        sort(v.begin(), v.end());
        
    }
    return 0;
}