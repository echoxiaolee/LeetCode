#ifndef STRING_H
#define STRING_H
#include<string>
#include<vector>
#include<stack>
#include<utility>
#include<iterator>
#include<algorithm>
#include<map>
#include<iostream>
using namespace std;


//É¾³ý×Ö·û´®Ê×Î²µÄ¿Õ¸ñ
void trim(string&str)
{
	if (!str.empty())
	{
		str.erase(0, str.find_first_not_of(" "));
		str.erase(str.find_last_not_of(" ") + 1);
	}
}

//Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases. 
bool isPalindrome(string s) 
{
	string::iterator it = s.begin();
	while ( it !=s.end())
	{
		if (it != s.end())
		{
			if (*it >= 'A'&&*it <= 'Z')*it = tolower(*it);
		}
		else break;

		if (*it<'0' ||(*it>'9'&&*it<'A')|| (*it>'Z'&&*it<'a') || *it>'z')
		{
			s.erase(it);
		}
		else it++;
	}
	if (s.empty())return true;
	string::iterator p = s.begin(), q = s.end() - 1;
	while (p < q)
	{
		if (*p != *q)return false;
		p++;
		q--;
	}
	return true;
}

//Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string.
//If the last word does not exist, return 0.
int lengthOfLastWord(string s)
{
	while (s.back() == ' ')s.pop_back();
	int i = 0;
	string::reverse_iterator it= s.rbegin();
	while (it != s.rend())
	{
		if (*it == ' ')break;
		i++;
		it++;
	}
	cout << string(it.base(), s.end()) << endl;
	return i;
}

int compareVersion(string version1, string version2) {

	version1.erase(0, version1.find_first_not_of('0'));
	version2.erase(0, version2.find_first_not_of('0'));
	if (version1 == version2)return 0;
	else if (version1 < version2)return -1;
	else return 1;

	string::size_type pos1 = version1.find_first_of('.');
	string::size_type pos2 = version2.find_first_of('.');

	int r1, r2;
	string::size_type sz1;
	int l1 = stoi(version1, &sz1);
	if (pos1!=string::npos)
		r1= stoi(version1.substr(sz1+1));
	string::size_type sz2;
	int l2 = stoi(version2, &sz2);
	if (pos2 != string::npos)
		r2 = stoi(version2.substr(sz2+1));

	if (pos1 != string::npos&&pos2 != string::npos)
	{
		if (l1 < l2 || l1 == l2&&r1 < r2)return -1;
		else if (l1 == l2&&r1 == r2)return 0;
		else return 1;
	}
	else if (pos1 == string::npos&&pos2 != string::npos)
	{
		if (l1 < l2||l1==l2&&r2!=0)return -1;
		else if (l1 == l2&&r2 == 0)return 0;
		else return 1;
	}
	else if (pos1 != string::npos&&pos2 == string::npos)
	{
		if (l1 < l2)return -1;
		else if (l1 == l2&&r1 == 0)return 0;
		else return 1;
	}
	else
	{
		if (l1 < l2)return -1;
		else if (l1 == l2)return 0;
		else return 1;
	}
}


//Given two binary strings, return their sum (also a binary string). 
string addBinary(string a, string b)
{
	//string::iterator it = a.begin();
	if (a.find_first_of('1') != string::npos)a.erase(a.begin(), a.begin() + a.find_first_of('1'));
	if (a.find_last_not_of(' ')!=string::npos)a.erase(a.begin() + a.find_last_not_of(' ')+1, a.end());
	if (b.find_first_of('1') != string::npos)b.erase(b.begin(), b.begin() + b.find_first_of('1'));
	if (b.find_last_not_of(' ') != string::npos)b.erase(b.begin() + b.find_last_not_of(' ')+1, b.end());

	//vector<int>aa;
	//vector<int>bb;
	//for (string::size_type it = 0; it < a.size(); it++)
	//	aa.push_back(a[it] - '0');
	//for (string::size_type it = 0; it < b.size(); it++)
	//	bb.push_back(b[it] - '0');
	vector<int>vec;

	string::const_reverse_iterator ra = a.rbegin();
	string::const_reverse_iterator rb = b.rbegin();

	int carry = 0;
	while (ra != a.rend() && rb != b.rend())
	{
		int temp = *ra - '0' + *rb - '0'+carry;
		if (temp > 1)
		{
			vec.insert(vec.begin(), temp % 2);
			carry = 1;
		}
		else
		{
			vec.insert(vec.begin(), temp );
			carry = 0;
		}
		ra++;
		rb++;
	}
	while (ra != a.rend())
	{
		int temp = *ra - '0' + carry;
		if (temp > 1)
		{
			vec.insert(vec.begin(), temp % 2);
			carry = 1;
		}
		else
		{
			vec.insert(vec.begin(), temp);
			carry = 0;
		}
		ra++;
	}
	while (rb != b.rend())
	{
		int temp = *rb - '0' + carry;
		if (temp > 1)
		{
			vec.insert(vec.begin(), temp % 2);
			carry = 1;
		}
		else
		{
			vec.insert(vec.begin(), temp);
			carry = 0;
		}
		rb++;
	}
	if (carry == 1)vec.insert(vec.begin(), carry);
	ostream_iterator<int>out(cout, " ");
	copy(vec.begin(), vec.end(), out);
	cout << endl;
	string str;
	for (vector<int>::const_iterator it = vec.begin(); it != vec.end(); it++)
	{
		str += to_string(*it);
	}
	return str;
}


//Given two strings s and t, determine if they are isomorphic.
bool isIsomorphic(string s, string t) 
{
	if (s.length() != t.length())return false;
	string ss = s;
	string tt = t;
	map<char, char>m;
	map<char, char>n;
	for (string::size_type it = 0; it != s.length(); it++)
	{
		m.insert(make_pair(s[it], t[it]));
		n.insert(make_pair(t[it], s[it]));
	}
	for (string::size_type it = 0; it != s.length(); it++)
	{
		ss[it] = m[s[it]];
		tt[it] = n[t[it]];
	}
	if (ss != t||tt!=s)return false;
	else return true;
}
//Given n pairs of parentheses, write a function to generate all combinations of 
//well-formed parentheses
//vector<string> generateParenthesis(int n)
//{
//	
//}


#endif // !STRING_H
