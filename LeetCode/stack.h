#ifndef STACK_H
#define	STACK_H
#include<iostream>
#include<cassert>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
class MinStack {
	stack<int>data;
	stack<int>mini;
public:
	void push(int x) {
		data.push(x);
		if (mini.empty() || x <= mini.top())mini.push(x);
	}

	void pop() {
		if (data.top() == mini.top())mini.pop();
		data.pop();
	}

	int top() {
		return data.top();
	}

	int getMin() {
		return mini.top();
	}
};

class Stack {//Implement Stack using Queues
	queue < int > in;
	queue<int>out;
public:
	// Push element x onto stack.
	void push(int x) {
		in.push(x);
	}

	// Removes the element on top of the stack.
	void pop() {
		if (!in.empty() || !out.empty())
		{
			if (in.empty())
			{
				while (!out.empty())
				{
					if (out.size() == 1)
					{
						out.pop();
						return;
					}
					in.push(out.front());
					out.pop();
				}
			}
			else
			{
				while (!in.empty())
				{
					if (in.size() == 1)
					{
						in.pop();
						return;
					}
					out.push(in.front());
					in.pop();
				}
			}
		}
	}

	// Get the top element.
	int top() {
		if (!in.empty() || !out.empty())
		{
			if (in.empty())
			{
				while (!out.empty())
				{
					if (out.size() == 1)
					{
						in.push(out.front());
						out.pop();
						return in.back();
					}
					in.push(out.front());
					out.pop();
				}
			}
			else
			{
				while (!in.empty())
				{
					if (in.size() == 1)
					{
						return in.front();
					}
					out.push(in.front());
					in.pop();
				}
			}
		}
	}

	// Return whether the stack is empty.
	bool empty() {
		if (in.empty() && out.empty())return true;
		else return false;
	}
};
#endif // !stack_H
