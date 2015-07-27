#ifndef SORT_H
#define	SORT_H
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
//#include<functional>
#include<cstdlib>
#pragma warning(disable:4996)
using namespace std;

vector<int> merge2(vector<int>& nums1, vector<int>& nums2)//将两个有序序列合并，nums1和nums2分别是两个有序序列,将合并后序列返回
{
	vector<int>vec(nums1.size() + nums2.size());
	vector<int>::size_type i = 0, j = 0, k = 0;
	while (i < nums1.size()&&j < nums2.size())
	{
		if (nums1[i] < nums2[j])vec[k++] = nums1[i++];
		else vec[k++] = nums2[j++];
	}
	while (i<nums1.size())vec[k++] = nums1[i++];
	while (j<nums2.size())vec[k++] = nums2[j++];
	return vec;
}

//归并排序
void mergeSort(vector<int>&vec)
{
	if (vec.size() > 1)
	{
		vector<int>left(vec.begin(), vec.begin() + vec.size() / 2);
		vector<int>right(vec.begin() + vec.size() / 2, vec.end());
		mergeSort(left);
		mergeSort(right);
		vec=merge2(left, right);
	}
}

bool comp(vector<int>&nums1, vector<int>&nums2)
{
	if (nums1==nums2)return false;
	vector<int>vec1(nums1);
	copy(nums2.begin(), nums2.end(), inserter(vec1, vec1.end()));
	//vec1.insert(vec1.end(), nums2.begin(), nums2.end());
	vector<int>vec2(nums2);
	copy(nums1.begin(), nums1.end(), inserter(vec2, vec2.end()));
	//vec1.insert(vec2.end(), nums1.begin(), nums1.end());
	vector<int>::size_type it;

	for ( it = 0; it < vec1.size(); it++)
	{
		if (vec1[it] == vec2[it])continue;
		return vec1[it] > vec2[it];
	}
	return false;
}

string largestNumber(vector<int>& nums) 
{
	vector<vector<int>>vec;
	vector<int>temp;
	int n;
	for (vector<int>::size_type it = 0; it != nums.size(); it++)
	{
		temp.clear();
		n = nums[it];
		if (n == 0)temp.push_back(0);
		while (n != 0)
		{
			temp.insert(temp.begin(),n % 10);
			n = n / 10;
		}
		vec.push_back(temp);
	}

	sort(vec.begin(), vec.end(), comp);

	string str;

	for (vector<vector<int>>::size_type u =0; u <vec.size(); u++)
	{
		ostream_iterator<int>out(cout, " ");

		copy(vec[u].begin(), vec[u].end(), out);
		cout << endl;

		for (vector<int>::size_type v = 0; v < vec[u].size(); v++)
		{
			char arr[] = { '0' + vec[u][v], '\0' };
			str = str + string(arr);
		}
	}
	if (str[0] == '0')return "0";
	return str;
}

#endif // !SORT_H
