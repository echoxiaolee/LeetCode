#ifndef BINARYSEARCH_H
#define BINARYSEARCH_H
#include<vector>
using namespace std;
template<typename T>
int binarySearch(const T*arr,const T&value, int left, int right)//�ҵ������±�λ�ã�δ�ҵ�����-1
{
	if (left <= right)
	{
		int mid = (left + right) / 2;
		if (value == arr[mid])return mid;
		if (value < arr[mid])
		{
			right = mid - 1;
			mid = (left + right) / 2;
			return binarySearch(arr, value, left, right);
		}
		else
		{
			left = mid + 1;
			mid = (left + right) / 2;
			return binarySearch(arr, value, left, right);
		}
	}
	else return -1;
}

template<typename T>
int binarySearch(vector<T>&arr, const T&value, int left, int right)//�ҵ������±�λ�ã�δ�ҵ�����-1
{
	if (left <= right)
	{
		int mid = (left + right) / 2;
		if (value == arr[mid])return mid;
		if (value < arr[mid])
		{
			right = mid - 1;
			mid = (left + right) / 2;
			return binarySearch(arr, value, left, right);
		}
		else
		{
			left = mid + 1;
			mid = (left + right) / 2;
			return binarySearch(arr, value, left, right);
		}
	}
	else return -1;
}
#endif // !BINARYSEARCH_H
