
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
	void levelOrder(node* root);
	void insert(int loc, unsigned long data, int left, int right);//used to add nodes to array

};

bTree::bTree(int nodes){
	root =NULL;
	size = nodes;
	array = new node[size];//create array big enough to hold all the nodes
}

void bTree::levelOrder(node* root){
	node * t = root;
    queue<node*> tree;
    while (t != NULL){
        cout << t->data << " ";
        if (t->left != NULL)
        tree.push(t->left);
        //cout << "push left" << t->left << "\n";
        if (t->right != NULL)
        tree.push(t->right);
        //cout << "pushright" << t->right << "\n";
        if (tree.empty())t = NULL;
        else{
        t = tree.front();
        tree.pop();
        }
    }
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

	bTree* tree = new bTree(size);

	for (int i = 0; i < size; i++){	//for loop to take in inputs of all nodes
		unsigned long data;
		int left;
		int right;
		cin >> data >> left >> right;
		tree->insert(i, data, left, right);
	}
	
	tree->levelOrder(tree->root);


	return 0;
}
