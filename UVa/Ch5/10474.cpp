#include <iostream>
#include <algorithm>
using namespace std;
int N, Q, x[10000], kase = 0;
int main()
{

    while(cin >> N >> Q && N && Q)
    {
        for(int i = 0; i < N; cin >> x[i++]);
        sort(x, x + N);
        cout << "CASE# " << ++kase << ":" << endl;
        while(Q--)
        {
            int a, i;
            cin >> a;
            for(i = 0; i < N; i++)
            {
                if(a == x[i])
                    break;
            }
            if(i == N)
                cout<< a << " not found" << endl;
            else
                cout<< a << " found at " << i + 1 << endl;
        }
    }
    return 0;
}