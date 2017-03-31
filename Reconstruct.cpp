#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <queue>

using namespace std;

struct node {
	
	node* left;		//pointer to left child
	node* right;	//pointer to right child
	unsigned long data;//data contained in node

};
class bTree {
public:
	node* array;	//array to hold nodes
	node* root;		//pointer to root of tree
	int size;		//size of array

	bTree(int size);//constructor
	node* reconstruct(unsigned long * inOrder, unsigned long* postOrder, int size);
	void levelOrder(node* root);

};

bTree::bTree(int nodes){
	root =NULL;
	size = nodes;
	array = new node[size];//create array big enough to hold all the nodes
}


node* bTree::reconstruct(unsigned long* inOrder, unsigned long* postOrder, int size){
	int pos = -1;
	unsigned long data = postOrder[size-1];//grabs last node in the subtree
	unsigned long * newIn;
	unsigned long * newPost;

	node* root = new node;//sets root of tree or subtree
	root->data = data;//creates the node
	
	for (int i = 0; i < size; i++){//find in inOrder
		if (inOrder[i] == root->data){
			pos = i;
			break;
		}
	}
	if (pos > 0){
	newIn = new unsigned long[pos];
	newPost = new unsigned long[pos];
	for (int i = 0; i < pos; i++){//sets up new arrays for left subtree
		newIn[i] = inOrder[i];
		newPost[i] = postOrder[i];
	}

	}
	
	if (pos > 0){//means that there is actually a left child
		root->left = reconstruct(newIn,newPost, pos);
	}
	
	
	if (pos < size-1 && pos >= 0){
	newIn = new unsigned long[size-pos-1];
	newPost = new unsigned long[size-pos-1];
	
	for (int i = 0; i < size - pos - 1; i ++){//sets up new arrays for right subtree
		newPost[i] = postOrder[pos + i];
		newIn[i] = inOrder[pos + i + 1];
		
	}
	
	}
	if (pos < size-1 && pos >= 0){//makes sure there is at least one node to the right
		root->right = reconstruct(newIn,newPost, size-pos-1);
	}

	return root;
}
void bTree::levelOrder(node* root){//taken from last problem's solution
	node * t = root;
    queue<node*> tree;
    while (t != NULL){
        cout << t->data << " ";
        if (t->left != NULL)
        tree.push(t->left);
        if (t->right != NULL)
        tree.push(t->right);
        if (tree.empty())t = NULL;
        else{
        t = tree.front();
        tree.pop();
        }
    }
}

int main(){

	int size;//size of tree
	std::cin >> size;

	bTree* tree = new bTree(size);

	unsigned long *postOrder = new unsigned long[size];

	for (int i = 0; i < size; i++){//take in postOrder Traversal
		cin >> postOrder[i];
	}
	
	unsigned long *inOrder = new unsigned long[size];

	for (int i = 0; i < size; i++){//take in inOrder Traversal
		cin >> inOrder[i];
	}

	tree->root = tree->reconstruct(inOrder,postOrder, size);//Reconstructs in one call
	tree->levelOrder(tree->root);//prints out level order Traversal
	cout << "\n";

	return 0;
}