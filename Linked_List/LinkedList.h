#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <sstream>

using namespace std;

template<typename T>
class LinkedList
{
private:
	struct Node
	{
		T value;
		Node* next;
		Node(const T& val) : value(val), next(NULL) {} //end node
		Node(const T& val, Node* nxt) : value(val), next(nxt) {} //middle node
	};
	Node* head = NULL;

public:
	/*Constructor*/
	LinkedList() {}

	/*Destructor*/
	~LinkedList()
	{
		this->clear();
	}

	/** Iterater class */
	class Iterator
	{
	private:
		Node * node; //pointer to node
	public:
		/** Constructor */
		Iterator(Node* n) : node(n) {}

		/** Increment operator */
		Iterator& operator++()
		{
			this->node = this->node->next;
			return *this;
		}

		/** Inequality operator */
		bool operator!=(const Iterator& other) const
		{
			if (node == other.node) return false;
			return true;
		}

		/** Derefferencing operator*/
		T& operator*() const
		{
			return node->value;
		}
	};
	
	/** Returns pointer to node */
	Node * find(Node* start, T value)
	{
		while (start != NULL)
		{
			if (start->value == value) return start;
			start = start->next;
		}
		return NULL;
	}

    /** Returns pointer to last node */
	Node * last(Node* start)
	{
		if (start == NULL) return NULL;
		Node* next = start->next;
		while (next != NULL)
		{
			start = start->next;
			next = start->next;
		}
		return start;
	}

	/** like find*/
	Node * before(Node* start, T value)
	{
		while (start->next != NULL)
		{
			if (start->next->value == value) return start;
			start = start->next;
		}
		return NULL;
	}

	/** Insert Node at beginning of linked list (no duplicates) */
	virtual bool insertHead(T value)
	{
		if (find(head, value)) return false;
		head = new Node(value, head);
		return true;
	}

	/** Insert Node at end of linked list (no duplicates) */
	virtual bool insertTail(T value)
	{
		if (find(head, value)) return false;
		if (head == NULL)
		{
			head = new Node(value);
			return true;
		}
		last(head)->next = new Node(value);
		return true;
	}

	/** Insert Node after matchNode (no duplicates) */
	virtual bool insertAfter(T matchNode, T node)
	{
		if (find(head, node)) return false;
		Node* match = find(head, matchNode);
		if (!match) return false;
		match->next = new Node(node, match->next);
		return true;
	}

	/** Remove Node from linked list */
	virtual bool remove(T value)
	{
		if (head == NULL) return false;
		Node* toDelete;
		if (head->value == value)
		{
			toDelete = head;
			head = head->next;
		}
		else
		{
			Node* beforeMatch = before(head, value);
			if (!beforeMatch) return false;
			toDelete = beforeMatch->next;
			beforeMatch->next = beforeMatch->next->next;
		}
		delete toDelete;
		return true;
	}

	/** Remove all Nodes from linked list */
	virtual bool clear()
	{
		while (head != NULL)
		{
			Node* toDelete = head;
			head = head->next;
			delete toDelete;
		}
		return true;
	}

	/** Return Node at index (0 based) via value parameter */
	virtual bool at(size_t index, string& value)
	{
		if (this->size() <= index)return false;
		Node* node = head;
		for (int i = 0; i < index; i++)
		{
			node = node->next;
		}
		stringstream ss;
		ss << node->value;
		value = ss.str();
		return true;
	}

	/** Returns the number of nodes in the linked list */
	virtual size_t size() const
	{
		Node* node = head;
		size_t size = 0;
		while (node != NULL)
		{
			size++;
			node = node->next;
		}
		return size;
	}

	/** Return a level order traversal of a Linked List as a string */
	virtual string toString() const
	{
		if (head == NULL) return "Empty";
		stringstream value;
		Node* node = head;
		while (node != NULL)
		{
			value << node->value << " ";
			node = node->next;
		}
		return value.str();
	}

	/** Returns Iterator from head */
	Iterator begin()
	{
		return Iterator(head);
	}

	/** Returns Iterator after end */
	Iterator end()
	{
		return Iterator(NULL);
	}
};

#endif