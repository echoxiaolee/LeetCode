#ifndef STRINGTOINTEGER_H
#define STRINGTOINTEGER_H

#include<string>
#include<vector>
using namespace std;

void trim(string&);

int myAtoi(string str)
{
	trim(str);
	if (str.empty())return 0;
	char ch = str.front();
	if (ch < '0' || ch > '9')
	{
		if (ch != '+' &&ch != '-')
		return 0;
	}

	int sign;
	if (ch == '-')sign = -1;
	else sign = 1;


	vector<int>vec;
	int result=0;
	string::iterator iter;
	if (str.front()== '+' || str.front() == '-')
		iter = str.begin() + 1;
	else
		iter = str.begin();


	for (; iter != str.end(); iter++)
	{
		if (*iter<'0' || *iter>'9')break;
		vec.push_back(*iter - '0');
	}

	int nonzero;
	int i;
	for (i= 0; i != vec.size(); i++)
	{
		if (vec[i] != 0)
		{
			break;
		}
	}

	nonzero = i;
   	vec.erase(vec.begin(), vec.begin() + nonzero);

	if (vec.size()== 10)
	{
		if (vec[0] > 1)
		{
			if (vec[0] > 2)return INT_MAX;
			if (vec[0] == 2 && vec[1] > 1)return INT_MAX;
			if (vec[0] == 2 && vec[1] == 1 && vec[2] > 4)return INT_MAX;
			if (vec[0] == 2 && vec[1] == 1 && vec[2] == 4 && vec[3] > 7)return INT_MAX;
			if (vec[0] == 2 && vec[1] == 1 && vec[2] == 4 && vec[3] == 7 && vec[4] > 4)return INT_MAX;
			if (vec[0] == 2 && vec[1] == 1 && vec[2] == 4 && vec[3] == 7 && vec[4] == 4 && vec[5] > 8)return INT_MAX;
			if (vec[0] == 2 && vec[1] == 1 && vec[2] == 4 && vec[3] == 7 && vec[4] == 4 && vec[5] == 8 && vec[6] > 3)return INT_MAX;
			if (vec[0] == 2 && vec[1] == 1 && vec[2] == 4 && vec[3] == 7 && vec[4] == 4 && vec[5] == 8 && vec[6] == 3 && vec[7] > 6)return INT_MAX;
			if (vec[0] == 2 && vec[1] == 1 && vec[2] == 4 && vec[3] == 7 && vec[4] == 4 && vec[5] == 8 && vec[6] == 3 && vec[7] == 6 && vec[8] > 4)return INT_MAX;
			if (vec[0] == 2 && vec[1] == 1 && vec[2] == 4 && vec[3] == 7 && vec[4] == 4 && vec[5] == 8 && vec[6] == 3 && vec[7] == 6 && vec[8] == 4 && vec[9] > 7)
			{
				if (sign == 1)
					return INT_MAX;
				else
					return INT_MIN;
			}
		}
	}

	if (vec.size()> 10)
	{
		if (sign == 1)
			return INT_MAX;
		else
			return INT_MIN;
	}

	for (int i = 0; i != vec.size(); i++)
	{
		result = result * 10 + vec[i];
	}
	return result*sign;
}

void trim(string&str)
{
	if (!str.empty())
	{
		str.erase(0, str.find_first_not_of(" "));
		str.erase(str.find_last_not_of(" ")+1);
	}
}

#endif // !StringtoInteger_H
