#ifndef FINDMEDIANSORTEDARRAYS_H
#define FINDMEDIANSORTEDARRAYS_H

#include<vector>
#include<algorithm>
#include<iterator>
using namespace std;
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
{
	vector<int>vec;
	merge(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), inserter(vec, vec.begin()));
	if (vec.size() % 2 == 0)return (double)(vec[vec.size() / 2] + vec[vec.size() / 2 - 1])/2.0;
	return (double)vec[vec.size() / 2];
	//copy(nums1.begin(), nums1.end(), inserter(vec,vec.begin()));
}

#endif // !FINDMEDIANSORTEDARRAYS_H
