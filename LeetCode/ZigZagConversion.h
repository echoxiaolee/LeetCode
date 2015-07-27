#ifndef CONVERT_H
#define CONVERT_H

#include<string>
#include<cstdlib>
#include<cstdio>
#include<vector>

using namespace std;

string convert(string s, int numRows)
{
	int len = s.size();
	if (numRows >= len || numRows==1)return s;
	//if (numRows == 2)
	//{
	//	string ss;
	//	for (string::size_type i = 0; i < s.size(); i += 2)
	//		ss.append(s.substr(i,1));
	//	for (string::size_type i = 1; i < s.size(); i += 2)
	//		ss.append(s.substr(i, 1));
	//	return ss;
	//}

	int round = numRows * 2 - 2;

	int mod = len % round;
	if (mod ==len)mod = len%numRows;

	int groupsz = len / round;

	char *arr = new char[len + 1];
	arr[len] = '\0';

	int numClos;
	if (mod >= 1 && mod < numRows)
	{
		if (groupsz==0)
			numClos = mod + 1;
		else
			numClos = (numRows - 1)*groupsz + 1;
	}
	else if (mod==0)
		numClos = (numRows - 1)*groupsz;
	else
		numClos = (numRows - 1)*groupsz + 1 + mod%numRows;

	char**p = (char**)malloc(sizeof(char*)*numRows);//分配一个二维数组
	if (p == NULL)
	{
		printf("Memory Error!\n");
		exit(1);
	}
	for (int i = 0; i < numRows; i++)
	{
		p[i] = (char*)malloc(sizeof(char)*numClos);
		if (p[i] == NULL)
		{
			printf("Memory Error!\n");
			exit(1);
		}
	}

	for (int i = 0; i != numRows; i++)
		for (int j = 0; j != numClos; j++)
			p[i][j] = '\0';

	for (int i = 0; i != len; i++)
	{
		if (i%round < numRows)p[i%round][(i / round)*(numRows - 1)] = s[i];
		else
			p[round - i%round][(i / round)*(numRows - 1) + i%round - numRows+1] = s[i];
	}

	int k = 0;
	for (int i = 0; i != numRows; i++)
		for (int j = 0; j != numClos; j++)
		{
			if (p[i][j] != '\0')
			{
				arr[k] = p[i][j];
				k++;
			}
		}
	string str(arr);

	for (int i = 0; i != numRows; i++)
	{
		free(p[i]);
	}
	free(p);
	free(arr);

	return str;
}

#endif // !CONVERT_H
