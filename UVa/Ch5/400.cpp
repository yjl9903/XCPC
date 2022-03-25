#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
string file[105];
int main()
{
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int N;
	while (cin >> N)
	{
		for (int i = 0; i < N; i++)
			cin >> file[i];
		sort(file, file + N);
		int M = file[0].length();
		for (int i = 1; i < N; i++)
			if (file[i].length() > M)
				M = file[i].length();
		int col = (60 - M) / (M + 2) + 1, row = N / col;
		if (N % col)
			row++;
		int rest = N % row;
		col = (N - 1) / row + 1;
		for (int i = 0; i < 60; cout << '-', i++);
		//cout << row << col << rest <<endl;
		cout << endl;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (j * row + i < N)
				{
					cout << file[j * row + i];
					for (int x = file[j * row + i].length(); x < M; x++)
						cout << ' ';
					if (j < col - 2)
						cout << "  ";
					else if (j == col - 2 && i < rest)
						cout << "  ";
				}
			}
			cout << endl;
		}
	}
	return 0;
}