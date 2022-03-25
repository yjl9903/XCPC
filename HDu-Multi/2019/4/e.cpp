#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

void build_tree(int left, int right, int deep)   
{  
    int i;  
    if (left == right) return ;  
    int mid = (left + right) >> 1;  
    int same = mid - left + 1; //位于左子树的数据  
    for (i = left; i <= right; ++i) {//计算放于左子树中与中位数相等的数字个数  
        if (tree[deep][i] < sorted[mid]) {  
            --same;  
        }  
    }  
    int ls = left;  
    int rs = mid + 1;  
    for (i = left; i <= right; ++i) {  
        int flag = 0;  
        if ((tree[deep][i] < sorted[mid]) || (tree[deep][i] == sorted[mid] && same > 0)) {  
            flag = 1;  
            tree[deep + 1][ls++] = tree[deep][i];  
            if (tree[deep][i] == sorted[mid])  
                same--;  
        } else {  
            tree[deep + 1][rs++] = tree[deep][i];  
        }  
        toleft[deep][i] = toleft[deep][i - 1]+flag;  
    }  
    build_tree(left, mid, deep + 1);  
    build_tree(mid + 1, right, deep + 1);  
}  
int query(int left, int right, int k, int L, int R, int deep)  
{  
    if (left == right)  
        return tree[deep][left];  
    int mid = (L + R) >> 1;  
    int x = toleft[deep][left - 1] - toleft[deep][L - 1];//位于left左边的放于左子树中的数字个数  
    int y = toleft[deep][right] - toleft[deep][L - 1];//到right为止位于左子树的个数  
    int ry = right - L - y;//到right右边为止位于右子树的数字个数  
    int cnt = y - x;//[left,right]区间内放到左子树中的个数  
    int rx = left - L - x;//left左边放在右子树中的数字个数  
    if (cnt >= k) {  
        return query(L + x, L + y - 1, k, L, mid, deep + 1);
    } else {  
        return query(mid + rx + 1, mid + 1 + ry, k - cnt, mid + 1, R, deep + 1); 
    }  
}  

int main() {
    
    return 0;
}