#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

struct node{
    int l, r;
};
vector<node> a;
bool cmp(node a, node b){
    if (a.r >= a.l && b.l > b.r) return true;
    if (a.r < a.l && b.l <= b.r) return false;
    if (a.r >= a.l && b.r >= b.l) return a.l < b.l;
    return a.r > b.r;
}
int n, ans;
char s[maxn];

int main(){
    int T; scanf("%d", &T);
    while (T--){
        ans = 0; a.clear();
        scanf("%d", &n);
        for (int i = 0; i < n; i++){
            stack<char> st;
            scanf("%s", s); int len = strlen(s);
            int x = 0, y = 0;
            for (int j = 0; j < len; j++){
                if (s[j] == '('){
                    st.push('('); y++;
                }
                else if (s[j] == ')'){
                    if (!st.empty() && st.top() == '(') st.pop(), ans++, y--;
                    else x++;
                }
            }
            // a[i].l = x, a[i].r = y;
            if (x || y) a.push_back(node{x, y});
        }
        sort(a.begin(), a.end(), cmp);
        int t = 0;
        for (int i = 1; i < a.size(); i++){
            t += a[i - 1].r;
            if (a[i].l > t){
                ans += t; t = 0;
            }
            else {
                ans += a[i].l;
                t -= a[i].l;
            }
        }
        printf("%d\n", ans * 2);
    }
    return 0;
}