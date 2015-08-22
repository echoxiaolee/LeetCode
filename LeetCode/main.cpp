#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<algorithm>
#include<iterator>
#include<utility>
#include<string>
#include<map>
//#include"twoSum.h"
//#include"binarySearch.h"
//#include"combinationSum2.h"
//#include"list.h"
//#include"lengthOfLongestSubstring.h"
//#include"findMedianSortedArrays.h"
//#include"longestPalindrome.h"
//#include"ZigZagConversion.h"
//#include"ReverseInteger.h"
//#include"StringtoInteger.h"
//#include"PalindromeNumber.h"
//#include"RandomList.h"
//#include"BinaryTree.h"
//#include"findKthLargest.h"
//#include"stack.h"
//#include"math.h"
//#include"array.h"
//#include"sort.h"
#include"string.h"

#define random(x) rand()%(x)
const unsigned int SIZE = 15;
using namespace std;

int main(int argc, char*argv[])
{
	srand((unsigned)time(0));
	//int arr[SIZE];
	//////int arr2[] = {32,32 };
	//for (int i = 0; i < SIZE; i++)
	//{
	//	arr[i] = random(100);
	//	cout << arr[i] << ' ';
	//}
	//cout << endl;


	//int sz = sizeof(arr) / sizeof(*arr);
	//TreeNode*q = NULL;
	//for (int i = 0; i < sz; i++)
	//	insert(q, arr[i]);
	//inPrintTree(q);
	//cout << endl;

	//sort(arr, arr + SIZE);
	//ostream_iterator<int>out(cout, " ");
	//copy(arr, arr + SIZE, out);
	//cout << endl;
	//sort(arr2, arr2 + sz2);

	//vector<int>vec;
	//copy(arr, arr + sz, inserter(vec, vec.begin()));

	clock_t start, stop;
	start = clock();//启动计时器
	/*算法调用处*/
	int pos=strStr("", "");
	cout << pos << endl;

	stop = clock();//计时器停止
	double timespan = (double)(stop - start) / CLK_TCK;//算法用时(以秒为单位)
	
	cout << "查找用时：" << timespan << "秒" << endl;
	return EXIT_SUCCESS;
}