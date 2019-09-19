#ifndef MY_QUEUE_H
#define MY_QUEUE_H

#include "MyDeque.h"

template<typename T>
class MyQueue
{
private:
	MyDeque<T> container;
public:
	void push(const T& value)
	{
		container.push_back(value);
	}
	void pop(void)
	{
		container.pop_front();
	}
	T& top(void)
	{
		return container.front();
	}
	size_t size() const
	{
		return container.size();
	}
	T& at(size_t index)
	{
		return container.at(index);
	}
	std::string tostring() const
	{
		return container.toString();
	}
	int find(T value) const
	{
		return container.find(value);
	}
};
#endif // MY_QUEUE_H
