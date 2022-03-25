#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#define maxn 10010
using namespace std;

int wt1[maxn], wt2[maxn], len, best, bestSum; 
int lch[maxn], rch[maxn];

bool read(int *a)
{
    string x;
    if (!getline(cin, x)) return false;
    stringstream ss(x);
    int i = 0;
    while (ss >> a[i])
    {
        i++;
    }
    len = i - 1;
    return i;
}

int build(int l1, int r1, int l2, int r2)
{
    if (l1 > r1 || l2 > r2)    return 0;
    int root = wt2[r2], i = l1;
    while (wt1[i] != root)  i++;
    int cnt = i - l1;
    lch[root] = build(l1, i - 1, l2, l2 + cnt - 1);
    rch[root] = build(i + 1, r1, l2 + cnt, r2 - 1);
    return root;
}

void dfs(int x, int sum)
{
    sum += x;
    if (!lch[x] && !rch[x])
        if (sum < bestSum || (sum == bestSum && x < best))
        {
            bestSum = sum;
            best = x;
        }
    if (lch[x]) dfs(lch[x], sum);
    if (rch[x]) dfs(rch[x], sum);
}

int main()
{
    while (read(wt1))
    {
        read(wt2);
        build(0, len, 0, len);
        bestSum = 1 << 30;
        dfs(wt2[len], 0);
        cout << best << endl;
    }
    return 0;
}