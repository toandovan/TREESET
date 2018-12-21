/* Copyright (C) 2018
* Course: CO2003
* Author: Rang Nguyen
* Ho Chi Minh City University of Technology
*/

#include "TreeSet.h"

TreeSet::TreeSet()
{
	root = NULL;
	count = 0;
}

TreeSet::~TreeSet()
{
	clear();
}

void TreeSet::clearRec(AVLNode* root) {
	if (root != NULL) {
		clearRec(root->left);
		clearRec(root->right);
		delete root;
	}
}

void TreeSet::clear() {
	clearRec(root);
	root = NULL;
	count = 0;
}

int height(AVLNode * node)
{
	if (node == NULL) return 0;
	return node->balance;
}

int max(int x, int y)
{
	if (x > y) return x;
	else
		return y;
}

AVLNode * rightRotate(AVLNode *&root )
{
	AVLNode * temp = root->left;
	AVLNode * temp1 = temp->right;
	temp->right = root;
	root->left = temp1;
	root->balance = max(height(root->left), height(root->right)) + 1;
	temp->balance = max(height(temp->left), height(temp->right)) + 1;
	return temp;
}

AVLNode * leftRotate(AVLNode *&root)
{
	AVLNode * temp = root->right;
	AVLNode * temp1 = temp->left;
	temp->left = root;
	root->right = temp1;
	root->balance = max(height(root->left), height(root->right)) + 1;
	temp->balance = max(height(temp->left), height(temp->right)) + 1;
	return temp;
}

int Balance(AVLNode * node)
{
	if (node == NULL) return 0;
	int balancefactor = height(node->left) - height(node->right);
	return balancefactor;
}

AVLNode* insert(AVLNode* node, int data)
{
	if (node == NULL)
		return (new AVLNode(data,1));

	if (data < node->key)
		node->left = insert(node->left, data);
	else if (data > node->key)
		node->right = insert(node->right, data);
	else 
		return node;

	node->balance = max(height(node->left),
		height(node->right))+1;

	int balancefactor = Balance(node);

	if (balancefactor > 1)
	{
		if (data < node->left->key)
		{
			return rightRotate(node);
		}
		if (data > node->left->key)
		{
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}
	}
	if (balancefactor < -1)
	{
		if (data > node->right->key)
		{
			return leftRotate(node);
		}
		if (data < node->right->key)
		{
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}
	}
	return node;
}

AVLNode* del(AVLNode *&root, int val)
{
	if (root == NULL)
		return root;

	if (val < root->key)
		root->left = del(root->left, val);

	else if (val > root->key)
		root->right = del(root->right, val);

	else
	{
		if (root->left == NULL && root->right == NULL)
		{
			root = NULL;
		}
		else if (root->left == NULL && root->right != NULL)
		{
			root = root->right;
		}
		else if (root->left != NULL && root->right == NULL)
		{
			root = root->left;
		}
		else if(root->left != NULL && root->right != NULL)
		{
			AVLNode* temp = root->right;
			while (temp->left != NULL)
			{
				temp = temp->left;
			}
			root->key = temp->key;
			root->right = del(root->right, temp->key);
		}
	}

	if (root == NULL)
		return root;

	root->balance = 1 + max(height(root->left),
		height(root->right));

	int balancefactor = Balance(root);
	if (balancefactor > 1)
	{
		if(Balance(root->left) >= 0)
			return rightRotate(root);
		if (Balance(root->left) < 0)
		{
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
	}
	
	if (balancefactor < -1 )
	{
		if(Balance(root->right) <= 0)
			return leftRotate(root);
		if (Balance(root->right) > 0)
		{
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
	}
		
	return root;
}

int TreeSet::add(int val) {
	// TODO
	//call insert AVL
	if (val < 0) return 0;
	if (contains(val) == 1) return 0;
	root=insert(root, val);
	count = count + 1;
	return 1;
}

bool TreeSet::contains(int val) {
	// TODO
	//contains
	if (val < 0) return 0;
	AVLNode * Temp = root;
	while (Temp != NULL)
	{
		if (Temp->key == val)
			return 1;
		if (Temp->key < val)
			Temp = Temp->right;
		else if (Temp->key > val)
			Temp = Temp->left;
	}
	return 0;
}

void  TreeSet::coppy(AVLNode * &root, AVLNode * setroot)
{
	if (setroot != NULL)
	{
		coppy(root, setroot->left);
		add(setroot->key);
		coppy(root, setroot->right);
	}
}

void TreeSet::copy(const TreeSet& set) {
	// TODO
	clear();
	coppy(root, set.root);
}

int TreeSet::first() {
	if (root == NULL) {
		throw "NoSuchElementException";
	}
	// TODO
	AVLNode * Temp = root;
	while (Temp->left != NULL)
	{
		Temp = Temp->left;
	}
	return Temp->key;
}

int TreeSet::last() {
	if (root == NULL) {
		throw "NoSuchElementException";
	}

	// TODO
	AVLNode *Temp = root;
	while (Temp->right != NULL)
	{
		Temp = Temp->right;
	}
	return Temp->key;
}

AVLNode *high(int val, AVLNode * root, int &hi)
{
	if (root == NULL) return root;
	if (root->key < val)
	{
		high(val, root->right, hi);
		if (root->key > hi&&root->key < val)
			hi = root->key;
	}
	else
	{
		high(val, root->left, hi);
		if (root->key > hi&&root->key < val)
			hi = root->key;
	}
	return root;


}

AVLNode  * low(int val, AVLNode * root, int &lo)
{
	if (root == NULL) return root;
	if (root->key > val)
	{
		low(val, root->left, lo);
		if (root->key<lo&&root->key>val)
			lo = root->key;
	}
	else
	{
		low(val, root->right, lo);
		if (root->key<lo&&root->key>val)
			lo = root->key;
	}
	return root;
}

int TreeSet::higher(int val) {
	// TODO
	int lo = last();
	if (val >= lo) return -1;
	low(val, root, lo);
	return lo;
}

int TreeSet::lower(int val) {
	// TODO
	int hi = first();
	if (hi >= val) return -1;
	high(val, root, hi);
	return hi;
}

int TreeSet::remove(int val) {
	// TODO	
	if (contains(val) == 0) return 0;
	root = del(root, val);
	count = count - 1;
	return 1;
}

void TreeSet::subs(AVLNode *root, TreeSet *&sub, int fromVal, int toVal)
{
	if (root != NULL)
	{
		subs(root->left, sub, fromVal, toVal);
		if (root->key >= fromVal && root->key < toVal)
		{
			sub->add(root->key);
		}
		subs(root->right, sub, fromVal, toVal);
	}
}

TreeSet* TreeSet::subSet(int fromVal, int toVal) {
	// TODO
	TreeSet *sub = new TreeSet();
	subs(root, sub, fromVal, toVal);
	return sub;
}

int TreeSet::size() {
	// TODO
	return count;
}