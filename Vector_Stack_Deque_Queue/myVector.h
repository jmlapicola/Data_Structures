#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include "MyDeque.h"

template<typename T>
class MyVector
{
private:
	MyDeque<T> vectorDeque;
public:
	void push_back(const T& value)
	{
		vectorDeque.push_back(value);
	}
	void pop_back(void)
	{
		vectorDeque.pop_back();
	}
	T& back(void)
	{
		return vectorDeque.back();
	}
	size_t size() const
	{
		return vectorDeque.size();
	}
	T& at(size_t index)
	{
		return vectorDeque.at(index);
	}
	std::string tostring() const
	{
		return vectorDeque.toString();
	}
	int find(T value) const
	{
		return vectorDeque.find(value);
	}
};
#endif // MY_VECTOR_H
