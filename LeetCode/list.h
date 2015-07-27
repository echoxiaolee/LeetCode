#ifndef LIST_H
#define LIST_H
#include<iostream>
#include<vector>
#include<iomanip>
#include<algorithm>
#include<map>
#include<stack>
using namespace std;
//Definition for singly-linked list.
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};


ListNode *getRear(ListNode *);

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
	if (l1 == NULL)return l2;
	if (l2 == NULL)return l1;
	ListNode*rl1 = l1;
	ListNode*rl2 = l2;
	ListNode*result = new ListNode((rl1->val + rl2->val) % 10);
	ListNode*p=result;
	int temp = (rl1->val + rl2->val) /10;
	while (rl1->next != NULL && rl2->next != NULL)
	{
		temp = temp + rl1->next->val + rl2->next->val;
		p->next = new ListNode(temp%10);
		temp = temp / 10;
		p = p->next;
		rl1 = rl1->next;
		rl2 = rl2->next;
	}
	if (rl1->next == NULL&& rl2->next == NULL&&temp == 0)return result;
	else if (rl1->next == NULL&& rl2->next == NULL)
	{
		p->next = new ListNode(temp % 10);
		p = p->next;
	}
	else if (rl1->next == NULL&&rl2->next != NULL)
	{
		while (rl2->next != NULL)
		{
			temp = temp + rl2->next->val;
			p->next = new ListNode(temp);
			temp = temp / 10;
			p = p->next;
			rl2 = rl2->next;
		}
		if (temp != 0)
		{
			p->next = new ListNode(temp );
			p = p->next;
		}
	}
	else 
	{
		while (rl1->next != NULL)
		{
			temp = temp + rl1->next->val;
			p->next = new ListNode(temp % 10);
			temp = temp / 10;
			p = p->next;
			rl1 = rl1->next;
		}
		if (temp != 0)
		{
			p->next = new ListNode(temp % 10);
			p = p->next;
		}
	}
	return result;
}

ListNode*copyList(ListNode*head)
{
	if (head == NULL)return NULL;
	ListNode*p =head;
	ListNode*res = new ListNode(p->val);
	ListNode*q = res;
	ListNode*rear = res;
	while (p->next != NULL)
	{
		q = new ListNode(p->next->val);
		rear->next = q;
		rear = q;
		p = p->next;
	}
	return res;
}

ListNode*reverseList(ListNode*ll)//iteratively 
{
	if (ll != NULL)
	{
		ListNode*p = ll;
		ListNode*result = new ListNode(p->val);
		ListNode*q;
		while (p->next != NULL)
		{
			q = new ListNode(p->next->val);
			q->next = result;
			result = q;
			p = p->next;
		}
		return result;
	}
	return NULL;
}

ListNode* reverseList2(ListNode* head) //
{
	if (head != NULL)
	{
		ListNode*p = head->next;
		ListNode*q = head;
		while (head->next != NULL)
		{
			head->next = p->next;
			p->next = q;
			q = p;
			p = head->next;
		}
		return q;
	}
	return NULL;
}

ListNode* reverseList3(ListNode* head)//recursively
{
	if (head == NULL || head->next == NULL)return head;
	ListNode*res = reverseList3(head->next);
	ListNode*rear = getRear(res);
	rear->next = head;
	head->next = NULL;
	return res;
}

void makeEmpty(ListNode*&ll)
{
	ListNode*p = ll;
	while (p != NULL)
	{
		p = p->next;
		delete ll;
		ll = p;
	}
}
void printList(const ListNode*ll)
{
	const ListNode*p = ll;
	int i = 0;
	while (p != NULL)
	{
		i++;
		cout << p->val << ' ';
		p = p->next;
	}
	cout << endl;
}

ostream&operator<<(ostream&out, const ListNode*ll)
{
	const ListNode*p = ll;
	int i = 0;
	while (p != NULL)
	{
		i++;
		out << p->val << ' ';
		p = p->next;
	}
	out << endl;
	return out;
}

int length(const ListNode *ll)
{
	const ListNode *p = ll;
	int k = 0;
	while (p != NULL)
	{
		k++;
		p = p->next;
	}
	return k;
}

ListNode *getRear(ListNode *ll)
{
	if (ll == NULL||ll->next==NULL)return ll;
	ListNode *p = ll;
	while (p->next != NULL)p = p->next;
	return p;
}

