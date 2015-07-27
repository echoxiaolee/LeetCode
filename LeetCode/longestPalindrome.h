#ifndef LONGESTPALINDROME_H
#define	LONGESTPALINDROME_H

#include<string>
#include<vector>
#include<algorithm>
using namespace std;

string longestPalindrome(string s)
{
	int length = s.length();
	if (s.length() == 1 || s.length() == 2 && s[0] == s[1])return s;
	else if (s.length() == 2 && s[0] != s[1])
	{
		return s.substr(0,1);
	}
	else
	{
		vector<string>svec;
		string temp;
		vector<int>size;
		int len;
		for (string::size_type it = 1; it != s.size(); it++)
		{
			if (s[it] != s[it - 1] && s[it-1] != s[it +1])continue;
			else
			{
				string::iterator iter = s.begin();
				temp.clear();
				if (s[it] == s[it - 1] && s[it - 1] == s[it + 1])//Á¬´®
				{
					int m, k;
					for (m = it + 1, k = it - 1; m != s.size() && k >= 0; m++, k--)
					{
						if (s[m] != s[k])
						{
							if ((m - k ) % 2 == 0)
							{
								m = it+1;
								k = it;
								continue;
							}
							temp.clear();
							if (s[m] == s[k + 1])
							{
								len = m - k;
								copy(iter + 1 + k, iter + m+1, inserter(temp, temp.begin()));
							}
							else
							{
								copy(iter + 1 + k, iter + m, inserter(temp, temp.begin()));
								len = m - k - 1;
							}
							size.push_back(len);
							svec.push_back(temp);
							break;
						}
					}
					if (m == s.size())
					{
						temp.clear();
						copy(iter + 1 + k, iter + m, inserter(temp, temp.begin()));
						len = m - k - 1;
						size.push_back(len);
						svec.push_back(temp);
						break;
					}
					if (k < 0)
					{
						temp.clear();
						if (s[m] == s[k + 1])
						{
							copy(iter + 1 + k, iter + m + 1, inserter(temp, temp.begin()));
							len = m - k;
						}
						else
						{
							copy(iter + 1 + k, iter + m , inserter(temp, temp.begin()));
							len = m - k - 1;
						}
						size.push_back(len);
						svec.push_back(temp);
					}
				}
				if (s[it] == s[it - 1] && s[it - 1] != s[it + 1])//Å¼
				{
					int m, k;
					for ( m= it , k = it - 1; m != s.size() && k >= 0; m++, k--)
					{
						if (s[m] != s[k])
						{
							temp.clear();
							copy(iter + 1 + k, iter + m, inserter(temp, temp.begin()));
							len = m - k -1;
							size.push_back(len);
							svec.push_back(temp);
							break;
						}
					}
					if (m == s.size())
					{
						temp.clear();
						copy(iter +1+k , iter + m, inserter(temp, temp.begin()));
						len = m - k-1 ;
						size.push_back(len);
						svec.push_back(temp);
						break;
					}
					if (k < 0)
					{
						temp.clear();
						copy(iter + 1+k, iter + m, inserter(temp, temp.begin()));
						len = m - k - 1;
						size.push_back(len);
						svec.push_back(temp);
					}
				}
				else//s[it] != s[it - 1] && s[it - 1] == s[it + 1],Ææ
				{
					int m,k;
					for ( m= it+1, k = it - 1; m != s.size() && k >= 0; m++, k--)
					{
						if (s[m] != s[k])
						{
							temp.clear();
							copy(iter + 1 + k, iter + m, inserter(temp, temp.begin()));
							len = m - k - 1;
							size.push_back(len);
							svec.push_back(temp);
							break;
						}
					}
					if (m == s.size())
					{
						temp.clear();
						copy(iter + 1+k, iter + m, inserter(temp, temp.begin()));
						len = m - k - 1;
						size.push_back(len);
						svec.push_back(temp);
						break;
					}
					if (k < 0)
					{
						temp.clear();
						copy(iter + 1 + k, iter + m, inserter(temp, temp.begin()));
						len = m - k - 1;
						size.push_back(len);
						svec.push_back(temp);
					}
				}
			}
		}
		sort(size.begin(), size.end());
		int longest = size.back();
		vector<string>::size_type u;
		for (u = 0; u != svec.size(); u++)
		{
			if (longest == svec[u].size())
				break;
		}
		return svec[u];
	}
}

#endif // !LONGESTPALINDROME_H
