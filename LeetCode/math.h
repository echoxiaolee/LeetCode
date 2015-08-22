#ifndef MATH_H
#define MATH_H

#include<iostream>
#include<vector>
#include<iterator>
#include<algorithm>
#include<map>
#include<set>
#include<cmath>
#include<stack>
#include<string>
#include<cstdint>

using namespace std;


//Given a non - negative number represented as an array of digits, plus one to the number.
//
//The digits are stored such that the most significant digit is at the head of the list.

vector<int> plusOne(vector<int>& digits)
{
	int carry =1;
	for (int i = digits.size() - 1; i >= 0; i--)
	{
		int temp = digits[i];
		digits[i]=(digits[i] + carry)%10;
		carry = (temp + carry) / 10;
	}
	if (carry == 1)digits.insert(digits.begin(), 1);
	return digits;
}
//Implement pow(x, n). 
double myPow(double x, int n)
{
	if (n == 0)return 1;
	if (n == 1)return x;
	if (n < 0)
	{
		if (n>INT_MIN)   
			return 1.0 / myPow(x, -n);
		else
			return 1.0 / (myPow(x, -n+1)*x);
	}
	double result = 1,tem=x;
	while (n > 0)
	{
		if (n & 1)result = result*tem;//n%2==1
		tem=tem*tem;
		n >>= 1;//n=n/2
	}
	return result;
}

int factorial(int n)//阶乘
{
	if (n == 0 || n == 1)return 1;
	int res = 1;
	for (int i = 1; i <= n; i++)
		res = res*i;
	return res;
}

//Given a set of distinct integers, nums, return all possible subsets. 
vector<vector<int>> subsets(vector<int>& nums) 
{
	sort(nums.begin(), nums.end());
	int sz = nums.size();
	if (sz < 1)return vector<vector<int>>(1, nums);
	int temp = nums[0];
	nums.erase(nums.begin());
	vector<vector<int>>res = subsets(nums);
	vector<vector<int>>fin(res);
	for (vector<vector<int>>::size_type it = 0; it != res.size(); it++)
		res[it].insert(res[it].begin(), temp);
	copy(res.begin(), res.end(), inserter(fin, fin.begin()));
	//fin.push_back(vector<int>());
	return fin;
}

vector<vector<int>> subsetsWithDup(vector<int>& nums) 
{
	vector<vector<int>>fin = subsets(nums);
	sort(fin.begin(), fin.end());

	vector<vector<int>>::iterator iter=unique(fin.begin(), fin.end());
	fin.erase(iter, fin.end());
	return fin;

}

//Given numRows, generate the first numRows of Pascal's triangle.
vector<vector<int>> generate(int numRows) //此种方法numRows不能大于13，否则算阶乘时溢出
{
	if (numRows == 0)return vector<vector<int>>();
	if (numRows == 1)return vector<vector<int>>(1, vector<int>(1,1));
	if (numRows > 13)
	{
		cout << "不能大于13,否则算阶乘时溢出！" << endl;
		exit(1);
	}
	vector<vector<int>>vec(1, vector<int>(1, 1));
	vector<int>temp;
	for (int k = 1; k < numRows; k++)
	{
		temp.clear();
		for (int i = 0; i <= k; i++)
		{
			temp.push_back(factorial(k) / (factorial(i)*factorial(k - i)));
		}
		vec.push_back(temp);
	}
	return vec;
}

vector<vector<int>> generate2(int numRows)
{
	if (numRows == 0)return vector<vector<int>>();
	if (numRows == 1)return vector<vector<int>>(1, vector<int>(1, 1));
	vector<vector<int>>vec(1, vector<int>(1, 1));
	vector<int>temp;
	for (int k = 1; k < numRows; k++)
	{
		temp.clear();
		temp.push_back(1);
		for (int i = 1; i < k; i++)
		{
			temp.push_back(vec[k-1][i-1]+vec[k-1][i]);
		}
		temp.push_back(1);
		vec.push_back(temp);
	}
	return vec;

}

vector<int> getRow(int rowIndex) 
{
	vector<vector<int>>vec(generate2(rowIndex+1));
	//if (vec.empty())return vector<int>();
	return vec.back();
}
/*
帕斯卡三角形（杨辉三角）
1
1    1
1    2    1
1    3    3    1
1    4    6    4    1

三角形边界上的数都是1，内部的每个数是位于它上面的两个数之和。

利用递归我们可以很容易地把问题转换为这个性质：

假设f(row, col)表示杨辉三角的第row行的第col个元素，那么：

f(row, col) = 1 (col = 1 或者 row = col)，也就是递归的停止条件。

f(row, col) = f(row - 1, col - 1) + f(row - 1, col)，也就是上一行的两个相邻元素的和。
*/
static long GetElement(const long row, const long col)
{
	// 每行的外围两个元素为1
	if ((1 == col) || (row == col))
		return 1;
	else
		// 其余的部分为上一行的(col - 1)和(col)元素之和
		return GetElement(row - 1, col - 1) + GetElement(row - 1, col);
}

