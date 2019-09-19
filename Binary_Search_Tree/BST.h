#ifndef BST_H
#define BST_H
#include "BSTInterface.h"
#include <string>
#include <sstream>

using namespace std;

/** A binary tree node with data, left and right child pointers */
template<typename T>
class BST : public BSTInterface<T>
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

	// Output nodes at a given level
	bool outLevel(Node* node, size_t level, stringstream& out) const;

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
		if (node == NULL) return true;
		clear(node->left);
		clear(node->right);
		delete node;
		node = NULL;
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
		return clear(root);
	}

	/** Returns the number of nodes in tree */
	size_t size()
	{
		return nodes;
	}

	/** Return a level order traversal of a BST as a string */
	virtual std::string toString() const
	{
		if (root == NULL) return " empty";
		stringstream out;
		int level = 0;
		
		do
		{
			out << endl << "  " << ++level << ":";
		} while (outLevel(root, level, out));
		
		return out.str();
	}

	/** BST iterator */
	class Iterator
	{
	private:
		Node * root;
		size_t index;

		Node * find(Node * node, size_t& countdown)
		{
			if (node == NULL) return NULL;
			Node* left = find(node->left, countdown);
			if (left != NULL) return left;
			if (countdown == 0) return node;
			return find(node->right, --countdown);
		}

	public:
		Iterator(Node* iterRoot, size_t iterIndex) : root(iterRoot), index(iterIndex){}
		~Iterator() {}

		bool operator!=(const Iterator& iter2) const
		{
			return(index != iter2.index);
		}
		bool operator==(const Iterator& iter2) const
		{
			return(index == iter2.index);
		}
		Iterator operator++()
		{
			return Iterator(root, ++index);
		}
		T operator*()
		{
			size_t itemNum = 0;
			size_t countdown = index;
			Node* found = find(root, countdown);
			return found->value;
		}
	};

	Iterator begin() const
	{
		return Iterator(root, 0);
	}
	
	Iterator end() const
	{
		return Iterator(root, nodes);
	}

	/** Uses insertion operator to return toString value */
	friend std::ostream& operator<< (std::ostream& os, const BST<T>& bst)
	{
		os << bst.toString();
		return os;
	}
};


// Output nodes at a given level
template<typename T>
bool BST<T>::outLevel(Node* node, size_t level, stringstream& out) const
{
	if (node == NULL) return false;
	if (level == 1)
	{
		out << " " << node->value;
		if ((node->left != NULL) || (node->right != NULL)) return true;
		return false;
	}
	if ((level == 2) && !node->left && node->right) out << " _";
	bool left = outLevel(node->left, level - 1, out);
	bool right = outLevel(node->right, level - 1, out);
	if ((level == 2) && node->left && !node->right) out << " _";
	return left || right;
}


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