//**** YOU MAY NOT MODIFY THIS DOCUMENT ****/
#ifndef HASH_MAP_H
#define HASH_MAP_H
#include <string>
#include <utility>
#include <sstream>
#include "HashMapInterface.h"

template <typename K, typename V>
class HashMap: public HashMapInterface<K,V>
{
private:
	pair<K, V> * table = NULL;
	size_t tableSize = DEFAULT_MAP_HASH_TABLE_SIZE;
	size_t items = 0;

	void rehash()
	{
		pair<K, V> * temp = table;
		table = new pair<K, V>[2 * tableSize];
		for (size_t i = 0; i < tableSize; ++i)
		{
			if (temp[i].first.length())
			{
				int index = temp[i].first[0];
				for (size_t j = 1; j < temp[i].first.length(); ++j)
				{
					index = index * 3 + temp[i].first[j];
				}
				index %= 2 * tableSize;

				int k = 1;
				while (true)
				{
					if (table[index].first.length())
					{
						index = (index + k) % (2*tableSize);
						k += 2;
					}
					else
					{
						table[index].first = temp[i].first;
						table[index].second = temp[i].second;
						break;
					}
				}
			}
		}
		delete[] temp;
		tableSize *= 2;
	}

public:
	HashMap()
	{
		table = new pair<K, V>[tableSize];
	}

	virtual ~HashMap()
	{
		delete[] table;
	}

	/** Read/write index access operator.
	If the key is not found, an entry is made for it.
	@return: Read and write access to the value mapped to the provided key. */
	virtual V& operator[](const K& key)
	{
		int index = key[0];
		for (size_t i = 1; i < key.length(); ++i)
		{
			index = index * 3 + key[i];
		}

		int k = 1;
		while (true)
		{
			if (table[index % tableSize].first.length())
			{
				if (table[index % tableSize].first == key)
				{
					return table[index % tableSize].second;
				}
				index = index + k;
				k += 2;
			}
			else
			{
				++items;
				double load = 100 * items;
				if (load / tableSize > LOAD_THRESHOLD) rehash();
				table[index % tableSize].first = key;
				return table[index % tableSize].second;
			}
		}
	}

	/** @return: the number of elements that matchthe key in the Map. */
	virtual size_t count(const K& key)
	{
		return 0;
	}

	/** Removes all items from the Map. */
	virtual void clear()
	{
		delete[] table;
		table = new pair<K, V>[tableSize];
	}

	/** @return: number of Key-Value pairs stored in the Map. */
	virtual size_t size() const
	{
		return items;
	}

	/** @return: maximum number of Key-Value pairs that the Map can hold. */
	virtual size_t max_size() const
	{
		return tableSize;
	}

	/** @return: string representation of Key-Value pairs in Map. */
	virtual std::string toString() const
	{
		stringstream ss;
		for (size_t i = 0; i < tableSize; ++i)
		{
			if (table[i].first.length())
			{
				ss << "  [" << i << ":" << table[i].first;
				ss << "->" << table[i].second << "]" << endl;
			}
		}
		return ss.str();
	}
};
#endif // HASH_MAP_H