static void PascalTriangle(const long n)
{
	int row;
	int col;

	for (row = 1; row <= n; ++row)
	{
		for (col = 1; col <= row; ++col)
			printf(" %4ld", GetElement(row, col));
		printf("\n");
	}
}

vector<int> getRow2(int rowIndex)
{
	vector<int>vec;
	for (int col = 1; col <= rowIndex+1; ++col)
		vec.push_back(GetElement(rowIndex+1, col));
	return vec;
}

//计算n!/(m!*(n-m)!)
double calcComb(int n, int m)
{
	if (n == m || m == 0)return 1;
	double sum = 1;
	for (double i = 1; i <= double(n - m); i++)
		sum =sum* ((double(m) + i) / i);
	return sum;
}

vector<double> getRow3(int rowIndex)
{
	vector<double>vec;
	for (int col =0; col <= rowIndex ; ++col)
		vec.push_back(calcComb(rowIndex,col));
	return vec;
}

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
{
	vector<int>vec;
	merge(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), inserter(vec,vec.begin()));
	nums1 = vec;
}

int singleNumber(vector<int>& nums) 
{
	if (nums.size() == 1)return nums[0];
	sort(nums.begin(), nums.end());
	size_t i;
	int flag = 1;
	for (i = 1; i<nums.size(); i++)
	{
		if (nums[i] == nums[i - 1])flag++;
		else flag--;
		if (flag== 0)return nums[i - 1];
	}
	if (i == nums.size() && flag == 1)return nums[i - 1];
}

//
//A happy number is a number defined by the following process : Starting with any positive integer,
//replace the number by the sum of the squares of its digits, and repeat the process until the 
//number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1.
//Those numbers for which this process ends in 1 are happy numbers.
bool isHappy(int n) 
{
	if (n <= 0)return false;
	vector<int>digits;
	int sum=0;
	set<int>cnt;
	//int sign;
	//int m = 0;
	while (true)
	{
		//m++;
		digits.clear();
		while (n != 0)
		{
			digits.push_back(n % 10);
			n /= 10;
		}
		for (size_t i = 0; i < digits.size(); i++)
		{
			sum = sum+digits[i] * digits[i];
		}
		if (sum == 1)break;
		pair<set<int>::iterator, bool>ref = \
			cnt.insert(sum);
		if (ref.second == false)return false;
		//if (m >1 && sign == sum)return false;
		//sign = sum;
		n = sum;
		sum = 0;
	}
	return true;
}

void merge2(vector<int>& nums1, int m, vector<int>& nums2, int n)
{
	vector<int>vec(nums1.begin(), nums1.begin() + m);
	int i = 0, j = 0, k = 0;
	while (i < m&&j < n)
	{
		if (vec[i] < nums2[j])nums1[k++] = vec[i++];
		else nums1[k++] = nums2[j++];
	}
	while (i<m)nums1[k++] = vec[i++];
	while (j<n)nums1[k++] = nums2[j++];
}

bool isPrime(int n)//判断一个数是不是素数
{
	for (int i = 2; i <= sqrt(n); i++)
	{
		if (n%i != 0)continue;
		else return false;
	}
	return true;
}


int countPrimes(int n) 
{

	int cnt = 0;
	for (int i = 2; i <= n; i++)
	{
		if (isPrime(i) == false)continue;
		else cnt++;
	}
	return cnt;
}

int countPrimes2(int n)//n以内的素数个数，不包括n
{
	if (n <= 2)return 0;
	int cnt = 0;
	bool *arr = new bool[n];
	for (int i = 3; i < n; i++)
	{
		if(i%2==0)arr[i] = false;
		else arr[i] = true;
	}
	arr[2] = true;
	for (int i = 3; i*i<n; i += 2)//不用i<sqrt(n),防止调用函数带来的额外开销
	{
		if (arr[i])
		{
			for (int j = i *i; j < n; j += i)
			{
				arr[j] = false;
			}
		}
	}
	for (int i = 2; i < n; i++)
		if (arr[i])cnt++;
	delete[]arr;
	return cnt;
}


