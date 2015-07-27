#ifndef PALINDROMENUMBER_H
#define	PALINDROMENUMBER_H

/*Determine whether an integer is a palindrome. Do this without extra space.*/
#include"ReverseInteger.h"
#include<vector>
#include<cmath>
bool isPalindrome(int x) 
{
	if (x < 0)return false;
	int num = reverse(x);
	if (num == x)return true;
	return false;
}

bool isPalindrome2(int x)
{
	if (x < 0)return false;
	int temp = x;
	vector<int>vec;
	int result=0;

	while (x / 10 != 0)
	{
		vec.push_back(x % 10);
		x /= 10;
	}
	vec.push_back(x);

	for (int i = 0; i != vec.size(); i++)
	{
		result = result * 10 + vec[i];
	}
	if (temp== result)return true;
	return false;
}

bool isPalindrome3(int x)
{
	if (x < 0)return false;
	int k = 1;
	int temp = x;
	while (x / 10 != 0)
	{
		k++;
		x /= 10;
	}
	x = temp % 10;

	bool flag = true;
	for (int i = 1; i <= k / 2; i++)
	{
		if (x == temp / int(pow(10, k - i)))
		{
			temp = temp%int(pow(10, k - i));
			x = (temp % (int(pow(10, i + 1)))) / int(pow(10, i));
		}
		else
		{
			flag = false;
			break;
		}
	}

	if (flag)return true;
	return false;
}

#endif // !PALINDROMENUMBER_H
