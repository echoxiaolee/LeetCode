#ifndef RANDOMLIST_H
#define RANDOMLIST_H

#include<iostream>
#include<map>
using namespace std;

// Definition for singly-linked list with a random pointer.
struct RandomListNode {
	int label;
	RandomListNode *next, *random;
	RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

void insertFront(RandomListNode *&ll, const int&value)
{
	RandomListNode *p = new RandomListNode(value);
	if (ll == NULL)
	{
		ll = p;
		return;
	}
	p->next = ll;
	ll = p;
}
void printList(const RandomListNode*ll)
{
	const RandomListNode*p = ll;
	int i = 0;
	while (p != NULL)
	{
		i++;
		cout << p->label << ' ';
		p = p->next;
	}
	cout << endl;
}

void makeEmpty(RandomListNode*&ll)
{
	RandomListNode*p = ll;
	while (p != NULL)
	{
		p = p->next;
		delete ll;
		ll = p;
	}
}

RandomListNode *copyRandomList(RandomListNode *head)
{
	if (head == NULL)return NULL;
	map<RandomListNode*, RandomListNode*>m;
	RandomListNode*p = head;
	RandomListNode*res = new RandomListNode(p->label);
	RandomListNode*q = res;
	RandomListNode*post = p->next;
	q->random = p;
	m[p] = post;

	p->next = q;
	p = post;

	RandomListNode*rear = res;
	while (p != NULL)
	{
		q = new RandomListNode(p->label);
		rear->next = q;
		rear = q;
		q->random = p;
		post = p->next;
		m[p] = post;
		p->next = q;
		p = post;
	}

	q = res;
	while (q != NULL)
	{
		if (q->random->random == NULL)q->random = NULL;
		else
			q->random = q->random->random->next;
		q = q->next;
	}

	p = head;
	while (p != NULL)
	{
		p->next = m[p];
		p = p->next;
	}

	return res;
}

RandomListNode *copyRandomList2(RandomListNode *head)
{
	if (head == NULL)return NULL;
	RandomListNode *res = new RandomListNode(head->label);
	RandomListNode*p = head;
	RandomListNode*q = res;
	while (p->next != NULL)
	{
		q->next = p->next;
		p->next = q;
		p = q->next;
		q = new RandomListNode(p->label);
	}
	q->next = p->next;
	p->next = q;

	p = head;
	while (p != NULL)
	{
		if (p->random != NULL)
			p->next->random = p->random->next;
		else
			p->next->random = NULL;
		p = p->next->next;
	}

	p = head;
	q = p->next;
	while (p->next->next != NULL)
	{
		p->next = q->next;
		p = p->next;
		q->next = p->next;
		q = p->next;
	}
	p->next = NULL;

	return res;
}

#endif // !RANDOMLIST_H
