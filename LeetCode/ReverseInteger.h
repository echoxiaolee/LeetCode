#ifndef REVERSEINTEGER_H
#define	REVERSEINTEGER_H

#include<cmath>
#include<vector>
#include<iostream>
#include<iterator>
using namespace std;
int reverse(int x)
{
	if (-10 < x&&x < 10)return x;
	if (x <-2147483647)return 0;//-2^31
	int sign;
	int result=0;
	if (x < 0)sign = -1;
	else sign = 1;
	x = x*sign;
	vector<int>vec;
	while (x / 10 != 0)
	{
		vec.push_back(x % 10);
		x = x / 10;
	}
	vec.push_back(x % 10);


	if (vec.size() == 10)
	{
		if (vec[0] > 1)
		{
			if (vec[0] > 2)return 0;
			if (vec[0] == 2 && vec[1] > 1)return 0;
			if (vec[0] == 2 && vec[1] == 1 && vec[2] > 4)return 0;
			if (vec[0] == 2 && vec[1] == 1 && vec[2] == 4 && vec[3] > 7)return 0;
			if (vec[0] == 2 && vec[1] == 1 && vec[2] == 4 && vec[3] == 7 && vec[4] > 4)return 0;
			if (vec[0] == 2 && vec[1] == 1 && vec[2] == 4 && vec[3] == 7 && vec[4] == 4 && vec[5] > 8)return 0;
			if (vec[0] == 2 && vec[1] == 1 && vec[2] == 4 && vec[3] == 7 && vec[4] == 4 && vec[5] == 8 && vec[6] > 3)return 0;
			if (vec[0] == 2 && vec[1] == 1 && vec[2] == 4 && vec[3] == 7 && vec[4] == 4 && vec[5] == 8 && vec[6] == 3 && vec[7] > 6)return 0;
			if (vec[0] == 2 && vec[1] == 1 && vec[2] == 4 && vec[3] == 7 && vec[4] == 4 && vec[5] == 8 && vec[6] == 3 && vec[7] == 6 && vec[8] > 4)return 0;
			if (vec[0] == 2 && vec[1] == 1 && vec[2] == 4 && vec[3] == 7 && vec[4] == 4 && vec[5] == 8 && vec[6] == 3 && vec[7] == 6 && vec[8] == 4 && vec[9] > 7)return 0;
		}
	}

	for (int i = 0; i != vec.size(); i++)
	{
		result = result*10+vec[i];
	}
	return result*sign;
}

#endif // !REVERSEINTEGER_H
