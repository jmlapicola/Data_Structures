#ifndef BST_H
#define BST_H
#include <string>
#include <sstream>

using namespace std;

/** A binary tree node with data, left and right child pointers */
template<typename T>
class BST
{
private:
	//Node struct
	struct Node
	{
		T value;
		Node* left;
		Node* right;
		Node(const T& val) : value(val), left(NULL), right(NULL) {} //leaf node
	};

	//Data
	Node* root = NULL;
	size_t nodes = 0;

	//prints out in order
	string toString(const Node* node) const
	{
		stringstream ss;
		if (node->left != NULL) ss << toString(node->left) << ",";
		ss << node->value;
		if (node->right != NULL) ss << "," << toString(node->right);
		return ss.str();
	}

	//finds a node and returns a reference to the pointer to the node
	bool remove(Node*& node, const T& target);

	//adds a node in the proper spot recursively
	bool add(Node*& node, const T& target)
	{
		if (node == NULL) //proper position found
		{
		node = new Node(target);
		return true;
		}
		if (node->value > target) return add(node->left, target);
		if (node->value < target) return add(node->right, target);
		return false; //node already exists
	}

	//swaps a node with its predecessor
	bool swapPredecessor(Node* node)
	{
		Node* ptr = node->left;
		while (ptr->right != NULL) ptr = ptr->right;
		T temp = ptr->value;
		ptr->value = node->value;
		node->value = temp;
		return true;
	}

	//returns true if target value is found in within subtree
	bool find(Node* node, const T& target) const
	{
		if (node == NULL) return false;
		if (target < node->value) return find(node->left, target);
		if (target > node->value) return find(node->right, target);
		return true;
	}

	//clears all children of a certain node
	bool clear(Node*& node)
	{
		if (node->left != NULL) clear(node->left);
		if (node->right != NULL) clear(node->right);
		delete node;
		return true;
	}

public:
	BST(void) {}
	virtual ~BST(void) { clearTree(); }

	/** Return true if node added to BST, else false */
	virtual bool addNode(const T& value)
	{
		if(add(root, value))
		{
			++nodes;
			return true;
		}
		return false;
	}

	/** Return true if node removed from BST, else false */
	virtual bool removeNode(const T& value)
	{
		if(remove(root, value))
		{
			--nodes;
			return true;
		}
		return false;
	}

	/** Return true if node found with desired value, else false */
	bool find(const T& target) const
	{
		return find(root, target);
	}

	/** Return true if BST cleared of all nodes, else false */
	virtual bool clearTree()
	{
		nodes = 0;
		if(root!=NULL) return clear(root);
		root = NULL;
		return true;
	}

	/** Returns the number of nodes in tree */
	size_t size() const
	{
		return nodes;
	}

	/** Return a level order traversal of a BST as a string */
	virtual std::string toString() const
	{
		if (root == NULL) return "";
		else return toString(root);
	}

	/** Uses insertion operator to return toString value */
	friend std::ostream& operator<< (std::ostream& os, const BST<T>& bst)
	{
		os << bst.toString();
		return os;
	}
};

//finds a node and returns a reference to the pointer to the node
template<typename T>
bool BST<T>::remove(Node*& node, const T& target)
{
	//find node
	if (node == NULL) return false;
	else if (target < node->value) return remove(node->left, target);
	else if (target > node->value) return remove(node->right, target);
	//delete node
	if (node->left == NULL && node->right == NULL)
	{
		delete node;
		node = NULL;
		return true;
	}
	if (node->left == NULL)
	{
		Node* temp = node;
		node = node->right;
		delete temp;
		return true;
	}
	else if (node->right == NULL)
	{
		Node* temp = node;
		node = node->left;
		delete temp;
		return true;
	}
	else
	{
		swapPredecessor(node);
		return remove(node->left, target);
	}
}
#endif	// BST_H