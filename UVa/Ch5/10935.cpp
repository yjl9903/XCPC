#include <iostream>
#include <vector>
using namespace std;
vector<int> deck;
int main()
{
	//freopen("out.txt", "w", stdout);
	int n;
	while (cin >> n && n)
	{
		deck.clear();
		for (int i = 0; i <= n; i++)
			deck.push_back(i);
		int tot = 1, kase = 0;
		cout << "Discarded cards:";
		while (tot < n)
		{
			if (kase++) 
				cout << ",";
			
			cout << ' ' << deck[tot];
			tot++;
			deck.push_back(deck[tot++]);
			n++;
		}
		cout << endl << "Remaining card: " << deck[tot] << endl;
	}
	return 0;
}
