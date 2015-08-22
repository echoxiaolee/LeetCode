#ifndef ARRAY_H
#define	ARRAY_H

//#define max(a,b) ((a)>(b)?(a):(b))
//#define min(a,b) ((a)<(b)?(a):(b))

#include<vector>
#include<iterator>
#include<algorithm>
#include<map>
#include<string>
using namespace std;

//Given a matrix of m x n elements(m rows, n columns), return all elements of the matrix in spiral order.
//vector<int> spiralOrder(vector<vector<int>>& matrix)
//{
//	vector<int>vec(matrix.size()*matrix[0].size());
//
//}

//Rotate an array of n elements to the right by k steps.
//
//For example, with n = 7 and k = 3, the array[1, 2, 3, 4, 5, 6, 7] is rotated to[5, 6, 7, 1, 2, 3, 4].
void rotate(vector<int>& nums, int k) 
{
	k = k%nums.size();
	if (k!= 0)
	{
		vector<int>temp;
		copy(nums.end() - k, nums.end(), inserter(temp, temp.begin()));
		nums.erase(nums.end() - k, nums.end());
		copy(temp.begin(), temp.end(), inserter(nums, nums.begin()));
	}
}

int removeElement(vector<int>& nums, int val)
{
	vector<int>::iterator it =find(nums.begin(),nums.end(),val);
	while (it != nums.end())
	{
		nums.erase(it);
		it = find(nums.begin(), nums.end(), val);
	}
	return nums.size();
}

int removeDuplicates(vector<int>& nums) 
{
	vector<int>::iterator it = unique(nums.begin(), nums.end());
	nums.erase(it, nums.end());
	return nums.size();
}

int removeDuplicates2(vector<int>& nums)
{
	if (nums.size() <= 2)return nums.size();
		vector<int>vec(1,nums.front());
		//ostream_iterator<int>out(cout, " ");
		//copy(vec.begin(), vec.end(), out);
		//cout << endl;

	int flag = 1;
	for (vector<int>::iterator it = nums.begin()+1; it != nums.end(); it++)
	{
		if (*it == *(it - 1))flag++;
		else flag = 1;
		if (flag <= 2)
			vec.push_back(*it);
	}

	nums.clear();
	nums = vec;
	return nums.size();
}

bool containsDuplicate(vector<int>& nums) 
{
	if (nums.size()<2)return false;
	sort(nums.begin(), nums.end());
	vector<int>::size_type j;
	for (j = 1; j<nums.size(); j++)
	{
		if (nums[j] == nums[j - 1])return true;
	}
	if (j = nums.size())return false;
}


//Given an array of integers and an integer k, find out whether there there are
//two distinct indices i and j in the array such that nums[i] = nums[j] and 
//the difference between i and j is at most k.

bool containsNearbyDuplicate(vector<int>& nums, int k)
{
	if (nums.size() <= 1)return false;
	vector<int>vec(nums);
	sort(vec.begin(), vec.end());
	vector<int>::iterator iter = unique(vec.begin(), vec.end());
	if (iter == vec.end())return false;
	for (vector<int>::iterator it = nums.begin(); it != nums.end(); it++)
	{
		vector<int>::iterator pos = find(it + 1, nums.end(),*it);
		if (pos != nums.end() && distance(it, pos) <= k)return true;
	}

	return false;
}


//Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.
int majorityElement(vector<int>& nums)
{
	sort(nums.begin(), nums.end());
	int cnt = 1;
	int temp=cnt;
	vector<int>::iterator iter = nums.begin();
	vector<int>::iterator it;
	for (it= nums.begin()+1; it != nums.end(); it++)
	{
		if (*it == *(it - 1))cnt++;
		else
		{
			if (temp < cnt)
			{
				temp = cnt;
				iter = it-1;
			}
			cnt = 1;
		}
	}
	if (it == nums.end() && cnt > temp)iter = it - 1;
	return *iter;
}
int max(int a, int b){ return a > b ? a : b; }

//Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water. 
int maxArea(vector<int>& height)
{
	int i = 0,j = height.size() - 1;
	int result=0;
	while (i<j)
	{
		if (height[i] > height[j])
		{
			result =max(result, height[j] * (j - i));
			j--;
		}
		else
		{
			result =max(result, height[i] * (j - i));
			i++;
		}
	}
	return result;
}
//Given a sorted integer array without duplicates, return the summary of its ranges.
//For example, given [0,1,2,4,5,7], return ["0->2","4->5","7"]. 
vector<string> summaryRanges(vector<int>& nums)
{
	vector<string>vstr;
	int i =0, j = 0;
	int k = 0;
	while (k < nums.size())
	{
		j=i = nums[k];
		while (k + 1 < nums.size() && nums[k+1] == nums[k] + 1)
		{
			j = nums[k + 1];
			k++;
		}
		if (j == i)
		{
			vstr.push_back(to_string(i));
		}
		else
		{
			string str = to_string(i);
			str.append("->");
			str.append(to_string(j));
			vstr.push_back(str);
		}
		k++;
	}
	return vstr;
}

//Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times. The algorithm should run in linear time and in O(1) space.
vector<int> majorityElement2(vector<int>& nums) //Majority Element II
{
	vector<int>vec;
	if (!nums.empty())
	{
		sort(nums.begin(), nums.end());
		int temp = nums[0];
		int cnt = 1;
		for (int i = 1; i < nums.size(); i++)
		{
			if (nums[i] == temp)
			{
				cnt++;
			}
			else
			{
				if (cnt > nums.size()/3)vec.push_back(temp);
				temp = nums[i];
				cnt = 1;
			}
		}
		if (cnt > nums.size() / 3)vec.push_back(temp);
	}
	return vec;
}
//Product of Array Except Self
vector<int> productExceptSelf(vector<int>& nums)
{
	int product=1;
	int n = 0;
	size_t pos = -1;
	for (size_t i = 0; i < nums.size(); i++)
	{
		if (nums[i])product *= nums[i];
		else
		{
			pos = i;
			n++;
		}
	}
	if (n>1)return vector<int>(nums.size(), 0);
	else if (n == 1)
	{
		vector<int>output(nums.size(), 0);
		output[pos] = product;
		return output;
	}
	else
	{
		vector<int>output;
		for (size_t i = 0; i < nums.size(); i++)
		{
			output.push_back(product / nums[i]);
		}
		return output;
	}
}


//Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.
int searchInsert(vector<int>& nums, int target)
{

}
//Write an efficient algorithm that searches for a value in an m x n matrix.This matrix has the following properties :
//•Integers in each row are sorted from left to right.
//•The first integer of each row is greater than the last integer of the previous row.
//bool searchMatrix(vector<vector<int>>& matrix, int target)
//{
//
//}
#endif // !ARRAY_H