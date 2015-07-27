#ifndef TWOSUM_H
#define TWOSUM_H

#include<vector>
#include<algorithm>
#include<iterator>
using namespace std;
vector<int>twoSum(vector<int>&nums, int target)
{
	vector<int>arr(nums);
	vector<int>index;
	//ostream_iterator<int>out(cout, " ");
	sort(arr.begin(), arr.end(), less<int>());

	//copy(arr.begin(), arr.end(), out);
	//cout << endl;

	for (vector<int>::size_type it = 0; it != arr.size()-1; it++)
	{
		int temp = target - arr[it];
		vector<int>::size_type left = it + 1;
		vector<int>::size_type right = arr.size()-1;
		vector<int>::size_type mid = (left + right) / 2;
		while (left<right)
		{
			if (temp == arr[mid])
			{
				break;
			}

			else if (temp > arr[mid])
			{
				left = mid + 1;
				mid = (left + right) / 2;
			}
			else
			{
				right = mid - 1;
				mid = (left + right) / 2;
			}
		}
		if (temp == arr[mid])
		{
			index.push_back(arr[it]);
			index.push_back(arr[mid]);
			break;
		}
	}
	//copy(index.begin(), index.end(), out);
	//cout << endl;
	int i = 0;
	int t1 = index[0], t2 = index[1];
	for (vector<int>::size_type it = 0; it != nums.size() ; it++)
	{
		if (t1 == nums[it]||t2==nums[it])
		{
			index[i++] = it + 1;
			if (i == 2)break;
		}
	}
	return index;
}

#endif // !TWOSUM_H