void insertFront(ListNode *&ll,const int&value)
{
	ListNode *p = new ListNode(value);
	if (ll == NULL)
	{
		ll = p;
		return;
	}
	p->next = ll;
	ll = p;
}

void insertBack(ListNode *&ll,  const int&value)
{
	ListNode *p = new ListNode(value);
	if (ll == NULL)
	{
		ll = p;
		return;
	}
	getRear(ll)->next=p;
}

ListNode* swapPairs(ListNode* head) 
{
	if (head == NULL || head->next == NULL)return head;
	ListNode*p = head;
	ListNode*q = head->next;
	ListNode*newHead =q;
	int len = length(head);

	p->next = q->next;
	q->next = p;
	ListNode*last=p;

	if (len % 2 == 0)
	{
		for (int i = 0; i < (len-2)/2; i++)
		{
			p = p->next;
			q = p->next;
			p->next = q->next;
			q->next = p;
			last->next = q;
			last = p;
		}
		p->next = NULL;
	}
	else
	{
		for (int i = 0; i < (len - 3) / 2; i++)
		{
			p = p->next;
			q = p->next;
			p->next = q->next;
			q->next = p;
			last->next = q;
			last = p;
		}
	}
	return newHead;
}

void swap(ListNode*node1, ListNode*node2)
{
	if (node1 != NULL&&node2 != NULL)
	{
		int temp = node1->val;
		node1->val = node2->val;
		node2->val = temp;
	}
}

void selectionSortList(ListNode* head)//选择排序
{
	if (head == NULL || head->next == NULL)return;
	//ListNode*newHead = head;

	ListNode*p = head;
	ListNode*q = p->next;
	ListNode*temp=p;
	while (p->next!=NULL)
	{
		while (q!=NULL)
		{
			if (temp->val> q->val)
			{
				//swap(temp, q);
				temp = q;
			}
			q = q->next;
		}
		if (temp != p)
		{
			swap(temp, p);
			p = p->next;
			q = p->next;
			temp = p;
		}
		else
		{
			p = p->next;
			q = p->next;
			temp = p;
		}
	}
	//return newHead;
}



ListNode* sort(ListNode* head)//效率低
{
	vector<int>vec;
	while (head != NULL)
	{
		vec.push_back(head->val);
		head = head->next;
	}
	ListNode*p = NULL;
	sort(vec.begin(), vec.end());
	for (int i = 0; i != vec.size(); i++)
		insertBack(p, vec[i]);
	return p;
}

