//**** YOU MAY NOT MODIFY THIS DOCUMENT ****/
#ifndef SET_H
#define SET_H
#include <string>
#include "SetInterface.h"
#include "BST.h"

template<typename T>
class Set : public SetInterface<T>
{
private:
	BST<string> data;

public:
	Set() {}
	virtual ~Set() {}

	/** Inserts item into the set, if the container doesn't
	already contain an element with an equivalent value.
	@return: pair.first = pointer to item
	pair.second = true if successfully inserted, else false. */
	//virtual Pair<T*, bool> insert(const T& item) = 0;
	virtual bool insert(const T& item)
	{
		return data.addNode(item);
	}

	/** Removes all items from the set. */
	virtual void clear()
	{
		data.clearTree();
	}

	/** @return: the number of elements contained by the Set. */
	virtual size_t size() const
	{
		return data.size();
	}

	/** @return: return 1 if contains element equivalent to item, else 0. */
	virtual size_t count(const T& item)
	{
		return (data.find(item) ? 1 : 0);
	}

	/** @return: string representation of items in Set. */
	virtual std::string toString() const
	{
		return data.toString();
	}

	/** Uses insertion operator to return toString value */
	friend std::ostream& operator<< (std::ostream& os, const Set<T>& set)
	{
		os << set.toString();
		return os;
	}
};
#endif // SET_H