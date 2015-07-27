#ifndef BINARYTREE_H
#define BINARYTREE_H

#include<iostream>
#include<cassert>
#include<vector>
#include<algorithm>
#include<stack>
#include<queue>
#include<iterator>
#include<map>
using namespace std;

//Definition for singly-linked list.
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。
TreeNode*Convert(TreeNode*root)
{
	if (root != NULL)
	{
		TreeNode*l = Convert(root->left);
		TreeNode*r = Convert(root->right);

		if (l == nullptr&&r == nullptr)
		{
			l = r = root;
			l->left = root;
			r->left->right = root;
		}
		else if (l == nullptr&&r != nullptr)
		{
			l = root;
			root->right = r;
			l->left = r->left;
			r->left->right = l;
			r->left = root;
		}
		else if (l != nullptr&&r == nullptr)
		{
			r = root;
			l->left->right = root;
			root->left = l->left;
			root->right = l;
			l->left = root;
		}
		else
		{
			l->left->right = root;
			root->left = l->left;
			l->left = r->left;
			root->right = r;
			r->left->right = l;
			r->left = root;
		}
		return l;
	}
	return root;
}

//Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.
/**
* Your BSTIterator will be called like this:
* BSTIterator i = BSTIterator(root);
* while (i.hasNext()) cout << i.next();
*/

class BSTIterator {
	stack<TreeNode *>s;//s保存搜索中序遍历下第一个节点过程中的父节点
	TreeNode *r;//r指向二叉搜索树中序遍历下的第一个节点
public:
	BSTIterator(TreeNode *root) {
		r = root;
		while (r!=NULL&&r->left != NULL)
		{
			s.push(r);
			r = r->left;
		}
	}

	/** @return whether we have a next smallest number */
	bool hasNext() {
		if (r != NULL)return true;
		else
		{
			return false;
		}
	}

	/** @return the next smallest number */
	int next() {
		int res;
		if (r->left==NULL&&r->right == NULL)
		{
			res = r->val;
			if (s.empty())
			{
				r = NULL;
			}
			else
			{
				r = s.top();
				s.pop();
				r->left = NULL;
			}
		}
		else if (r->left==NULL&&r->right!=NULL)
		{
			res = r->val;
			r = r->right;
			if(!s.empty())s.top()->left = r;
		}
		else//r->left!=NULL&&r->right!=NULL
		{
			while (r->left != NULL)
			{
				s.push(r);
				r = r->left;
			}
			res = r->val;

			if (s.empty())
				r = r->right;
			else
			{
				if (r->right != NULL)
				{
					s.top()->left = r->right;
					r = r->right;
				}
				else
				{
					r = s.top();
					s.pop();
					r->left = NULL;
				}
			}
		}
		return res;
	}
};