void swap(int*a, int*b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void reverseBetween(ListNode* &head, ListNode*tail)//左闭右开，即[head,tail),将此范围内的元素反转
{
	if (head != NULL)
	{
		ListNode*p = head->next;
		ListNode*q = head;
		while (head->next != tail)
		{
			head->next = p->next;
			p->next = q;
			q = p;
			p = head->next;
		}
		//tail = head;
		head = q;
	}
}

ListNode* reverseBetween(ListNode* &head, int m, int n) 
{
	int len = length(head);
	if (m<1 || n<1 || n>len|| m>=n ||head==NULL||head->next==NULL)return head;
	ListNode*pm;
	ListNode*pn;
	ListNode*temp=head;

	ListNode*pre=NULL;

	int i = 1;
	while (i < m-1)
	{
		i++;
		temp = temp->next;
	}
	if (m == 1)pm = head;
	else
	{
		pre = temp;//指向第m-1个元素
		pm = pre->next;
	}
	while (i < n)
	{
		i++;
		temp = temp->next;
	}

	pn = temp;//指向第n个元素
	//post = pn->next;
	reverseBetween(pm, pn->next);
	if (m == 1)head = pm;
	else
		pre->next = pm;
	//pn->next = post;
	return head;
}

ListNode* rotateRight(ListNode* head, int k) 
{
	int len = length(head);
	if (len == 1 || len == 0)return head;
	if (k%len == 0)return head;
	k = k%len;

	int i = 1;
	ListNode*p = head;
	while (i<len-k)
	{
		i++;
		p = p->next;
	}

	ListNode*rear = getRear(p);
	rear->next = head;
	ListNode*newHead = p->next;
	p->next = NULL;
	return newHead;

}

ListNode* reverseKGroup(ListNode* head, int k)
{
	if (head == NULL || head->next == NULL || k < 2)return head;
	int len = length(head);

	int size = len / k;//4

	ListNode*p = head;

	for (int i = 1; i <= size; i++)
	{
		p=reverseBetween(head, (i - 1)*k + 1, k*i);
	}
	return p;
}

void reorderList(ListNode* head)
{
	int len = length(head);
	if (len > 2)
	{
		int i = 1;
		ListNode*mid = head;
		ListNode*p = head;
		while (i < (len + 1) / 2)
		{
			i++;
			mid = mid->next;
		}

		ListNode*q = mid->next;
		reverseBetween(q, NULL);
		mid->next = q;

		if (len % 2 == 1)
		{
			while (q != NULL)
			{
				mid->next = q->next;
				q->next = p->next;
				p->next = q;
				p = p->next->next;
				q = mid->next;
			}
		}
		else
		{
			while (q->next != NULL)
			{
				mid->next = q->next;
				q->next = p->next;
				p->next = q;
				p = p->next->next;
				q = mid->next;
			}
		}
	}
}

ListNode* removeNthFromEnd(ListNode* head, int n) 
{
	int len = length(head);
	if (len == 0 || n > len||n<=0)return head;
	ListNode*p = head;
	if (n == len)
	{
		head = head->next;
		delete p;
		return head;
	}
	for (int i = 1; i < len - n; i++)
	{
		p = p->next;
	}
	ListNode*q = p->next;
	p->next = q->next;
	delete q;
	return head;
}

ListNode*searchValue(ListNode* head, int val)
{
	ListNode*p = head;
	while (p != NULL)
	{
		if (p->val == val)break;
		p = p->next;
	}
	return p;
}

/*Remove all elements from a linked list of integers that have value val.*/
ListNode* removeElements(ListNode* head, int val) 
{
	ListNode*p = head;
	ListNode*q = head;
	while (p != NULL&&p->val == val)
	{
		q = q->next;
		delete p;
		p = q;
		head = p;
	}
	if (head == NULL)return head;

	while (p->next != NULL)
	{
		p = p->next;
		if (p->val == val)
		{
			q->next = p->next;
			delete p;
			p = q;
			continue;
		}
		q = q->next;
	}
	return head;
}

/*Given a sorted linked list, delete all duplicates such that each element appear only once.*/
ListNode* deleteDuplicates(ListNode* head) 
{
	if (head == NULL || head->next == NULL)return head;
	ListNode*p = head->next;
	ListNode*q = head;
	while (q!=NULL&&q->next != NULL)
	{
		while (p != NULL&&p->val == q->val)
		{
			q->next = p->next;
			delete p;
			p = q->next;
		}
		q = q->next;
		if (q!=NULL)
		p = q->next;
	}
	return head;
}

/***********************************************************
*	Given a sorted linked list, delete all nodes that have duplicate numbers, 
*	leaving only distinct numbers from the original list. 
*	For example,
*	Given 1->2->3->3->4->4->5, return 1->2->5.
*	Given 1->1->1->2->3, return 2->3.
**************************************************************/

ListNode* deleteDuplicates2(ListNode* head)
{
	if (head == NULL || head->next == NULL)return head;
	ListNode*p = head->next;
	ListNode*q = head;
	ListNode*temp = p->next;
	
	if (temp == NULL)
	{
		if (p->val == q->val)
			return NULL;
		else
			return head;
	}

	while (temp!= NULL)
	{
		if (p->val != q->val&&p->val != temp->val)
			break;
		p = p->next;
		q = q->next;
		temp = temp->next;
	}
	if (head->val != head->next->val&&head -> val != head->next->next->val)
		temp = head;
	else
	{
		if (temp == NULL&&p->val == q->val)
		{
			makeEmpty(head);
			return NULL;
		}
		temp = p;
	}


	p = head->next;
	q = head;
	ListNode*pre = head;
	bool flag = false;
	while (q != NULL&&q->next != NULL)
	{
		while (p != NULL&&p->val == q->val)
		{
			flag = true;
			q->next = p->next;
			delete p;
			p = q->next;
		}
		if (flag)
		{
			pre->next = q->next;
			delete q;
			q = p;
		}
		if (q != NULL)
		{
			if (flag == false)
			{
				pre = q;
				q = q->next;
			}
			p = q->next;
		}

		flag = false;
	}
	return temp;
}

ListNode* insertionSortList(ListNode* head)//直接插入排序
{
	if (head==NULL||head->next==NULL)return head;

	ListNode*p = head->next;
	ListNode*q = head;
	ListNode*it = head;
	while (p != NULL)
	{
		if (p->val >= q->val)
		{
			q = q->next;
			p = p->next;
			continue;
		}
		it = head;
		while (it != q->next)
		{
			if (it->val > p->val&&it==head)
			{
				q->next = p->next;
				p->next = it;
				head = p;
				p = q->next;
				break;
			}
			if (it->next->val > p->val)
			{
				q->next = p->next;
				p->next = it->next;
				it->next = p;
				p = q->next;
				break;
			}
			it = it->next;
		}
	}
	return head;
}



bool hasCycle(ListNode *head) 
{
	if (head == NULL||head->next==NULL)return false;
	ListNode*p = head;
	ListNode*q = head;
	while (p != NULL)
	{
		if (p->next == NULL)
			p = p->next;
		else
			p = p->next->next;
		q = q->next;
		if (p == q)return true;
	}
	return false;
}

//Given a linked list, return the node where the cycle begins.If there is no cycle, return null.
ListNode *detectCycle(ListNode *head) 
{
	if (hasCycle(head))
	{
		map<ListNode *, int>m;
		ListNode *p = head;
		while (1)
		{
			m[p]++;
			p = p->next;
			if (m[p] > 1)break;
		}
		return p;
	}
	return NULL;
}

//Write a program to find the node at which the intersection of two singly linked lists begins.
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
{
	map<ListNode *, int>m;
	ListNode *p = headA;
	ListNode *q = headB;
	while (p != NULL)
	{
		m[p]++;
		p = p->next;
	}
	while (q != NULL)
	{
		m[q]++;
		if (m[q] > 1)return q;
		q = q->next;
	}
	return NULL;
}

ListNode *getIntersectionNode2(ListNode *headA, ListNode *headB)
{
	ListNode *reara = getRear(headA);
	ListNode *rearb = getRear(headB);
	if (reara == NULL || rearb == NULL || reara != rearb)return NULL;
	ListNode *pa = headA;
	ListNode *pb = headB;
	while (pa!= NULL&&pb!= NULL)
	{
		if (pa == pb)return pb;
		pb = pb->next;
		pa = pa->next;
	}

	if (pa == NULL&&pb != NULL)
	{
		pa = headB;
		rearb->next = headA;
	}
	if (pb == NULL&&pa != NULL)
	{
		pb = headA;
		reara->next = headB;
	}
	while (1)
	{
		if (pa == pb)
		{
			rearb->next = NULL;
			reara->next = NULL;
			break;
		}
		pb = pb->next;
		pa = pa->next;
	}
	return pb;
}
ListNode *getIntersectionNode3(ListNode *headA, ListNode *headB)
{
	ListNode *pa = headA;
	ListNode *pb = headB;
	if (pa == NULL || pb == NULL)return NULL;
	while (pa != NULL&&pb != NULL&&pa!=pb)
	{
		pa = pa->next;
		pb = pb->next;
		if (pa == pb)return pa;

		if (pa == NULL)pa = headB;
		if (pb == NULL)pb = headA;
	}
	return pb;
}

ListNode *detectCycle2(ListNode *head)
{
	if (head == NULL || head->next == NULL)return NULL;
	ListNode*p = head;
	ListNode*q = head;
	while (p != NULL)
	{
		if (p->next == NULL)
			p = p->next;
		else
			p = p->next->next;
		q = q->next;
		if (p == q)break;
	}
	if (p == NULL)return NULL;
	p = p->next;
	q->next = NULL;
	return getIntersectionNode3(p, head);
}

//Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.
//You should preserve the original relative order of the nodes in each of the two partitions. 
ListNode* partition(ListNode* head, int x)
{
	if (head == NULL || head->next == NULL)return head;
	ListNode*p = head;
	ListNode*q;
	ListNode*temp = NULL;

	ListNode*right = NULL;//右边
	ListNode*rear = NULL;

	ListNode*left = NULL;//左边
	ListNode*tail = NULL;//

	int i = 0;
	while (p!= NULL)//找到第一个值等于x的节点，p保存该节点位置
	{
		if (p->val == x)break;
		p = p->next;
	}


	ListNode*pos = head;
	while (pos!=p)//找到第一个值大于x的节点，pos保存该节点位置
	{
		if (pos->val > x)break;
		pos= pos->next;
	}

	if (p != NULL)//表中包含值等于x的节点
	{
		if (pos != p)//如果pos==p，说明在p之前没有比x大的节点
		{
			q = pos;//左边
			while (q != p)//q从pos开始遍历到p，找到并从原来表中删除所有比x小的节点，保存到left中，tail指向left表结尾
			{
				if (q->next->val < x)
				{
					i++;
					temp = q->next;
					q->next = temp->next;
					temp->next = NULL;
					if (i == 1)
					{
						left = tail = temp;
					}
					else
					{
						tail->next = temp;
						tail = temp;
					}
				}
				else
					q = q->next;
			}
		}

		q = p;//右边
		i = 0;
		while (q->next != NULL)//q从p开始遍历表剩余部分，找到并从原来表中删除所有比x小的节点，保存到right中，rear指向right表结尾
		{
			if (q->next->val < x)
			{
				i++;
				temp = q->next;
				q->next = temp->next;
				temp->next = NULL;
				if (i == 1)
				{
					right = rear = temp;
				}
				else
				{
					rear->next = temp;
					rear = temp;
				}
			}
			else
				q = q->next;
		}

		if (left != NULL)
		{
			tail->next = right;
			if (right == NULL)
			{
				right = left;
				rear = tail;
			}
		}
		else
		{
			left = right;
			tail = rear;
		}

		temp = head;
		while (temp != NULL)//找到第一个值大于或等于x的节点的前导节点，temp保存该节点位置
		{
			if (temp == head&&temp->val >= x&&left != NULL)
			{
				rear->next = head;
				head = left;
				return head;
			}
			if (temp->next->val >= x)break;
			temp = temp->next;
		}
		if (left != NULL)
		{
			rear->next = temp->next;
			temp->next = left;
		}
	}

	else//表中不包含值等于x的节点
	{
		p = head;
		while (p->next != NULL)
		{
			if (p->val > x&&p->next->val < x)break;
			p = p->next;
		}
		if (p->next == NULL)//表中所有节点的值均大于或者小于x
		{
			return head;
		}

		//表中不包含值等于x的节点，但x介于某两个相邻节点的值之间，p指向最后一个值大于x的节点


		if (pos != p)//如果pos==p，说明在p之前没有比x大的节点
		{
			q = pos;//左边
			while (q != p)//q从pos开始遍历到p，找到并从原来表中删除所有比x小的节点，保存到left中，tail指向left表结尾
			{
				if (q->next->val < x)
				{
					i++;
					temp = q->next;
					q->next = temp->next;
					temp->next = NULL;
					if (i == 1)
					{
						left = tail = temp;
					}
					else
					{
						tail->next = temp;
						tail = temp;
					}
				}
				else
					q = q->next;
			}
		}

		q = p;//右边
		i = 0;
		while (q->next != NULL)//q从p开始遍历表剩余部分，找到并从原来表中删除所有比x小的节点，保存到right中，rear指向right表结尾
		{
			if (q->next->val < x)
			{
				i++;
				temp = q->next;
				q->next = temp->next;
				temp->next = NULL;
				if (i == 1)
				{
					right = rear = temp;
					if (right == NULL)
					{
						right = left;
						rear = tail;
					}
				}
				else
				{
					rear->next = temp;
					rear = temp;
				}
			}
			else
				q = q->next;
		}

		if (left != NULL)
		{
			tail->next = right;
		}
		else
		{
			left = right;
			tail = rear;
		}

		temp = head;
		while (temp != NULL)//找到第一个值大于x的节点的前导节点，temp保存该节点位置
		{
			if (temp == head&&temp->val >= x&&left != NULL)
			{
				rear->next = head;
				head = left;
				return head;
			}
			if (temp->next->val >= x)break;
			temp = temp->next;
		}
		if (left != NULL)
		{
			rear->next = temp->next;
			temp->next = left;
		}
	}
	return head;
}

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)//重新分配空间，合并到另外一个更大的链表中
{
	if (l1 == NULL)return l2;
	if (l2 == NULL)return l1;
	ListNode*head=NULL;
	ListNode*tail=NULL;
	ListNode*p = l1;
	ListNode*q = l2;
	ListNode*temp;
	int i = 0;
	while (p != NULL&&q != NULL)
	{
		i++;
		if (p->val <= q->val)
		{
			if (i == 1)
				head = tail = new ListNode(p->val);
			else
			{
				temp = new ListNode(p->val);
				tail->next = temp;
				tail = temp;
			}
			p = p->next;
		}
		else
		{
			if (i == 1)
				head = tail = new ListNode(q->val);
			else
			{
				temp = new ListNode(q->val);
				tail->next = temp;
				tail = temp;
			}
			q = q->next;
		}
	}
	if (p == NULL)
	{
		tail->next = copyList(q);
	}
	if (q==NULL)
		tail->next = copyList(p);
	return head;
}

