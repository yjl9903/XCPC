#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
vector<vector<string>> code;
vector<string> line;
int maxLen[200] = { 0 };
int main()
{
	string str, s;
	while (getline(cin, s))
	{
		stringstream ss(s);
		while (ss >> str)
			line.push_back(str);
		code.push_back(line);
		line.clear();
	}
	for (int i = 0; i < 200; i++)
	{
		for (int j = 0; j < code.size(); j++)
			if (i < code[j].size() && code[j][i].size() > maxLen[i])
				maxLen[i] = code[j][i].size();
	}
	for (int i = 0; i < code.size(); i++)
	{
		for (int j = 0; j < code[i].size(); j++)
		{
			cout << code[i][j];
			if (j < code[i].size() - 1)
				for (int k = code[i][j].size(); k < maxLen[j] + 1; k++)
					cout << ' ';
		}
		cout << endl;
	}
	return 0;
}
