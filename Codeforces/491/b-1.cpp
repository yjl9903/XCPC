#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int n, sum = -1;
    double a[105], ans = 0;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        ans += a[i];
    }
    sort(a, a + n);
    for (int i = 0; i < n; i++)
    {
        // cout << ans / n << endl;
        if (ans / n >= 4.5)
        {
            sum++;
            break;
        }
        else
        {
            ans -= a[i];
            ans += 5;
            sum++;
        }
        cout << sum << endl;
    }
    cout << sum << endl;
    return 0;
}