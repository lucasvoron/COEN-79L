/* Lucas Voron
 * Oct. 22, 2021
 * COEN 79
 * Lab 4 */

#include "keyed_bag.h"
#include <assert.h>
#include <cassert>

using namespace std;

namespace coen79_lab4
{
	const keyed_bag::size_type keyed_bag::CAPACITY;

	keyed_bag::keyed_bag()
	{
		used=0;
		for (int i=0; i<keyed_bag::CAPACITY; i++) 
		{
			keys[i]= ' ';
			data[i]= 0;
		}
	}

	void keyed_bag::erase()
	{
		for(int i=0;i<used;i++)
		{
			keys[i] = ' ';
			data[i] = 0;
		}
		used=0;
	}

	bool keyed_bag::erase(const key_type& key)
	{
		if(has_key(key)) // check if key is found
			for(int i=0; i<used; i++)
				if(keys[i] == key)
				{
					for (int j=i; j<used-1; j++)
					{
						keys[j] = keys[j+1]; // shift the keys forward
						data[j] = data[j+1]; // shift the data forward
					}
					used--; // decrease used variable
					return true;
				}
		return false; // if the key is not found return false
	}
	void keyed_bag::insert(const value_type& entry, const key_type& key)
	{
		assert(size() < CAPACITY); // check the capacity
		if (has_key(key)==false) // check the key
		{
			data[used] = entry; // insert new item into the bag
			keys[used] = key; // insert new key into the bag
			used++; // increment used variable
		}
	}

	void keyed_bag::operator +=(const keyed_bag& addend)
	{
		assert(used + addend.used < CAPACITY); // check the capacity and keys first
		std::copy(addend.data, addend.data + addend.used, data + used); // combine data
		std::copy(addend.keys, addend.keys + addend.used, keys + used); // combine keys
		used += addend.used; // combine the used variable
	}
	
	bool keyed_bag::has_key(const key_type& key) const
	{
		for (int i = 0; i<used; i++) // iterate through and check if there is a duplicate key
			if (keys[i]==key) // compare key with each key in array
				return true;
		return false;
	}
	
	keyed_bag::value_type keyed_bag::get(const key_type& key) const
	{
		for(int i = 0; i<used; i++) // check the key
			if (keys[i]==key)
				return data[i]; // return the item
		return 0;
	}

	keyed_bag::size_type keyed_bag::size() const
	{
		return used; // return the size of the items in the bag
	}
	
	keyed_bag::size_type keyed_bag::count(const value_type& target) const
	{
		int count = 0;
		for (int i = 0; i<used; i++) // iterate throught the bag
			if (data[i]==target) // check if the current item is the target
				count++; // incremement the count when the target has been found
		return count;
	};

	bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const
	{
		bool duplicate = false;
		for (int i = 0; i<used; i++)
			for (int j = 0; j<used; j++)
				if (keys[i] ==otherBag.keys[j]) // check if the other keyed bag has any duplicate components with this bag
					duplicate = true;
		return duplicate;
	};

	// NONMEMBER FUNCTIONS for the keyed_bag class
	keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2)
	{
		keyed_bag total; // create new keyed_bag object total
		assert(b1.size() + b2.size() < keyed_bag::CAPACITY); // make sure that the keyed bag has enough capacity
		total += b1; // add b1 to the total object
		total += b2; // add b2 to the total object
		return total;
	}
}