// Definition for binary tree with next pointer.
struct TreeLinkNode {
int val;
TreeLinkNode *left, *right, *next;
TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

//Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.
//Initially, all next pointers are set to NULL.

void connect2(TreeLinkNode *root) 
{
	if (root != nullptr&&(root->left!=nullptr||root->right!=nullptr))
	{
		queue<TreeLinkNode *>que;
		que.push(root);
		int size = 1;
		while (!que.empty())
		{

			if (size == 0)
			{
				size = que.size();
			}

			TreeLinkNode *p = que.front();
			que.pop();
			size--;

			if (size!=0)
			{
				p->next = que.front();
			}

			if (p->left != nullptr)que.push(p->left);
			if (p->right != nullptr)que.push(p->right);

		}
	}
}



TreeNode*createBinaryTree(const int*VLR, const int*LVR, int n)//给出前序遍历和中序遍历序列，构造二叉树,VLR存储前序遍历序列，LVR存储后续遍历序列
{
	if (n == 0)return NULL;
	int k = 0;
	while (VLR[0] != LVR[k])k++;
	TreeNode*root = new TreeNode(VLR[0]);
	root->left = createBinaryTree(VLR + 1, LVR, k);
	root->right = createBinaryTree(VLR+k+1,LVR+k+1,n-k-1);
	return root;
}

//Given preorder and inorder traversal of a tree, construct the binary tree.
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)
{
	/*if (!preorder.empty())
	{
		int k = 0;
		while (preorder[0] != inorder[k])k++;
		TreeNode*root = new TreeNode(preorder[0]);
		root->left = buildTree\
			(vector<int>(preorder.begin() + 1, preorder.begin() + k + 1), \
			vector<int>(inorder.begin(), inorder.begin()+k));
		root->right = buildTree\
			(vector<int>(preorder.begin() + k + 1, preorder.end()), \
			vector<int>(inorder.begin() + k + 1, inorder.end()));
		return root;
	}
	return nullptr;*/
	if (!preorder.empty())
	{
		int k = 0;
		while (preorder[0] != inorder[k])k++;
		TreeNode*root = new TreeNode(preorder[0]);
		vector<int>lpre = vector<int>(preorder.begin() + 1, preorder.begin() + k + 1);
		preorder.erase(preorder.begin(), preorder.begin() + k + 1);
		vector<int>lin = vector<int>(inorder.begin(), inorder.begin() + k);
		inorder.erase(inorder.begin(), inorder.begin() + k);

		vector<int>rpre(preorder.begin(), preorder.end());
		preorder.clear();
		vector<int>rin(inorder.begin() + 1, inorder.end());
		inorder.clear();

		root->left = buildTree(lpre, lin);

		root->right = buildTree(rpre, rin);

		return root;
	}
	return nullptr;
}

void insert(TreeNode*&root, int x)//二叉搜索树的插入算法
{
	if (root == NULL)
	{
		TreeNode*temp = new TreeNode(x);
		assert(temp);
		root = temp;
	}
	else
	{
		if (x < root->val)insert(root->left, x);
		else
			insert(root->right, x);
	}
}


void destroy(TreeNode*root)//释放节点用后序遍历
{
	if (root != NULL)
	{
		destroy(root->left);
		destroy(root->right);
		delete root;
	}
}

int size(TreeNode*root)
{
	if (root == NULL)return 0;

	int l = size(root->left);
	int r = size(root->right);
	return l + r + 1;
}

int height(TreeNode*root)//树的高度
{
	if (root == NULL)return 0;
	int l = height(root->left);
	int r = height(root->right);
	return l > r ? l + 1 : r + 1;
}

bool isBalanced(TreeNode* root) 
{
	if (root == NULL)return true;

	int l = height(root->left);
	int r = height(root->right);
	if (abs(l - r) > 1)return false;
	bool ll = isBalanced(root->left);
	bool rr = isBalanced(root->right);
	if (ll&&rr)return true;
	return false;
}

vector<int> prePrintTree(TreeNode*root)//前序遍历输出
{
	vector<int>temp;
	if (root != NULL)
	{
		cout << root->val << ' ';
		temp.push_back(root->val);
		vector<int>l = prePrintTree(root->left);
		vector<int>r = prePrintTree(root->right);
		copy(l.begin(), l.end(),inserter(temp,temp.end()));
		copy(r.begin(),r.end(), inserter(temp, temp.end()));
	}
	return temp;
}

vector<int> inPrintTree(TreeNode*root)//中序遍历输出
{
	vector<int>temp;
	if (root != NULL)
	{
		vector<int>l=inPrintTree(root->left);
		cout << root->val << ' ';
		temp.push_back(root->val);
		vector<int>r=inPrintTree(root->right);
		copy(l.begin(), l.end(), inserter(temp, temp.begin()));
		copy(r.begin(), r.end(), inserter(temp, temp.end()));
	}
	return temp;
}
vector<int> postPrintTree(TreeNode*root)//后序遍历输出
{
	vector<int>temp;
	if (root != NULL)
	{
		vector<int>l=postPrintTree(root->left);
		vector<int>r = postPrintTree(root->right);
		cout << root->val << ' ';
		copy(l.begin(), l.end(), inserter(temp, temp.begin()));
		copy(r.begin(), r.end(), inserter(temp, temp.end()));
		temp.push_back(root->val);
	}
	return temp;
}
TreeNode*find(TreeNode*root,const int& x)//二叉排序树递归查找算法
{
	if (root != NULL)
	{
		if (root->val == x)return root;
		else if (root->val > x)return find(root->left, x);
		else return find(root->right, x);
	}
	return NULL;
}

