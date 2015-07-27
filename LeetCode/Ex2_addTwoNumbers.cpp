#include<iostream>
#include<list>
using namespace std;
/* Definition for singly-linked list.*/
 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

 ListNode *addTwoNumbers(ListNode *, ListNode *);

 int main(int argc, char*argv[]){
	 
	 //ListNode *l1=NULL, *l2=NULL;
	 //l1->val = 2, l1->next->val = 4, l1->next->next->val = 3, l1->next->next->next=NULL;
	 //l2->val = 5, l2->next->val = 6, l2->next->next->val = 4, l2->next->next->next = NULL;
	 //ListNode *temp=addTwoNumbers(l1, l2);
	 //cout << temp->val << "->" << temp->next->val << "->" << temp->next->next->val << endl;
	 
	 //list<ListNode>l1, l2;
	 //l1.push_back(2), l1.push_back(4), l1.push_back(3);
	 //l2.push_back(5), l2.push_back(6), l2.push_back(4);
	 //list<ListNode>temp;
	 char *ptr1 = "xiaoman";
	 char *ptr2[] = { "xiaoman" ,"beautiful"};
	 size_t n = sizeof(*ptr2);
	 cout << *(1+ptr2) << endl;
	 return EXIT_SUCCESS;
 }


 ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
	 ListNode *temp=NULL;
	 temp->val = (l1->val + l2->val) % 10;
	 int l = (l1->val + l2->val) / 10;

	 temp->next->val = (l1->next->val + l1->next->val + l) % 10;
	 int m = (l1->next->val + l1->next->val + l) / 10;

	 temp->next->next->val = (l1->next->next->val + l2->next->next->val + m) % 10;
	 temp->next->next->next = NULL;
	 //int h = (l1->next->next->val + l2->next->next->val) % 10;
	 return temp;
 }
