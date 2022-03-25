#include <iostream>
#include <cmath>
#include <map>
#include <vector>
using namespace std;
vector<int> seq, seq2;
map<vector<int>, int> check;
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		check.clear();
		seq.clear();
		int n;
		cin >> n;
		while (n--)
		{
			int x;
			cin >> x;
			seq.push_back(x);
		}
		check[seq] = 1;
		while (true)
		{
			for (int i = 1; i < seq.size(); i++)
				seq2.push_back(abs(seq[i] - seq[i - 1]));
			seq2.push_back(abs(seq[seq.size() - 1] - seq[0]));
			seq = seq2;
			seq2.clear();
			int flag = 1;
			for (int i = 0; i < seq.size(); i++)
				if (seq[i] != 0)
					flag = 0;
			if (flag)
			{
				cout << "ZERO" << endl;
				goto ends;
			}
			if (check.count(seq))
			{
				cout << "LOOP" << endl;
				goto ends;
			}
			check[seq] = 1;
		}
	ends: ;
	}
	return 0;
}