//Given an integer n, count the total number of digit 1 appearing in all non-negative integers less than or equal to n.
int countDigitOne2(int n) 
{
	if (n <= 0)return 0;
	int total=0;
	for (int i = 1; i <= n; i++)
	{
		int temp = i;
		int num = 0;
		while (temp)
		{
			if (temp % 10 == 1)num++;
			temp /= 10;
		}
		total += num;
	}
	return total;
}

int countDigitOne(int n)
{
	if (n <= 0)return 0;
	if (n < 10)return 1;
	int high = n;
	int total = 0;
	int dec = 1;
	int bits = 0;
	while (high >= 10)
	{
		high /= 10;
		bits++;
		dec *= 10;
	}

	if (high > 1)total = dec + (dec / 10)*high*bits + countDigitOne(n-high*dec);
	else total = n - high*dec + 1 + dec / 10 * bits +countDigitOne(n - high*dec);

	return total;
}


//Given an integer, write a function to determine if it is a power of two. 
bool isPowerOfTwo(int n) 
{
	if ( n == 1)return true;
	if (n <= 0)return false;
	if (n % 2)return false;
	while (n > 1)
	{
		if (n % 2)return false;
		n >>= 1;
	}
	if (n == 1)return true;
	else return false;
}
//The expression string contains only non-negative integers, +, -, *, / operators and empty spaces . The integer division should truncate toward zero.
int calculate2(string &s) //Basic Calculator II 
{
	stack<int>data;
	stack<char>oper;

	string::iterator it = s.begin();
	while (it != s.end())//去掉空格
	{
		if (*it == ' ')s.erase(it);
		else it++;
	}
	it = s.begin();
	int flag = 0;
	while (it != s.end())
	{
		if (*it<'0' || *it>'9')
		{
			flag++;
			oper.push(*it);
			it++;
		}
		else
		{
			flag++;
			string::iterator i = it;
			while (it != s.end() && *it >= '0' && *it <= '9')
				it++;
			string str = s.substr(distance(s.begin(), i), distance(i, it));
			data.push(stoi(str));
		}
		if (flag % 2 == 1 && flag > 1)
		{
			char ch = oper.top();
			int d1, d2, res;
			switch (ch)
			{
			case '*':
				oper.pop();
				d1 = data.top();
				data.pop();
				d2 = data.top();
				data.pop();

				res = d2*d1;
				data.push(res);
				break;
			case '/':
				oper.pop();
				d1 = data.top();
				data.pop();
				d2 = data.top();
				data.pop();

				if (d1 != 0)
				{
					res = d2 / d1;
					data.push(res);
				}
				else
				{
					cout << "除数不能为0！" << endl;
					exit(-1);
				}
				break;
			default:
				break;
			}
		}
	}
	while (!oper.empty() && !data.empty())
	{
		char ch = oper.top();
		oper.pop();
		int d1 = data.top();
		data.pop();
		int d2 = data.top();
		data.pop();
		int res;
		switch (ch)
		{
		case '+':
			if (!oper.empty() && oper.top() == '-')
				res = d2 - d1;
			else
				res = d2 + d1;
			data.push(res);
			break;
		case '-':
			if (!oper.empty() && oper.top() == '-')
				res = d2 + d1;
			else
				res = d2 - d1;
			data.push(res);
			break;
		default:
			break;
		}
	}
	//ostream_iterator<int>out(cout, " ");
	//copy(data.begin(), data.end(), out);
	//cout << endl;
	//
	//ostream_iterator<char>ou(cout, " ");
	//copy(oper.begin(), oper.end(), ou);
	//cout << endl;

	return data.top();
}


