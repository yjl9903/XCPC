#include <iostream>
using namespace std;

int solve(int& w)
{
    int w1, d1, w2, d2;
    cin >> w1 >> d1 >> w2 >> d2;
    int f1 = 1, f2 = 1;
    if (!w1)
        f1 = solve(w1);
    if (!w2)
        f2 = solve(w2);
    w = w1 + w2;
    return f1 && f2 && (w1 * d1 == w2 * d2);
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int w = 0;
        cout << (solve(w) ? "YES" : "NO") << endl;
        if (T)  cout << endl;
    }
    return 0;
}