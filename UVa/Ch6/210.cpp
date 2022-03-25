#include <iostream>
#include <cstring>
#include <sstream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;
int var[26] = { 0 };
deque<int> exc, wait;
vector<vector<int>> opc, opd;
int main()
{
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int T, kase = 0;
	cin >> T;
	while (T--)
	{
		opc.clear(); opd.clear(); wait.clear();  memset(var, 0, sizeof var);
		int n, time[5], q, cnt = 0;
		cin >> n >> time[0] >> time[1] >> time[2] >> time[3] >> time[4] >> q;
		opc.resize(n); opd.resize(n);
		opc[0].push_back(1);
		opd[0].push_back(-1);
		cin.ignore();
		while (cnt < n)
		{
			char cmd[20];
			char x;
			cin.getline(cmd, 20);
			if (cmd[0] == 'p' && cmd[1] == 'r')
			{
				opc[cnt].push_back(1);
				opd[cnt].push_back(cmd[6] - 'a');
			}
			else if (cmd[0] == 'l' && cmd[1] == 'o')
			{
				opc[cnt].push_back(2);
				opd[cnt].push_back(-1);
			}
			else if (cmd[0] == 'u' && cmd[1] == 'n')
			{
				opc[cnt].push_back(3);
				opd[cnt].push_back(-1);
			}
			else if (cmd[0] == 'e' && cmd[1] == 'n')
			{
				opc[cnt].push_back(4);
				opd[cnt].push_back(-1);
				exc.push_back(cnt);
				cnt++;
				if (cnt < n)
				{
					opc[cnt].push_back(1);
					opd[cnt].push_back(-1);
				}
			}
			else
			{
				stringstream ss(cmd + 3);
				int xx;
				opc[cnt].push_back(cmd[0] - 'a' + 5);
				ss >> xx;
				opd[cnt].push_back(xx);
			}
		}
		int lock = 0;
		if (kase++) cout << endl;
		while (!exc.empty())
		{
			int prom = exc.front(), tot = opc[prom][0], sum = 0, flag = 1;
			exc.pop_front();
			while (sum < q)
			{
				//cout << opc[prom][tot] << endl;
				if (opc[prom][tot] >= 5)
					var[opc[prom][tot] - 5] = opd[prom][tot], sum += time[0];
				else if (opc[prom][tot] == 1)
					cout << prom + 1 << ": " << var[opd[prom][tot]] << endl, sum += time[1];
				else if (opc[prom][tot] == 2)
				{
					if (!lock)
						lock = 1;
					else
						wait.push_back(prom), flag = 0, sum = q + 1;
					sum += time[2];
				}
				else if (opc[prom][tot] == 3)
				{
					lock = 0, sum += time[3];
					if (!wait.empty())
					{
						exc.push_front(wait.front());
						wait.pop_front();
					}
				}
				else
					sum = q + 1, flag = 0;
				if (flag)
					tot++;
			}
			opc[prom][0] = tot;
			if (flag)
				exc.push_back(prom);
		}

	}
	return 0;
}