#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<sstream>
using namespace std;

class node {
private:
	int value;
	int key;
	node *left_child;
	node *right_child;
	node *parent;
public:
	node(int val) {
		value = val;
	}
	int get_key() {
		if (this == NULL) {
			return 0; 
		}
		return value;
	}
friend class tree;
};

class tree {
private:
	node *root;
public:
	tree() {
		root = NULL;
	};
	node* get_root() {
		return root;
	}
	node* search(int value) {
		node *root = this->root;
		if (root == NULL) {
			cout << "It's an empty tree! " << endl;
			return 0;
		}
		while(root != NULL && root->value != value) {
			if (root->value > value) {
				root = root->left_child;
			}
			else
				root = root->right_child;
		}
		return root;
	}
	node* get_max(node* x) {
		while (x->right_child != NULL) {
			x = x->right_child;
		}
		return x;
	}
	node* get_min(node* x) {
		while (x->left_child != NULL) {
			x = x->left_child;
		}
		return x;
	}
	node* successor(node* x) {
		if (x->right_child != NULL) {
			return (get_min(x->right_child));
		}
		else {
			node* y = x->parent;
			while (y != NULL && x == y->right_child) {
				x = y;
				y = y->parent;
			}
			return y;
		}
	}
	node* predecessor(node* x) {
		if (x->left_child != NULL) {
			return (get_max(x->left_child));
		}
		else{
			node* y = x->parent;
			while (y != NULL && x == y->left_child){
				x = y;
				y = y->parent;
			}
			if (y != NULL) {
				return y;
			}
		}
	}
	void insert(int value) {
		node *x;
		node *y = NULL;
		node *insert = new node(value); //要插入的
		x = this->root; //檢查樹是否為空
		if (x == NULL) {
			this -> root = insert;
			return;
		}
		while(x != NULL) {
			y = x;
			if (x-> value < insert->value) {
				x = x->right_child;
			}
			else
				x = x->left_child;
		}
		insert->parent = y;
		if (y->value > insert->value) {
			y->left_child = insert;
		}
		if (y->value < insert->value) {
			y->right_child = insert;
		}
	};
	void deletion(int value) {
		node* del = search(value);
		node* a; //node to be deleted
		node* b; //a's child
		if (del == NULL) {
			cout << endl << "Element doesn't exist!" << endl;
			return;
		}
		if (del->left_child == NULL || del->right_child == NULL) {
			a = del;
		}//case a
		else {
			a = successor(del); // 將a設成del的Successor
		}
		if (a->left_child != NULL) {
			b = a->left_child;  //將b設成a的child
		}
		else {
			b = a->right_child;
		}
		if (b != NULL) {   // 在a被刪除之前,將b接回樹
			b->parent = a->parent;
		}
		if (a->parent == NULL) { // 接著再把要被釋放記憶體的node之"parent"指向新的child
			this->root = b;    // 若刪除的是原先的root, 就把b當成新的root 
		}
		else if (a == a->parent->left_child) {
			a->parent->left_child = b;
		}
		else{
			a->parent->right_child = b;
		}
		if (a != del) {                 // 若y是delete_node的替身, 最後要再將y的資料
			del->value = a->value;          // 放回delete_node的記憶體位置, 並將y的記憶體位置釋放 
		}
		delete a;
	};
	void inorder(node* x) {
		if (x != NULL) {
			inorder(x->left_child);
			cout << x->value << " ";
			inorder(x->right_child);
		}
	}
};

int main(void){
	tree t;
	node* n;
	fstream file;
	file.open("bt_input.txt", ios::in);
	if (!file) {
		cout << "err";
		system("pause");
		return 0;
	}
	int node_val;
	string tmp;
	while(!file.eof()){
		getline(file, tmp);
		stringstream ss(tmp);
		ss >> node_val;
		t.insert(node_val);
	}
	cout << "Search element in the tree: ";
	n = t.search(67);
	cout << n->get_key() << endl;
	cout << "---------------------" << endl;
	cout << "Search element doesn't in the tree: ";
	n = t.search(5);
	cout << n->get_key() << endl;
	cout << "---------------------" << endl;
	cout << "The max element: ";
	n = t.get_max(t.get_root());
	cout << n->get_key()<< endl;
	cout << "---------------------" << endl;
	cout << "The min element: ";
	n = t.get_min(t.get_root());
	cout << n->get_key() << endl;
	cout << "---------------------" << endl;
	cout << "The tree after inorder travesal: ";
	t.inorder(t.get_root());
	cout <<endl<< "---------------------" << endl;
	cout << "The tree after insert 3842: ";
	t.insert(3842);
	t.inorder(t.get_root());
	cout<< endl << "---------------------" << endl;
	cout  << "The tree after trying to delete 3333: ";
	t.deletion(3333);
	cout << "---------------------" << endl;
	cout << "The tree after delete 4: " << endl;
	t.deletion(4);
	t.inorder(t.get_root());
	cout << endl << "---------------------" << endl;
	cout << "The successor of root: " << endl;
	n = t.successor(t.get_root());
	cout << n->get_key() << endl;
	cout << "---------------------" << endl;
	cout << "The predecessor of 52: " << endl;
	n = t.predecessor(t.search(52));
	cout << n->get_key() << endl;
	cout << "---------------------" << endl;
}