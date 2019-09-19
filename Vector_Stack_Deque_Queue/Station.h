#ifndef STATION_H
#define STATION_H

#include "myVector.h"
#include "myQueue.h"
#include "MyStack.h"

template<typename T>
class Station
{
private:
	MyVector<T> train;
	MyStack<T> stack;
	MyQueue<T> queue;
	T turnTable;
	bool emptyTable = true;
public:
	std::string addStation(T car)
	{
		if (!emptyTable) return "Turntable occupied!";
		turnTable = car;
		emptyTable = false;
		return "OK";
	}
	std::string removeStation()
	{
		if (emptyTable) return "Turntable empty!";
		train.push_back(turnTable);
		emptyTable = true;
		return "OK";
	}
	std::string topStation()
	{
		if (emptyTable) return "Turntable empty!";
		std::stringstream out;
		out << turnTable;
		return out.str();
	}
	std::string addStack()
	{
		if (emptyTable) return "Turntable empty!";
		stack.push(turnTable);
		emptyTable = true;
		return "OK";
	}
	std::string removeStack()
	{
		if (stack.size() == 0) return "Stack empty!";
		turnTable = stack.top();
		stack.pop();
		emptyTable = false;
		return "OK";
	}
	std::string topStack()
	{
		if (stack.size() == 0) return "Stack empty!";
		std::stringstream out;
		out << stack.top();
		return out.str();
	}
	std::string sizeStack()
	{
		std::stringstream out;
		out << stack.size();
		return out.str();
	}
	std::string addQueue()
	{
		if (emptyTable) return "Turntable empty!";
		queue.push(turnTable);
		emptyTable = true;
		return "OK";
	}
	std::string removeQueue()
	{
		if (queue.size() == 0) return "Queue empty!";
		turnTable = queue.top();
		queue.pop();
		emptyTable = false;
		return "OK";
	}
	std::string topQueue()
	{
		if (queue.size() == 0) return "Queue empty!";
		std::stringstream out;
		out << queue.top();
		return out.str();
	}
	std::string sizeQueue()
	{
		std::stringstream out;
		out << queue.size();
		return out.str();
	}
	std::string find(T car)
	{
		if (turnTable == car) return "Turntable";
		std::stringstream ss;
		if (queue.find(car) != -1) ss << "Queue[" << queue.find(car) << "]";
		else if (stack.find(car) != -1) ss << "Stack[" << stack.find(car) << "]";
		else if (train.find(car) != -1) ss << "Train[" << train.find(car) << "]";
		else return "Not Found!";
		return ss.str();
	}
	std::string toString() const
	{
		return train.tostring();
	}
};

#endif