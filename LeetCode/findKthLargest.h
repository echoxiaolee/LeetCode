#ifndef FINDKTHLARGEST_H
#define FINDKTHLARGEST_H

#include<vector>
#include<algorithm>
using namespace std;

int findKthLargest(vector<int>& nums, int k)
{
	sort(nums.begin(), nums.end());
	//vector<int>::iterator it=unique(nums.begin(), nums.end());
	//int dis = distance(nums.begin(), it);
	//if (k >= dis)return nums[0];
	return *(nums.end() - k);
}

#endif // !FINDKTHLARGEST_H
