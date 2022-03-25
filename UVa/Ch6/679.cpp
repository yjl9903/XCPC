#include <iostream>
using namespace std;

int main()
{
    int T, n, l;
    cin >> T;
    while (T--)
    {
        cin >> n >> l;
        int k = 1;
        for (int i = 0; i < n - 1; i++)
            if (l % 2)
                k = k * 2, l = (l + 1) / 2;
            else 
                k = k * 2 + 1, l /= 2;
        cout << k << endl;
    }
    cin >> T;
    return 0;
}