// Binary Search Tree - Implemenation in C++
// Simple program to create a BST of integers and search an element in it

#include<iostream>
using namespace std;

//Definition of Node for Binary search tree
struct BstNode {
	int data;
	BstNode* left;
	BstNode* right;
};

// Function to create a new Node in heap
BstNode* GetNewNode(int data) {
	BstNode* newNode = new BstNode();
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	return newNode;
}

// To insert data in BST, returns address of root node
BstNode* Insert(BstNode* root,int data) {
	if(root == NULL) { // empty tree
		root = GetNewNode(data);
	}
	// if data to be inserted is lesser, insert in left subtree.
	else if(data <= root->data) {
		root->left = Insert(root->left,data);
	}
	// else, insert in right subtree.
	else {
		root->right = Insert(root->right,data);
	}
	return root;
}

//To search an element in BST, returns true if element is found
bool Search(BstNode* root,int data) {
	if(root == NULL) {
		return false;
	}
	else if(root->data == data) {
		return true;
	}
	else if(data <= root->data) {
		return Search(root->left,data);
	}
	else {
		return Search(root->right,data);
	}
}

void Allpath(BstNode* root, int path[],int pathlen) {
	int i;
	if(root) {
		if(!root->left && !root->right) {
			cout << root->data << " to root: " << root->data << " ";
			for(i=pathlen-1; i>=0; i--) {
				cout << path[i] << " ";
			}
			cout << endl;
		} else {
			path[pathlen] = root->data;
			pathlen++;
			Allpath(root->left, path, pathlen);
			Allpath(root->right, path, pathlen);
		}
	}
}

void Maxpath(BstNode* root, int *path,int pathlen, int *maxpath, int &maxpathlen) {
	if(root) {
		if(!root->left && !root->right) {
			if(pathlen > maxpathlen){
				for(int i=pathlen-1; i>=0; i--) {
					maxpath[i] = path[i];
					maxpathlen = pathlen;
				}
				maxpath[maxpathlen] = root->data;
			}
		} else {
			path[pathlen] = root->data;
			pathlen++;
			Maxpath(root->left, path, pathlen, maxpath, maxpathlen);
			Maxpath(root->right, path, pathlen, maxpath, maxpathlen);
		}
	}
}

int main() {
	BstNode* root = NULL;  // Creating an empty tree
	/*Code to test the logic*/
	root = Insert(root,15);
	root = Insert(root,10);
	root = Insert(root,20);
	root = Insert(root,25);
	root = Insert(root,8);
	root = Insert(root,12);
	root = Insert(root,11);
	root = Insert(root,24);

	/* commented on 2017.12.05

	// Ask user to enter a number.
	int number;
	cout<<"Enter number be searched\n";
	cin>>number;
	//If number is found, print "FOUND"
	if(Search(root,number) == true) cout<<"Found\n";
	else cout<<"Not Found\n";

	*/

	int path[10], maxpath[10];;
	int pathlen = 0;
	int maxpathlen = 0;
	Allpath(root, path, pathlen);
	Maxpath(root, path, pathlen, maxpath, maxpathlen);
	cout << endl;
	for(int i= maxpathlen; i>=0; i--) {
		cout <<  maxpath[i] << " ";
	}
	cout << endl << maxpathlen << endl;
}