ListNode* mergeTwoLists2(ListNode* l1, ListNode* l2)//不重新分配空间，但是原来链表的结构会被破坏
{
	if (l1 == NULL)return l2;
	if (l2 == NULL)return l1;
	ListNode*head = NULL;
	ListNode*tail = NULL;
	ListNode*p = l1;
	ListNode*q = l2;
	int i = 0;
	while (p != NULL&&q != NULL)
	{
		i++;
		if (p->val <= q->val)
		{
			if (i == 1)
				head = tail = p;
			else
			{
				tail->next = p;
				tail = p;
			}
			p = p->next;
		}
		else
		{
			if (i == 1)
				head = tail = q;
			else
			{
				tail->next = q;
				tail = q;
			}
			q = q->next;
		}
	}
	if (p == NULL)
	{
		tail->next = q;
	}
	if (q == NULL)
		tail->next = p;

	return head;
}

ListNode* mergeKLists(vector<ListNode*>& lists)//迭代
{
	if (lists.size() < 1)return NULL;
	if (lists.size() == 1)return lists.front();
	ListNode*head = NULL;
	for (vector<ListNode*>::size_type it = 0; it != lists.size(); it++)
	{
		head = mergeTwoLists2(head, lists[it]);
	}
	return head;
}

ListNode* mergeKLists2(vector<ListNode*>& lists)//先迭代后递归
{
	if (lists.size() < 1)return NULL;
	if (lists.size() == 1)return lists.front();
	ListNode*first = NULL;
	vector<ListNode*>vec;
	for (vector<ListNode*>::size_type it = 0; it != lists.size()/2; it++)
	{
		first = mergeTwoLists2(lists[it + lists.size() / 2], lists[it]);
		vec.push_back(first);
	}
	if (lists.size() % 2 == 1)
	{
		vec.push_back(lists.back());
	}
	return mergeKLists2(vec);
}


