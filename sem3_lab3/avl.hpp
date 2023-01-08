#ifndef AVL_HPP
#define AVL_HPP
#include <string>
#include <typeinfo> 
#include "array_sequence.hpp"

template<typename Type>
class AVL {
protected:
	struct node // struct for storage tree's knot
	{
		Type key;
		unsigned char height;
		node* left;
		node* right;
		node(Type k) { 
			key = k; 
			left = right = 0; 
			height = 1; 
		}
	};
	node* root;

	unsigned char height(node* p)
	{
		if (p) {
			return p->height;
		}
		else {
			return 0;
		}
	}

	int bfactor(node* p) //balance factor
	{
		return height(p->right) - height(p->left);
	}

	void fixheight(node* p) // return fix hieght subtree
	{
		unsigned char hl = height(p->left);
		unsigned char hr = height(p->right);
		p->height = (hl > hr ? hl : hr) + 1;
	}

	node* rotateright(node* p) {
		node* q = p->left;
		p->left = q->right;
		q->right = p;
		fixheight(p);
		fixheight(q);
		return q;
	}   // right turn around p

	node* rotateleft(node* q) // left turn around p
	{
		node* p = q->right;
		q->right = p->left;
		p->left = q;
		fixheight(q);
		fixheight(p);
		return p;
	}

	node* balance(node* p) // balance p
	{
		fixheight(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->right) < 0)
				p->right = rotateright(p->right);
			return rotateleft(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->left) > 0)
				p->left = rotateleft(p->left);
			return rotateright(p);
		}
		return p; // if its balanced
	}

	node* insert(node* p, Type k) // insert k in tree with root in p
	{
		if (!p) return new node(k);
		if (k < p->key)
			p->left = insert(p->left, k);
		else
			p->right = insert(p->right, k);
		return balance(p);
	}

	node* findmin(node* p) // find min
	{
		return p->left ? findmin(p->left) : p;
	}

	node* removemin(node* p) // remove min from tree with root in p
	{
		if (p->left == 0)
			return p->right;
		p->left = removemin(p->left);
		return balance(p);
	}

	node* remove(node* p, Type k) // remove k from tree with root in p
	{
		if (!p) return 0;
		if (k < p->key)
			p->left = remove(p->left, k);
		else if (k > p->key)
			p->right = remove(p->right, k);
		else //  k == p->key 
		{
			node* q = p->left;
			node* r = p->right;
			delete p;
			if (!r) return q;
			node* min = findmin(r);
			min->right = removemin(r);
			min->left = q;
			return balance(min);
		}
		return balance(p);
	}



	node* nodefind(node* p, Type k) {
		if (p == nullptr) {
			return nullptr;
		}
		if (p->key == k) {
			return p;
		}
		if (k < p->key) {
			return nodefind(p->left, k);
		}
		else {
			return nodefind(p->right, k);
		}
	}

	int nodeget(Type k, node* p, Type &ans) {
		if (p == nullptr) {
			return 1;
		}
		if (p->key == k) {
			ans = p->key;
			return 0;
		}
		nodeget(k, p->left, ans);
		nodeget(k, p->right, ans);
		return 0;
	}

	int nodegetelements(ArraySequence<Type>* vec, node* p) {
		if (p == nullptr) {
			return 0;
		}
		nodegetelements(vec, p->left);
		vec->Append(p->key);
		nodegetelements(vec, p->right);
		return 0;
	}

public:
	AVL() {
		root = nullptr;
	}

	int add(Type k) {
		this->root = insert(this->root, k);
		return 0;
	}

	int delet(Type k) {
		this->root = remove(this->root, k);
		return 0;
	}

	bool find(Type k) {
		if (nodefind(this->root, k) == nullptr) {
			return false;
		}
		else {
			return true;
		}
	}


	int get(Type k, Type &ret) {
		if (find(k)) {
			Type ans;
			nodeget(k, this->root, ans);
			ret = ans;
			return 0;
		}
		else {
			return 1;
		}
	}

	int bin_search() {
		return 0;
	}
	ArraySequence<Type> getelements() {
		ArraySequence<Type> vec;
		nodegetelements(&vec, this->root);
		return vec;
	}
};

#endif