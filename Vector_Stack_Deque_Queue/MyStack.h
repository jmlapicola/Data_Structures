#ifndef MY_STACK_H
#define MY_STACK_H

#include "MyDeque.h"

template<typename T>
class MyStack
{
private:
	MyDeque<T> stackDeque;
public:
	void push(const T& value)
	{
		stackDeque.push_back(value);
	}
	void pop(void)
	{
		stackDeque.pop_back();
	}
	T& top(void)
	{
		return stackDeque.back();
	}
	size_t size() const
	{
		return stackDeque.size();
	}
	T& at(size_t index)
	{
		return stackDeque.at(index);
	}
	std::string tostring() const
	{
		return stackDeque.toString();
	}
	int find(T value) const
	{
		return stackDeque.find(value);
	}
};
#endif // MY_STACK_H
