#include <iostream>
#include <cstring>
#include <algorithm>
#include <utility>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 2000 + 5;

int n, m, head, rear;
PII q[maxn];

bool solve(int head, int rear){
    for (int i = head + 1; i <= rear; i++)
        if (q[i].first > q[head].first)
            return false; //need move
    return true; //print
}

int main(){
    int T; cin >> T;
    while (T--){
        cin >> n >> m;
        for (int i = 0; i < n; i++)
            cin >> q[i].first, q[i].second = i;
        head = 0, rear = n - 1;
        int res = 0;
        while (q[head].second != m || !solve(head, rear)){
            //cout << head << ' ' << rear << endl;
            if (solve(head, rear)){
                head++;
                res++;
            }
            else {
                q[++rear] = q[head++];
            }
            //flag = 1;
        }
        cout << res + 1 << endl;
    }
    return 0;
}