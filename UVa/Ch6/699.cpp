#include <iostream>
#include <cstring>
#define maxn 1010
using namespace std;

int sum[maxn] = {0};

void build(int p)
{
    int v;
    cin >> v;
    if (v == -1)    return;
    sum[p] += v;
    build(p - 1);
    build(p + 1);
}

bool read()
{
    int v, p = maxn / 2;
    cin >> v;
    if (v == -1)    return false;
    sum[p] = v;
    build(p - 1);
    build(p + 1);
    return true;
}

int main()
{
    int kase = 0;
    while (read())
    {
        int p = 0, t = 0;
        while (!sum[p]) p++;
        
        cout << "Case " << ++kase << ":\n";
        while (sum[p])
        {
            if (t++)
                cout << ' ';
            cout << sum[p++];
        }
        cout << endl << endl;
        memset(sum, 0, sizeof sum);
    }
    return 0;
}