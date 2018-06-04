// https://www.hackerrank.com/challenges/2d-array

#include "../../../../common/base.h"

int main_2d_arrays_ds()
{
	int n = 6, best = -100;
	vector<vector<int>> v(n, vector<int>(6));
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cin >> v[i][j];
		}
	}
	for (int i = 1; i < n - 1; ++i)
	{
		for (int j = 1; j < n - 1; ++j)
		{
			int current = 0;
			for (int i1 = -1; i1 <= 1; ++i1)
			{
				for (int j1 = -1; j1 <= 1; ++j1)
				{
					if ((i1 == 0) && (j1 != 0))
						continue;
					current += v[i + i1][j + j1];
				}
			}
			best = max(best, current);
		}
	}
	cout << best << endl;
	return 0;
}