TreeNode*find2(TreeNode*root, const int& x)//二叉排序树迭代查找算法
{
	TreeNode*p = root;
	while (p != NULL)
	{
		if (p->val == x)break;
		else if (p->val > x)p=p->left;
		else p=p->right;
	}
	return p;
}

bool remove(TreeNode*&root, int x)//二叉搜索树删除算法
{
	if (root == NULL)return false;
	TreeNode*temp;
	if (root->val > x)return remove(root->left, x);
	else if (root->val < x)return remove(root->right, x);
	else
	{
		if (root->left != NULL&&root->right != NULL)
		{
			temp = root->right;
			while (temp->left != NULL)temp = temp->left;
			root->val = temp->val;
			return remove(root->right, temp->val);
		}
		else
		{
			temp = root;
			if (root->left == NULL)root = root->right;
			else root = root->left;
			delete temp;
			return true;
		}
	}
}

void swap(TreeNode* &root)
{
	if (root != NULL)
	{
		TreeNode*temp = root->left;
		root->left = root->right;
		root->right = temp;
	}
}

TreeNode*copyTree(TreeNode*root)
{
	TreeNode*p = root;
	TreeNode*newHead = NULL;
	if (p!=NULL)
	{	
		TreeNode*temp = new TreeNode(p->val);
		newHead = temp;
		newHead->left = copyTree(p->left);
		newHead->right = copyTree(p->right);
	}
	return newHead;
}

TreeNode* invertTree(TreeNode* root)
{
	if (root != NULL)
	{
		TreeNode*temp = root->left;
		root->left = root->right;
		root->right = temp;
		invertTree(root->left);
		invertTree(root->right);
	}
	return root;
}
bool isSameTree(TreeNode* p, TreeNode* q) 
{
	if (p == NULL&&q == NULL)return true;
	//if (p == NULL&&q != NULL || p != NULL&&q == NULL)return false;

	if (p != NULL&&q != NULL)
	{
		if (p->val == q->val&&isSameTree(p->left, q->left) && isSameTree(p->right, q->right))return true;
		else return false;
	}
	return false;
}

bool isSymmetric(TreeNode* root) {
	TreeNode*p = copyTree(root);
	invertTree(root);
	bool flag = isSameTree(root, p);
	destroy(p);
	if (flag)
		return true;
	return false;
}

//Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.
TreeNode* sortedListToBST(ListNode* head) 
{
	if (head == NULL)return NULL;
	if (head->next == NULL)return new TreeNode(head->val);

	ListNode*p = head;
	ListNode*pre=head;

	ListNode*q = p->next;
	//int i = 2;
	while (q->next != NULL)
	{
		pre = p;
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
	pre->next = NULL;
	TreeNode*root = new TreeNode(p->val);

	TreeNode*l;
	if (p == head)l = NULL;
	else l= sortedListToBST(head);
	TreeNode*r = sortedListToBST(q);

	root->left = l;
	root->right = r;

	pre->next = p;
	p->next = q;

	return root;
}


//Lowest Common Ancestor of a Binary Search Tree
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
{
	if (root != nullptr&&p != nullptr&&q != nullptr)
	{
		if (p->val <= root->val&&q->val >= root->val || p->val >= root->val&&q->val <= root->val)return root;
		else if (p->val < root->val&&q->val < root->val)return lowestCommonAncestor(root->left,p,q);
		else return lowestCommonAncestor(root->right,p,q);
	}
	return nullptr;
}

//Lowest Common Ancestor of a Binary Tree
TreeNode* lowestCommonAncestor2(TreeNode* root, TreeNode* p, TreeNode* q)//栈实现遍历
{
	map<TreeNode*, TreeNode*>parent;
	stack<TreeNode*>s;
	if (root != nullptr&&p != nullptr&&q != nullptr)
	{
		parent[root] = nullptr;
		while (root->left != nullptr)
		{

		}
	}
	return nullptr;
}

TreeNode* lowestCommonAncestor3(TreeNode* root, TreeNode* p, TreeNode* q)//队列实现层次遍历
{
	map<TreeNode*, TreeNode*>parent;
	queue<TreeNode*>que;
	if (root != nullptr&&p != nullptr&&q != nullptr)
	{
		parent[root] = nullptr;
		//cout << root->val << endl;
		que.push(root);
		while (!que.empty())//层次遍历二叉树，记录每个节点的父节点
		{
			TreeNode*current = que.front();
			que.pop();
			cout << current->val << " ";
			
			if (current->left != nullptr)
			{
				que.push(current->left);
				parent[current->left] = current;
			}
			if (current->right != nullptr)
			{
				que.push(current->right);
				parent[current->right] = current;
			}
		}
		if (p==root||q==root)
		{
			return root;
		}
		else if (parent.find(p) == parent.end() || parent.find(q) == parent.end())
		{
			return nullptr;
		}
		else
		{
			TreeNode*a = p;
			TreeNode*b = q;
			if (a == b)return a;
			while (a != root&&b != root)
			{
				if (a == nullptr)a = q;
				else a = parent[a];
				if (b == nullptr)b = p;
				else b = parent[b];
				if (a == b)return a;
				if (a == root)
				{
					//a = q;
					//map<TreeNode*, TreeNode*>::iterator it = parent.find(a);
					//it->second = q;
					a = nullptr;
					//parent[a] = q;
				}
				if (b == root)
				{
					//b = p;
					/*map<TreeNode*, TreeNode*>::iterator it = parent.find(b);
					it->second = p;*/
					b = nullptr;
					//parent[b] = p;
				}
			}
		}
	}
	return nullptr;
}

//Kth Smallest Element in a BST
int kthSmallest(TreeNode* root, int k) 
{
	stack<TreeNode*>s;
	TreeNode*p = root;
	int i = 0;
	while (true)
	{
		if (p != nullptr)
		{
			s.push(p);
			p = p->left;
		}
		if (s.size() != 0&&p == nullptr)//p已遍历到中序下第一个节点
		{
			i++;
			cout << s.top()->val << " ";
			if (i == k)return s.top()->val;
			p = s.top()->right;
			s.pop();
		}
		if (s.size() == 0&&p==nullptr)break;
	}
}

//Count Complete Tree Nodes
int countNodes(TreeNode* root)//递归，效率低
{
	if (root != nullptr)
	{
		int l = countNodes(root->left);
		int r = countNodes(root->right);
		return l + r + 1;
	}
	return 0;
}


//Count Complete Tree Nodes
int countNodes2(TreeNode* root)//迭代 
{
	if (root != nullptr)
	{
		int i = 0;
		queue<TreeNode*>que;
		que.push(root);
		while (!que.empty())
		{
			i++;
			TreeNode*p = que.front();
			que.pop();
			cout << p->val << " ";
			if (p->left != nullptr)que.push(p->left);
			if (p->right != nullptr)que.push(p->right);
		}
		return i;
	}
	return 0;
}

//Count Complete Tree Nodes
int countNodes3(TreeNode* root)
{
	if (root != nullptr)
	{
		TreeNode*l = root->left;
		TreeNode*r = root->right;

		int nl = 0;
		int nr = 0;

		while (l)
		{
			l = l->left;
			nl++;
		}
		while (r)
		{
			r = r->right;
			nr++;
		}
		if (nl == nr)return (1<<(nl+1)) - 1;//1<<(nl+1)等价于pow(2,nl+1)
		return 1 + countNodes3(root->left) + countNodes3(root->right);
	}
	return 0;
}

//Count Complete Tree Nodes
int countNodes4(TreeNode* root)//测试不完全
{
	if (root != nullptr)
	{
		TreeNode*p = root;
		int level = 0;
		while (p != nullptr)
		{
			p = p->left;
			level++;
		}
		queue<TreeNode*>que;
		que.push(root);
		int i = 1;
		if (i == level)return 1;
		if (i == level - 2)
		{
			TreeNode*q = que.front();
			que.pop();
			que.push(q->left);
			que.push(q->right);
			
			int sz = que.size();
			int last = 0;
			for (int m = 0; m < sz; m++)
			{
				TreeNode*q = que.front();
				que.pop();
				if (q->left != nullptr)last++;
				else break;
				if (q->right != nullptr)last++;
				else break;
			}
			return 3 + last;
		}
		while (i+2<level)
		{
			for (int j = 0; j < pow(2, i - 1); j++)
			{
				TreeNode*q = que.front();
				que.pop();
				que.push(q->left->left);
				que.push(q->left->right);
				que.push(q->right->left);
				que.push(q->right->right);
			}
			i += 2;
		}

		if (i+2 == level)
		{
			for (int k = 0; k < pow(2, i - 1); k++)
			{
				TreeNode*q = que.front();
				que.pop();
				que.push(q->left);
				que.push(q->right);
			}
		}
		int size = que.size();
		int lastlevel = 0;
		for (int l = 0; l < size; l++)
		{
			TreeNode*q = que.front();
			que.pop();
			if (q->left != nullptr)lastlevel++;
			else break;
			if (q->right != nullptr)lastlevel++;
			else break;
		}
		return lastlevel +(int)pow(2, level - 1) - 1;
	}
	return 0;
}

int maxDepth(TreeNode* root)
{
	return height(root);
}

int minDepth(TreeNode* root) 
{
	if (root != nullptr)
	{
		int l = minDepth(root->left);
		int r = minDepth(root->right);
		return 1 + (l > r ? r : l);
	}
	return 0;
}

int MinDepth(TreeNode*root)
{
	if (root != nullptr)
	{
		if (root->left != nullptr&&root->right == nullptr)
		{
			return MinDepth(root->left) + 1;
		}
		else if (root->left == nullptr&&root->right != nullptr)
		{
			return MinDepth(root->right) + 1;
		}
		else if (root->left == nullptr&&root->right == nullptr)
			return 1;
		else
		{
			int l = MinDepth(root->left);
			int r = MinDepth(root->right);
			return (l < r ? l : r)+1;
		}
	}
	return 0;
}

vector<vector<int>> levelOrder(TreeNode* root) 
{
	vector<vector<int>>vec;
	if (root != nullptr)
	{
		queue<TreeNode*>que;
		que.push(root);
		int size = 1;
		vector<int>temp;
		while (!que.empty())
		{
			if (size == 0)
			{
				size = que.size();
				vec.push_back(temp);
				temp.clear();
			}
			TreeNode*p = que.front();
			if (size >= 0)
			{
				temp.push_back(p->val);
				size--;
			}
			que.pop();
			if (p->left != nullptr)
			{
				que.push(p->left);
			}
			if (p->right != nullptr)
			{
				que.push(p->right);
			}
		}
		vec.push_back(temp);
	}
	return vec;
}


vector<vector<int>> levelOrderBottom(TreeNode* root) 
{
	vector<vector<int>>vec(levelOrder(root));
	return vector<vector<int>>(vec.rbegin(), vec.rend());
}
vector<vector<int>> zigzagLevelOrder(TreeNode* root)
{
	vector<vector<int>>vec;
	if (root != nullptr)
	{
		queue<TreeNode*>que;
		que.push(root);
		int size = 1;
		bool flag = true;
		vector<int>temp;
		while (!que.empty())
		{
			if (size == 0)
			{
				size = que.size();
				if (flag)
				{
					vec.push_back(temp);
					flag = false;
				}
				else
				{
					vec.push_back(vector<int>(temp.rbegin(), temp.rend()));
					flag = true;
				}
				temp.clear();
			}
			TreeNode*p = que.front();
			if (size >= 0)
			{
				temp.push_back(p->val);
				size--;
			}
			que.pop();
			if (p->left != nullptr)
			{
				que.push(p->left);
			}
			if (p->right != nullptr)
			{
				que.push(p->right);
			}
		}
		if (flag)
		{
			vec.push_back(temp);
			flag = false;
		}
		else
		{
			vec.push_back(vector<int>( temp.rbegin(), temp.rend()));
			flag = true;
		}
	}
	return vec;
}

bool hasPathSum(TreeNode* root, int sum)
{
	if (root != nullptr)
	{
		if (root->val == sum&&root->left == nullptr&&root->right==nullptr)return true;
		bool l = hasPathSum(root->left, sum - root->val);
		bool r= hasPathSum(root->right, sum - root->val);
		return l || r;
	}
	return false;
}

//Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum. 
vector<vector<int>> pathSum(TreeNode* root, int sum)
{
	//if (hasPathSum(root, sum))return vector<vector<int>>();
	vector<vector<int>>vec;
	if (root != nullptr)
	{
		if (root->val == sum&&root->left == nullptr&&root->right == nullptr)
			return vector<vector<int>>(1, vector<int>(1, root->val));
		vector<vector<int>>l = pathSum(root->left, sum - root->val);
		vector<vector<int>>r = pathSum(root->right, sum - root->val);
		for (vector<vector<int>>::iterator it = l.begin(); it != l.end(); it++)
		{
			(*it).insert((*it).begin(), root->val);
		}
		for (vector<vector<int>>::iterator it = r.begin(); it != r.end(); it++)
		{
			(*it).insert((*it).begin(), root->val);
		}

		copy(l.begin(), l.end(), inserter(vec,vec.end()));
		copy(r.begin(), r.end(), inserter(vec, vec.end()));
	}
	return vec;
}
vector<int> rightSideView(TreeNode* root)
{
	vector < int > vec;
	if (root != nullptr)
	{
		queue<TreeNode*>que;
		que.push(root);
		int size = 1;
		vector<int>temp;
		while (!que.empty())
		{
			if (size == 0)
			{
				size = que.size();
				vec.push_back(temp.back());
				temp.clear();
			}
			TreeNode*p = que.front();
			if (size >= 0)
			{
				temp.push_back(p->val);
				size--;
			}
			que.pop();
			if (p->left != nullptr)
			{
				que.push(p->left);
			}
			if (p->right != nullptr)
			{
				que.push(p->right);
			}
		}
		vec.push_back(temp.back());
	}
	return vec;
}

TreeNode* sortedArrayToBST(vector<int>& nums)
{
	TreeNode*res = nullptr;
	if (!nums.empty())
	{
		res = new TreeNode(nums[nums.size() / 2]);
		vector<int>::iterator it = nums.begin() + nums.size() / 2;

		vector<int>l(nums.begin(), it);
		vector<int>r(++it, nums.end());

		res->left = sortedArrayToBST(l);
		res->right = sortedArrayToBST(r);
	}
	return res;
}


//Flatten Binary Tree to Linked List 
void flatten(TreeNode* root) 
{
	if (root != nullptr)
	{
		TreeNode*l = root->left;
		TreeNode*r = root->right;
		flatten(l);
		flatten(r);

		root->left = nullptr;
		if (l!=nullptr)	root->right = l;
		else root->right = r;

		TreeNode*ll = l;

		while (ll&&ll->right)
		{
			ll = ll->right;
		}
		if (l != nullptr)
		{
			ll->right = r;
		}
	}
}

vector<vector<int>>rootToLeaf(TreeNode*root)
{
	vector<vector<int>>vec;
	if (root != nullptr)
	{
		if (root->left == nullptr&&root->right == nullptr)
			return vector<vector<int>>(1, vector<int>(1,root->val));

		vector<vector<int>>l = rootToLeaf(root->left);
		vector<vector<int>>r = rootToLeaf(root->right);

		for (vector<vector<int>>::iterator it = l.begin(); it != l.end(); it++)
		{
			(*it).insert((*it).begin(), root->val);
		}

		for (vector<vector<int>>::iterator it = r.begin(); it != r.end(); it++)
		{
			(*it).insert((*it).begin(), root->val);
		}

		copy(l.begin(), l.end(), inserter(vec, vec.end()));
		copy(r.begin(), r.end(), inserter(vec, vec.end()));
	}
	return vec;
}

//Sum Root to Leaf Numbers 
//https://leetcode.com/problems/sum-root-to-leaf-numbers/
int sumNumbers(TreeNode* root)
{
	int res = 0;
	if (root != nullptr)
	{
		vector<vector<int>>vec = rootToLeaf(root);
		for (vector<vector<int>>::iterator it = vec.begin(); it != vec.end(); it++)
		{
			int temp = 0;
			for (vector<int>::iterator iter = (*it).begin(); iter != (*it).end(); iter++)
			{
				temp = temp * 10 + *iter;
			}
			res = res + temp;
		}
	}
	return res;
}

//Unique Binary Search Trees
//Given n, how many structurally unique BST's (binary search trees) that store values 1...n?
//https://leetcode.com/problems/unique-binary-search-trees/
int numTrees(int n) 
{
	int res = 0;
	if (n > 0)
	{
		vector<int>vec(n+1,0);
		vec[0] = vec[1] = 1;
		for (vector<int>::size_type i = 2; i <= n; i++)
			for (vector<int>::size_type j = 1; j <= i; j++)
				vec[i] += vec[j - 1] * vec[i - j];
		res = vec[n];
	}
	return res;
}

class LevelComp{//函数对象，层次遍历
public:
	//Comp():tree1(nullptr),tree2(nullptr){}
	bool operator()(TreeNode*tree1, TreeNode*tree2)
	{
		if (tree1 == nullptr)return true;
		else if (tree1 != nullptr&&tree2 == nullptr)return false;
		else
		{
			queue<TreeNode*>s1;
			queue<TreeNode*>s2;
			s1.push(tree1);
			s2.push(tree2);

			while (!s1.empty() && !s2.empty())
			{
				TreeNode*p1 = s1.front();
				TreeNode*p2 = s2.front();
				s1.pop();
				s2.pop();
				if (p1->val == p2->val)
				{
					if (p1->left != nullptr)s1.push(p1->left);
					if (p1->right != nullptr)s1.push(p1->right);
					if (p2->left != nullptr)s2.push(p2->left);
					if (p2->right != nullptr)s2.push(p2->right);
				}
				else if (p1->val < p2->val)return true;
				else return false;
			}
			if (s1.empty())return true;
			else return false;
		}
	}
};

bool levelComp(TreeNode*tree1, TreeNode*tree2)//if(tree1<=tree2)return true,层次遍历
{
	if (tree1 == nullptr)return true;
	else if (tree1 != nullptr&&tree2 == nullptr)return false;
	else
	{
		queue<TreeNode*>s1;
		queue<TreeNode*>s2;
		s1.push(tree1);
		s2.push(tree2);

		while (!s1.empty() && !s2.empty())
		{
			TreeNode*p1 = s1.front();
			TreeNode*p2 = s2.front();
			s1.pop();
			s2.pop();
			if ( p1->val == p2->val)
			{
				if (p1->left != nullptr)s1.push(p1->left);
				if (p1->right != nullptr)s1.push(p1->right);
				if (p2->left != nullptr)s2.push(p2->left);
				if (p2->right != nullptr)s2.push(p2->right);
			}
			else if (p1->val < p2->val)return true;
			else return false;
		}
		if (s1.empty())return true;
		else return false;
	}
}

vector<int> preToArray(TreeNode*root)//前序遍历输出到一维数组
{
	vector<int>temp;
	if (root != NULL)
	{
		temp.push_back(root->val);
		vector<int>l = preToArray(root->left);
		vector<int>r = preToArray(root->right);
		copy(l.begin(), l.end(), inserter(temp, temp.end()));
		copy(r.begin(), r.end(), inserter(temp, temp.end()));
	}
	return temp;
}
bool preComp(TreeNode*tree1, TreeNode*tree2)//if(tree1<=tree2)return true,前序遍历
{
	if (tree1 == nullptr)return true;
	else if (tree1 != nullptr&&tree2 == nullptr)return false;
	else
	{
		if (tree1->val < tree2->val)return true;
		else if (tree1->val > tree2->val)return false;
		else
		{
			vector<int>vec1 = preToArray(tree1);
			vector<int>vec2 = preToArray(tree2);
			vector<int>::size_type i = 1;
			for (; i < vec1.size() && i < vec2.size(); i++)
			{
				if (vec1[i] == vec2[i])continue;
				else if(vec1[i] < vec2[i])return true;
				else return false;
			}
			if (i == vec1.size())return true;
			else return false;
		}
	}
}

class PreComp{
public:
	bool operator()(TreeNode*tree1, TreeNode*tree2)
	{
		if (tree1 == nullptr)return true;
		else if (tree1 != nullptr&&tree2 == nullptr)return false;
		else
		{
			if (tree1->val < tree2->val)return true;
			else if (tree1->val > tree2->val)return false;
			else
			{
				vector<int>vec1 = preToArray(tree1);
				vector<int>vec2 = preToArray(tree2);
				vector<int>::size_type i = 1;
				for (; i < vec1.size() && i < vec2.size(); i++)
				{
					if (vec1[i] == vec2[i])continue;
					else if (vec1[i] < vec2[i])return true;
					else return false;
				}
				if (i == vec1.size())return true;
				else return false;
			}
		}
	}
};
//Unique Binary Search Trees II
//Given n, generate all structurally unique BST's (binary search trees) that store values 1...n.
vector<TreeNode*> generateTrees(int n)
{
	if (n <= 0)return vector<TreeNode*>(1, nullptr);
	vector<TreeNode*>result;
	if (n == 1)result = vector<TreeNode*>(1, new TreeNode(1));
	else
	{
		vector<TreeNode*>pre = generateTrees(n - 1);
		for (vector<TreeNode*>::size_type it = 0; it != pre.size(); it++)
		{
			TreeNode*p = new TreeNode(n);
			p->left = pre[it];//添加在根节点
			result.emplace_back(p);
		}

		pre = generateTrees(n - 1);
		for (vector<TreeNode*>::size_type it = 0; it != pre.size(); it++)
		{
			TreeNode*q = pre[it];
			TreeNode*front = pre[it];
			int cnt = 0;//根节点为pre[it]的二叉搜索树的右子树
			while (q != nullptr)
			{
				cnt++;
				front = q;
				q = q->right;
				
				TreeNode*copy = copyTree(pre[it]);
				TreeNode*largest = new TreeNode(n);
				TreeNode*_q = copy;
				TreeNode*_front = _q;
				for (int i = 0; i < cnt; i++)
				{
					_front = _q;
					_q = _q->right;
				}
				_front->right = largest;
				largest->left = _q;
				result.emplace_back(copy);
			}
		}
	}
	sort(result.begin(), result.end(), PreComp());
	return result;
}

//https://leetcode.com/problems/validate-binary-search-tree/
//Given a binary tree, determine if it is a valid binary search tree (BST). 
bool isValidBST(TreeNode* root)
{
	if (root == nullptr || (root->left == nullptr&&root->right == nullptr))return true;
	bool l = isValidBST(root->left);
	bool r = isValidBST(root->right);
	if (root->left == nullptr&&root->right != nullptr)
	{
		if (r&&root->val < root->right->val)
		{
			TreeNode*p = root->right;
			while (p != nullptr)
			{
				if (p->val <= root->val)return false;
				p = p->left;
			}
			return true;
		}
		else return false;
	}
	else if (root->left != nullptr&&root->right == nullptr)
	{
		if (l&&root->left->val < root->val)
		{
			TreeNode*p = root->left;
			while (p != nullptr)
			{
				if (p->val >= root->val)return false;
				p = p->right;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (l&&r&&root->left->val < root->val&&root->val < root->right->val)
		{
			TreeNode*p = root->left;
			while (p != nullptr)
			{
				if (p->val >= root->val)return false;
				p = p->right;
			}
			p = root->right;
			while (p != nullptr)
			{
				if (p->val <= root->val)return false;
				p = p->left;
			}
			return true;
		}
		else return false;
	}
}


//Binary Tree Maximum Path Sum 
int maxPathSum(TreeNode* root) 
{
	return 0;
}
//Given an array of integers, find out whether there are two distinct indices i and j in the array such that the difference between nums[i] and nums[j] is at most t and the difference between i and j is at most k. 
//bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) 
//{

//}
#endif // !binarytree_h
