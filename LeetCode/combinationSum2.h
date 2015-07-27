#ifndef COMBINATIONSUM2_H
#define	COMBINATIONSUM2_H

#include<vector>
#include<algorithm>
#include"binarySearch.h"
using namespace std;
vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
{
	vector<vector<int>>result;
	vector<int>vec;
	int sum = 0;
	vector<int>temp(candidates);
	sort(temp.begin(), temp.end());

	for (vector<int>::size_type it = 0; it != temp.size(); it++)
	{
		sum = temp[it];
		if (temp[it] > target)break;
		else if (temp[it] == target)
		{
			vec.clear();
			vec.push_back(temp[it]);
			result.push_back(vec);
			break;
		}
		else
		{
			vec.clear();
			vec.push_back(temp[it]);
			int pos = binarySearch(temp, target - temp[it], it + 1, temp.size() - 1);
			if (pos != -1)
			{
				vec.push_back(temp[pos]);
				result.push_back(vec);//2¸ö
				vec.pop_back();
			}
			for (vector<int>::size_type j = it + 1; j !=pos; j++)
			{
				sum = sum + temp[j];
				vec.push_back(temp[j]);
				int p = binarySearch(temp, target - sum, j + 1, pos - 1);
				if (p != -1)
				{
					vec.push_back(temp[p]);
					result.push_back(vec);//3¸ö
				}
			}
		}
	}
	return result;
}

#endif // !COMBINATIONSUM2_H