ListNode* sortList(ListNode* head)//归并排序
{
	if (head == NULL || head->next == NULL)return head;
	//if (head->next->next == NULL)
	//{
	//	if (head->val > head->next->val)
	//	{
	//		head->next->next = head;
	//		head = head->next;
	//		head->next->next = NULL;
	//	}
	//	return head;
	//}
	ListNode*p = head;
	ListNode*q = p->next;
	//int i = 2;
	while (q->next != NULL)
	{
		p = p->next;
		if (q->next->next == NULL)
		{
			q = q->next;
			//i = 1;//奇数个节点
		}
		else
		{
			q = q->next->next;
			//i = 2;//偶数个节点
		}
	}
	q = p->next;
	p->next = NULL;
	p = head;
	ListNode*l = sortList(p);
	ListNode*r = sortList(q);
	return mergeTwoLists2(l, r);
}


//Given a singly linked list, determine if it is a palindrome.
bool isPalindrome(ListNode* head) 
{
	if (head == nullptr || head->next == nullptr)return true;
	ListNode*p = head;
	stack<ListNode*>s;
	while (p != NULL)
	{
		s.push(p);
		p = p->next;
	}
	p = head;
	while (p != s.top()&&p->next!=s.top())
	{
		if (p->val != s.top()->val)return false;
		else
		{
			p = p->next;
			s.pop();
		}
	}
	if (p == s.top()||p->next == s.top() && p->val == s.top()->val)return true;
	else return false;;
}


//Delete Node in a Linked List 
void deleteNode(ListNode* node)
{
	ListNode*p = node;
	ListNode*pre = nullptr;
	while (p != nullptr&&p->next != nullptr)
	{
		p->val = p->next->val;
		pre = p;
		p = p->next;
	}
	if (p != NULL&&p->next == NULL&&pre!=nullptr)
	{
		pre->next = nullptr;
		delete p;
	}
	else
	{
		delete node;
		node = nullptr;
	}
}

#endif // !LIST_H