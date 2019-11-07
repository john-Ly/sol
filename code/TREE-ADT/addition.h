//// find height of a binary tree

/*
depth of node = number of edges in path from root to that node

depth = distance from root
height = distance from the longest leaf

height of tree = height of root
height of tree with 1 node = 0

height of tree = max depth
*/

int FindHeight(Node *root) {
	if(root == nullptr)
		return -1;
	return max(FindHeight(root->left), FindHeight(root->right)) + 1;
}

//// Binary tree traversal
/*
Traversals can be done either depth-first or breadth-first(level order)
*/

//// check if a given binary tree is BST or not
bool IsSubtreeLesser(Node *root, int value){
	if(root == nullptr) return true;
	if(root->data =< value
		&& IsSubtreeLesser(root->left, value)
		&& IsSubtreeLesser(root->right, value))
		return true;
	else
		return false;
}
bool IsSubtreeGreater(Node *root, int value){
	if(root == nullptr) return true;
	if(root->data >= value
		&& IsSubtreeLesser(root->left, value)
		&& IsSubtreeLesser(root->right, value))
		return true;
	else
		return false;
}
bool IsBinarySearchTree(Node *root) {
	if(IsSubtreeLesser(root->left, root->data)
		&& IsSubtreeGreater(root->right, root->data)
		&& IsBinarySearchTree(root->left)
		&& IsBinarySearchTree(root->right))
		return true;
	else
		return false;
}

IsSubtreeGreater, IsSubtreeLesser
are very expensive function, some nodes will be traversaled multi times

bool IsBinarySearchTree(Node *root, int minValue, intmaxValue) {
	if(root->data > minValue
		&& root->data < maxValue
		&& IsBinarySearchTree(root->left, minValue, root->data)
		&& IsBinarySearchTree(root->right, root->data, maxValue))
		return true;
	else
		return false;
}

without consider dupulicates,

another solution: in-order traversal to check whether sorted or not