#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

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
	void preOrder(node* root);//PreOrder Traversal and print
	void inOrder(node* root);	//InOrder Traversal and print
	void postOrder(node* root);//PostOder Traversal and print
	void insert(int loc, unsigned long data, int left, int right);//used to add nodes to array

};

bTree::bTree(int nodes){
	root =NULL;
	size = nodes;
	array = new node[size];//create array big enough to hold all the nodes
}
void bTree::preOrder(node* root){	
	cout << root->data << " ";
    if (root->left != NULL)
    preOrder(root->left);
    if (root->right != NULL)
    preOrder(root->right);
}
void bTree::inOrder(node* root){
	if (root->left != NULL)
        inOrder(root->left);
    cout << root->data << " ";
    if (root->right != NULL)
        inOrder(root->right);

}
void bTree::postOrder(node* root){
	if (root->left != NULL)
    postOrder(root->left);
    if (root->right != NULL)
    postOrder(root->right);
    cout << root->data << " ";

}
void bTree::insert(int loc, unsigned long data,int left,int right){
	node temp; //create a node that will be put in the tree
	if (left != -1)
	temp.left = &array[left];//set pointer to left child
	else temp.left = NULL;
	if (right != -1)
	temp.right = &array[right];//set pointer to right child
	else temp.right = NULL;
	temp.data = data;//insert data
	array[loc] = temp;//insert temp into array
	if (loc == 0) root = &array[0];

	

}
int main(){

	int size;
	std::cin >> size;

	bTree* tree = new bTree(size);//create tree object

	for (int i = 0; i < size; i++){//take in all inputs
		unsigned long data;
		int left;
		int right;
		cin >> data >> left >> right;
		tree->insert(i, data, left, right);
	}
	tree->preOrder(tree->root);
	cout << "\n";
	tree->inOrder(tree->root);
	cout << "\n";
	tree->postOrder(tree->root);
	cout << "\n";


	return 0;
}