#ifndef QUICKSORT_H
#define QUICKSORT_H
#include <string>
#include <sstream>
#include "QSInterface.h"

using namespace std;

template<typename T>
class QuickSort : public QSInterface<T>
{
private:
	T * QSArray = NULL;
	size_t maxCapacity = 0;
	size_t numItems = 0;

	//Doubles the array capacity 
	bool reallocate()
	{
		T * old = QSArray;
		QSArray = new T[maxCapacity * 2];
		for (size_t i = 0; i < numItems; ++i) QSArray[i] = old[i];
		delete[] old;
		maxCapacity *= 2;
		return true;
	}

public:
	QuickSort() {}
	virtual ~QuickSort()
	{
		delete[] QSArray;
	}

	/** Dynamically allocate an initial array to the QuickSort class. */
	virtual bool createArray(size_t newCapacity)
	{
		delete[] QSArray;
		QSArray = new T[newCapacity];
		maxCapacity = newCapacity;
		numItems = 0;
		return true;
	}

	/** Add an element to the QuickSort array. Dynamically grow array as needed. */
	virtual bool addElement(T element)
	{
		if (numItems == maxCapacity) reallocate();
		QSArray[numItems++] = element;
		return true;
	}

	/** Sort the elements of a QuickSort subarray using median and partition functions. */
	virtual bool sort(size_t left, size_t right)
	{
		if (numItems == 0 || left > right || right > numItems) return false;
		if (left + 1 == right || left == right) return true;
		if (left + 2 == right)
		{
			if (QSArray[left] > QSArray[right - 1]) swap(QSArray[left], QSArray[right - 1]);
			return true;
		}
		size_t middle = partition(left, right, medianOfThree(left, right));
		return sort(left, middle) && sort(middle + 1, right);
	}

	/** Sort all elements of the QuickSort array using median and partition functions. */
	virtual bool sortAll()
	{
		return sort(0, numItems);
	}

	/** Removes all items from the QuickSort array. */
	virtual bool clear()
	{
		numItems = 0;
		return true;
	}

	/** Return size of the QuickSort array. */
	virtual size_t capacity() const
	{
		return maxCapacity;
	}

	/** Return number of elements in the QuickSort array. */
	virtual size_t size() const
	{
		return numItems;
	}

	/** The median of three pivot selection has two parts:
	1) Calculates the middle index by averaging the given left and right indices:
	middle = (left + right)/2
	2) Then bubble-sorts the values at the left, middle, and right indices.

	After this method is called, data[left] <= data[middle] <= data[right].

	@param left - the left boundary for the subarray from which to find a pivot
	@param right - the right + 1 boundary for the subarray from which to find a pivot
	@return the index of the pivot (middle index).
	Return -1 if	1) the array is empty,
	2) if either of the given integers is out of bounds,
	3) or if the left index is not less than the right index.
	*/
	virtual int medianOfThree(size_t left, size_t right)
	{
		if (numItems == 0 || left >= right || right > numItems) return -1;
		size_t middle = (left + right) / 2;
		if (QSArray[left] > QSArray[middle]) swap(QSArray[left], QSArray[middle]);
		if (QSArray[middle] > QSArray[right-1]) swap(QSArray[middle], QSArray[right-1]);
		if (QSArray[left] > QSArray[middle]) swap(QSArray[left], QSArray[middle]);
		return middle;
	}

	/** Partitions a subarray around a pivot value selected according
	to median-of-three pivot selection. Because there are multiple ways
	to partition a list, follow the algorithm on page 611.

	The values which are smaller than the pivot should be placed to the left of the pivot;
	the values which are larger than the pivot should be placed to the right of the pivot.

	@param left - left index for the subarray to partition.
	@param right - right index + 1 for the subarray to partition.
	@param pivotIndex - index of the pivot in the subarray.
	@return the pivot's ending index after the partition completes:
	Return -1 if	1) the array is empty,
	2) if any of the given indexes are out of bounds,
	3) if the left index is not less than the right index.
	*/
	virtual int partition(size_t left, size_t right, size_t pivotIndex)
	{
		if (numItems == 0 || left >= right || pivotIndex < left || pivotIndex > right|| right > numItems) return -1;
		
		swap(QSArray[left], QSArray[pivotIndex]);
		
		size_t up = left + 1;
		size_t down = right - 1;
		while (true)
		{
			while ((up != right - 1) && (QSArray[left] >= QSArray[up])) ++up;
			while (QSArray[left] < QSArray[down]) --down;
			if (down <= up) break;
			swap(QSArray[up], QSArray[down]);
		}
		swap(QSArray[left], QSArray[down]);
		return down;
	}

	/** @return: comma delimited string representation of the array. */
	virtual std::string toString() const
	{
		if (numItems == 0) return "Empty";
		stringstream ss;
		ss << QSArray[0];
		for (size_t i = 1; i < numItems; ++i)
		{
			ss << "," << QSArray[i];
		}
		return ss.str();
	}
};

#endif // QUICKSORT_H 