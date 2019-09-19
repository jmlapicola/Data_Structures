#ifndef MY_DEQUE_H
#define MY_DEQUE_H

#include "DequeInterface.h"
#include <sstream>
#include <exception>

template<typename T>
class MyDeque : public DequeInterface<T>
{
private:
	static const size_t INIT_ARRAY_SIZE = 4;
	size_t arraySize = INIT_ARRAY_SIZE;
	size_t frontIndex = 0;
	size_t backIndex = INIT_ARRAY_SIZE - 1;
	size_t items = 0;
	T * cirArray = NULL;

	void reallocate()
	{
		T * oldArray = cirArray;
		cirArray = new T[arraySize*2];
		size_t index = frontIndex;
		for (size_t i = 0; i < items; ++i)
		{
			cirArray[i] = oldArray[index];
			index = (index + 1) % arraySize;
		}
		frontIndex = 0;
		backIndex = arraySize - 1;
		arraySize *= 2;
		delete[] oldArray;
	}

public:
	MyDeque(void)
	{
		cirArray = new T[arraySize];
	}

	~MyDeque(void)
	{
		delete[] cirArray;
	}

	/** Insert item at front of deque */
	virtual void push_front(const T& value)
	{
		if (items == arraySize) reallocate();
		frontIndex = (frontIndex + arraySize - 1) % arraySize;
		cirArray[frontIndex] = value;
		++items;
	}

	/** Insert item at rear of deque */
	virtual void push_back(const T& value)
	{
		if (items == arraySize) reallocate();
		backIndex = (backIndex + 1) % arraySize;
		cirArray[backIndex] = value;
		++items;
	}

	/** Remove the front item of the deque */
	virtual void pop_front(void)
	{
		if (items == 0) throw std::out_of_range("Already empty!");
		frontIndex = (frontIndex + 1) % arraySize;
		--items;
	}

	/** Remove the rear item of the deque */
	virtual void pop_back(void)
	{
		if (items == 0) throw std::out_of_range("Already empty!");
		backIndex = (backIndex + arraySize - 1) % arraySize;
		--items;
	}

	/** Return the front item of the deque (Do not remove) */
	virtual T& front(void)
	{
		if (items == 0) throw std::out_of_range("Empty!");
		return cirArray[frontIndex];
	}

	/** Return the rear item of the deque (Do not remove) */
	virtual T& back(void)
	{
		if (items == 0) throw std::out_of_range("Empty!");
		return cirArray[backIndex];
	}

	/** Return the number of items in the deque */
	virtual size_t size(void) const
	{
		return items;
	}

	/** Return true if deque is empty */
	virtual bool empty(void) const
	{
		return items == 0;
	}

	/** Return item in deque at index (0 based) */
	virtual T& at(size_t index)
	{
		if (index >= items) throw std::out_of_range("At out of range.");
		return cirArray[(frontIndex + index) % arraySize];
	}

	/** Return the deque items */
	virtual std::string toString(void) const
	{
		std::stringstream ss;
		for (size_t i = 0; i < items; ++i)
		{
			ss << " " << cirArray[(frontIndex + i) % arraySize];
		}
		return ss.str();
	}

	/** Returns the index of requested item */
	int find(T item) const
	{
		for (size_t i = 0; i < items; ++i)
		{
			if (cirArray[(frontIndex + i) % arraySize] == item) return i;
		}
		return -1;
	}
};

#endif // MY_DEQUE_H