//Implement a basic calculator to evaluate a simple expression string.
//
//The expression string may contain open(and closing parentheses), the plus + or minus sign - , non - negative integers and empty spaces
int calculate(string s) 
{
	string::iterator it = s.begin();
	while (it != s.end())
	{
		if (*it == ' ')s.erase(it);
		else it++;
	}

	stack<int>data;
	stack<char>op;
	int result = 0;

	it = s.begin();
	while (it != s.end())
	{
		if (*it<'0' || *it>'9')
		{
			if (*it == ')')
			{
				if (op.top() != '(')
				{
					int d1 = data.top();
					data.pop();
					int d2 = data.top();
					data.pop();

					if (op.top() == '+')
					{
						data.push(d1 + d2);
					}
					else
					{
						data.push(d2 - d1);
					}
					op.pop();
				}
				op.pop();
				if (!op.empty() && op.top() == '-')
				{
					int d1 = data.top();
					data.pop();
					if (!data.empty())
					{
						int d2 = data.top();
						data.pop();

						op.pop();

						data.push(d2 - d1);
					}
					else data.push(-d1);
				}
				else if (!op.empty() && op.top() == '+')
				{
					int d1 = data.top();
					data.pop();
					if (!data.empty())
					{
						int d2 = data.top();
						data.pop();

						op.pop();

						data.push(d2 + d1);
					}
					else data.push(d1);
				}

				it++;
			}
			else
			{
				op.push(*it);
				it++;
			}
		}
		else
		{
			string::iterator i = it;
			while (it != s.end() && *it >= '0'&&*it <= '9')
			{
				it++;
			}
			string str = s.substr(distance(s.begin(), i), distance(i, it));
			int temp = stoi(str);

			if (!op.empty() && op.top() == '+')
			{
				op.pop();
				i--;
				if (!data.empty() && op.empty() || !data.empty() && *(--i) != '(')
				{
					temp += data.top();
					data.pop();
				}					
			}
			else if (!op.empty() && op.top() == '-')
			{
				op.pop();
				i--;
				if (!data.empty() && op.empty() || !data.empty() && *(--i) != '(')
				{
					temp = data.top() - temp;
					data.pop();
				}
				else
					temp = -temp;
			}

			data.push(temp);
		}
	}
	while (!data.empty())
	{
		result+=data.top();
		data.pop();
	}
	return result;
}


//Rectangle Area 
int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) 
{
	int leftx = A > E ? A : E;
	int lefty = B > F ? B : F;

	int rightx = C < G ? C : G;
	int righty = D < H ? D : H;

	int corner;
	if (rightx <=leftx || righty <= lefty )corner = 0;
	else corner = (rightx - leftx)*(righty - lefty);
	return (G - E)*(H - F) + (C - A)*(D - B) - corner;
}


//Number of 1 Bits
int hammingWeight(uint32_t n) //#include<cstdint>
{
	int nums = 0;
	while (n)
	{
		if (n % 2)nums++;
		n>>=1;
	}
	return nums;
}
//Reverse Bits
uint32_t reverseBits(uint32_t n) 
{
	uint32_t res = 0;
	if (n != 0)
	{
		for (int i = 31; i >= 0; i--)
		{
			res += (n & 1) << i;
			n >>= 1;
		}
	}
	return res;
}

//You are climbing a stair case. It takes n steps to reach to the top.
//Each time you can either climb 1 or 2 steps.In how many distinct ways can you climb to the top ?
int climbStairs(int n)
{
	if (n <= 0)return 0;
	return (int)((pow((1 + sqrt(5)) / 2, n + 1) - pow((1 - sqrt(5)) / 2, n + 1)) / sqrt(5));
}

int climbStairs2(int n)
{
	if (n <= 0)return 0;
	vector<int>vec(n + 1);
	vec[0] = vec[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		vec[i] = vec[i - 1] + vec[i - 2];
	}
	return vec[n];
}

int trailingZeroes(int n)
{
	if (n < 5)return 0;
	int temp = n;
	int cnt= 0;
	while (temp >= 5)
	{
		temp /= 5;
		cnt++;
	}
	int sum = 0;
	int pre = 0;
	for (int i = cnt; i > 0; i--)
	{
		sum += i*(n / (int)pow(5, i) - pre);
		pre = n /(int)pow(5, i);
	}
	return sum;
}

string getPermutation(int n, int k) 
{
	if (k<1 || k>factorial(n))return string();
	vector<int>vec;
	string str;
	for (int i = 1; i <= n; i++)
		vec.push_back(i);
	int res = k / factorial(n - 1);
	int mod = k%factorial(n - 1);
	while (vec.size() > 0)
	{
		if (mod != 0)
		{
			cout << vec[res];
			str += to_string(vec[res]);
			vec.erase(vec.begin() + res);
		}
		else
		{
			if (res == 0)
			{
				for (vector<int>::reverse_iterator it = vec.rbegin(); it != vec.rend(); it++)
					str += to_string(*it);
				ostream_iterator<int>out(cout, "");
				copy(vec.rbegin(), vec.rend(), out);
				vec.clear();
				break;
			}
			else
			{
				cout << vec[res - 1];
				str += to_string(vec[res-1]);
				vec.erase(vec.begin() + res - 1);
			}
		}
		res = mod / factorial(vec.size() - 1);
		mod = mod%factorial(vec.size() - 1);
	}
	return str;
}

//Given a non-negative integer num, repeatedly add all its digits until the result has only one digit. 
int addDigits(int num) 
{
	if (num < 0)num *= -1;
	int res = num;
	int sum = 0;
	while (res > 0)
	{
		sum += res % 10;
		res /= 10;
		if (res == 0&&sum>=10)
		{
			res = sum;
			sum = 0;
		}
	}
	return sum;
}


//Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 6, 8 are ugly while 14 is not ugly since it includes another prime factor 7.
//Note that 1 is typically treated as an ugly number.
bool isUgly(int num)
{
	if (num <= 0)return false;
	while (num % 2 == 0&&num!=0)num /= 2;
	while (num % 3 == 0 && num != 0)num /= 3;
	while (num % 5 == 0 && num != 0)num /= 5;
	if (num == 1)return true;
	else return false;
}

//Write a program to find the n - th ugly number.
//Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.
//Note that 1 is typically treated as an ugly number.
int nthUglyNumber(int n) 
{
	int cnt = 1;
	int num = 1;
	while (cnt <= n)
	{
		if (isUgly(num))
		{
			cnt++;
		}
		num++;
	}
	return num-1;
}

int nthUglyNumber2(int n)
{
	if (n < 7)return n;
	vector<int>vec(n,1);
	int c2 = 0, c3 = 0, c5 = 0;
	for (size_t i = 1; i != n; i++)
	{
		vec[i] = vec[c2]*2 < (vec[c3]*3 < vec[c5]*5 ? vec[c3]*3 : vec[c5]*5) ? vec[c2]*2 : (vec[c3]*3 < vec[c5]*5 ? vec[c3]*3 : vec[c5]*5);
		if (vec[i] == vec[c2] * 2)c2++;
		if (vec[i] == vec[c3] * 3)c3++;
		if (vec[i] == vec[c5] * 5)c5++;
	}
	return vec[n - 1];
}

//Given a column title as appear in an Excel sheet, return its corresponding column number.
int titleToNumber(string s) 
{
	string::size_type beg = s.find_first_not_of(' ');
	s.erase(s.begin(), s.begin() + beg);
	string::size_type end = s.find_last_not_of(' ');
	s.erase(s.begin() + end+1, s.end());
	int res = 0;
	for (string::iterator it = s.begin(); it != s.end(); it++)
	{
		res = res * 26 + (*it - 'A')+1 ;
	}
	return res; 
}

//Given a positive integer, return its corresponding column title as appear in an Excel sheet.
string convertToTitle(int n) {
	vector<char>vec;
	while (n > 0)
	{
		if (n % 26 == 0)
		{
			vec.push_back('Z');
			n -= 26;
		}
		else
			vec.push_back(n % 26+'A'-1);
		n = n/26;
	}
	string str;
	for (vector<char>::reverse_iterator ch = vec.rbegin(); ch != vec.rend(); ch++)
		//str.append(1, *ch);
		str.insert(str.end(), *ch);
	return str;
}

//Since we are not allowed to rob two adjacent houses, we keep two variables pre and cur.During the i - th loop, pre records the maximum profit that we do not rob the i - 1 - th house and thus the current house(the i - th house) can be robbed while cur records the profit that we have robbed the i - 1 - th house.
int rob(vector<int>& nums) {
	int pre = 0, cur = 0;
	for (vector<int>::iterator it = nums.begin(); it != nums.end(); it++)
	{
		int temp = pre + *it > cur ? pre + *it : cur;
		pre = cur;
		cur = temp;
	}
	return cur;
}


//https://leetcode.com/problems/valid-sudoku/
//Determine if a Sudoku is valid. The Sudoku board could be partially filled, where empty cells are filled with the character '.'.
bool isValidSudoku(vector<vector<char>>& board)
{
	char arr[128] = { 0 };
	for (vector<vector<char>>::const_iterator row = board.begin(); row != board.end(); row++)
	{
		fill(arr + '0', arr + '9'+1, 0);
		for (vector<char>::const_iterator col = row->begin(); col != row->end(); col++)
		{
			arr[*col]++;
			if (*col != '.'&&arr[*col] > 1)return false;
		}
	}
	for (size_t row = 0; row != 9; row++)
	{
		fill(arr + '0', arr + '9' + 1, 0);
		for (size_t col = 0; col != 9; col++)
		{
			arr[board[col][row]]++;
			if (board[col][row] != '.'&&arr[board[col][row]] > 1)return false;
		}
	}
	for (size_t row = 0; row != 3; row++)
	{
		for (size_t col = 0; col != 3; col++)
		{
			fill(arr + '0', arr + '9' + 1, 0);
			for (size_t i = 0; i < 3; i++)
			{
				for (size_t j = 0; j < 3; j++)
				{
					arr[board[row * 3 + i][col * 3 + j]]++;
					if (board[row * 3 + i][col * 3 + j] !='.'&& arr[board[row * 3 + i][col * 3 + j]] > 1)return false;
				}
			}
		}
	}
	return true;
}
#endif // !MATH_H