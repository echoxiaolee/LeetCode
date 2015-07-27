#ifndef QUEUE_H
#define	QUEUE_H

#include<stack>
#include<iostream>
using namespace std;

class Queue {//Implement Queue using Stacks 
	stack<int>in;
	stack<int>out;
public:
	// Push element x to the back of queue.
	void push(int x) {
		in.push(x);
	}

	// Removes the element from in front of queue.
	void pop(void) {
		if (!out.empty())out.pop();
		else if (out.empty() && !in.empty())
		{
			while (!in.empty())
			{
				out.push(in.top());
				in.pop();
			}
			out.pop();
		}
		else
		{
			return;
		}
	}

	// Get the front element.
	int peek(void) {
		if (!empty())
		{
			int top;
			if (!out.empty()) top = out.top();
			else if (out.empty() && !in.empty())
			{
				while (!in.empty())
				{
					out.push(in.top());
					in.pop();
				}
				top = out.top();
			}
			return top;
		}
	}

	// Return whether the queue is empty.
	bool empty(void) {
		if (in.empty() && out.empty())return true;
		else return false;
	}
};

#endif // !QUEUE_H
