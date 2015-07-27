#ifndef LENGTHOFLONGESTSUBSTRING_H
#define LENGTHOFLONGESTSUBSTRING_H

#include<string>
#include<map>
#include<utility>
#include<algorithm>
#include<iterator>
#include<vector>
using namespace std;

int lengthOfLongestSubstring(string s)
{
	map<char, int>ch_cnt;
	//for (string::size_type it = 0; it != s.length(); it++)
	//{
	//	pair<map<char, int>::iterator, bool>ref = ch_cnt.insert(make_pair(s[it], 1));
	//	if (!ref.second)
	//		ref.first->second++;
	//}

	//vector<vector<char>>svec;
	//vector<char>temp;
	vector<int>ivec;
	int k = 0;
	string::iterator iter = s.begin();
	pair<map<char, int>::iterator, bool>ref;

	for (string::size_type it = 0; it != s.size(); it++)
	{
		k++;

		ref = ch_cnt.insert(make_pair(s[it], 1));
		if (!ref.second)
			ref.first->second++;
		if (k == 95)
		{
			ivec.push_back(k);
			break;
		}
		if (ch_cnt[s[it]] > 1)
		{
			size_t pos = s.find_last_of(s[it], it-1);
			//temp.clear();
			ivec.push_back(k-1);
			//copy(iter, iter+k-1, inserter(temp, temp.begin())); 
			//svec.push_back(temp);
			iter = s.begin()+pos+1;
			k = 0;
			it=pos;
			ch_cnt.clear();
		}
		if (it == s.size()-1)ivec.push_back(k);
	}

	if (k == s.size())
	{
		//copy(s.begin(), s.end(), inserter(temp, temp.begin())); 
		//svec.push_back(temp);
		ivec.push_back(k);
	}

	sort(ivec.begin(), ivec.end());
	return ivec.back();
}

int lenOfLonstSubstr(string s) {
	vector<int> mymap(256, -1);
	int i, last = 0, ans = 0;
	for (i = 0; i<s.length(); i++)
	{
		if (mymap[s[i]] == -1 || mymap[s[i]]<last)
			ans = max(ans, i - last + 1);
		else
			last = mymap[s[i]] + 1;
		mymap[s[i]] = i;
	}
	return ans;
}

#endif // !LENGTHOFLONGESTSUBSTRING_H