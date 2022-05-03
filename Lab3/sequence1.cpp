//
// FILE: sequence1.cpp
//  Sequence Class
//
//  COEN 79
//  
//
//
// INVARIANT for the sequence ADT (i.e. verbalization of rules governing
//   private member function behavior):
//   1. The number of items in the sequence is in the member variable used
//      (i.e. used = 0 means the sequence is empty).
//   2. For an empty sequence, we do not care what is stored in any of the
//      array data.  For a non-empty sequence, the items in the sequence are
//      stored in strictly maintained order in data[0] through
//      data[used].  We don't care what's in the rest of data (so don't
//      need to initialize data in the constructor).
//   3. To maintain strict order, current_index is used to keep track
//      of current location in data; when current_index is used-1,
//      we're at the last place in the array.  Also whenever current_index
//      is greater than or equal to used, there is no current item.
//   4. capacity keeps track of the current capacity of the array pointed
//      to by data; capacity starts out with the value initial_capacity
//      and is changed by resize as needed (whenever used is greater than
//      or equal to capacity).
//


#include "sequence1.h"
#include <iostream>
#include <cassert>
#include <assert.h>
#include <cmath>

using namespace std;
using namespace coen79_lab3;

namespace coen79_lab3 {
	
	sequence::sequence() {
		used = 0;
		current_index = 0; //initialize member variables here

		for(int i; i<CAPACITY; i++)
			data[i] = 0;
	}

	void sequence::start() {
		current_index = 0; //set the current index pointing to the first item
	}
	
	void sequence::end() {
		if(used>0) //check if the sequence is empty
        		current_index = used-1; //set the current index pointing to the last item
	}
	
	sequence::value_type sequence::current() const {
    		assert(is_item()); //don't forget to check if the current index is valid
		return data[current_index]; //return the current index value
    	}
	
	void sequence::advance() {
		if(is_item()&&(current_index!=used)) //check if we are at the end of the sequence and if the capacity of the bag has been reached
			current_index++; //set the current index to point to the next item
	}

	void sequence::retreat() {
		if(is_item()&&(current_index!=0)) //check if it is already at the beginning of the sequence
			current_index--; //set the current index to point to the previous item
	}
	
	bool sequence::is_item() const {
		if(current_index < used) //does the current index point to an item or not 
			return true;
		else
			return false;
	}
	
	void sequence::insert(const value_type& entry) {
		if(size() < CAPACITY) //check capacity first
		{
			if(!is_item()) //if the is_item returns false, then insert at the front
				current_index = 0;
			for (size_type i = used; i>current_index; i--) //shift items over and insert new entry at current index
				data[i] = data[i-1];
			data[current_index] = entry;
			used++; //increment used variable
		}
	}
	
	void sequence::attach(const value_type& entry) {
		if (size() < CAPACITY) //check capacity first
		{
			if (!is_item()) //if the is_item returns false, the insert entry and the end
			{
				data[used] = entry;
				current_index = used;
				used++;
			}
			else
			{	
				for(size_type i =used; i>current_index; i--) //shift items over and add the new entry behing the current index
					data[i] = data[i-1];
				data[current_index + 1] = entry;
				current_index++;
				used++; //increment used variable
			}
		}
	}
	
	void sequence::remove_current() {
    		if(is_item()) //if the is_item is true, remove current index
		{
			for (size_type i = current_index; i < used-1; i++) //remove the current entry and shift items over
				data[i] = data[i+1];
			used--; //decrement used variable
		}
	}

	void sequence::insert_front(const value_type& entry) {
		if(size() < CAPACITY) //check capacity first
		{
			for(size_type i = used; i>0; i--) //shift the items over
				data[i+1] = data[i];
			data[0] = entry; //move the current index to the front and insert there
			used++;
		}
	}

	void sequence::attach_back(const value_type& entry) {
		if(size() < CAPACITY) //check capacity first
		{
			data[used] = entry;
			current_index = used; //move the current index to the end and then attach
			used++; //increment used variable
		}
	}

	void sequence::remove_front() {
		if(is_item()) //check if is_item returns true
		{
			for(size_type i = 0; i < used; i++) //shift items
				data[i] = data[i+1];
			data[used] = 0; //move to front
			used--; //decrement used variable
		}
	}

	sequence::size_type sequence::size() const {
		return used; //return the number of entries
	}
	
	sequence::value_type sequence::operator[](int index) const {
		assert(index < used); //check if the there is an item there
			return data[index]; //return the value of the entry
	}
    
	sequence operator+(sequence& lhs, sequence& rhs) {
		sequence total;
		assert(lhs.size() + rhs.size() <=sequence::CAPACITY); //check that the size of the lhs and rhs added is less than the capacity
		total+=rhs; //add right hand side to the total
		total+=lhs; //add left hand side to the total
		return total;
	}

	sequence operator+=(const sequence& lhs, const sequence& rhs) {
		sequence s(lhs);
		assert(s.size() + rhs.size() < sequence::CAPACITY);
		std::copy(rhs.data, rhs.data + rhs.used, s.data + lhs.used); //adds items of rhs to lhs
		s.used = lhs.used + rhs.used; //increments the used variable by the rhs used number
		s.current_index = s.used-1;
	}

	// Homework Question Functions
	double sequence::mean() const
	{
		double sum=0.0;

		for(int i=0; i<used; ++i) //iterate through the sequence to calculate the sum
			sum+=data[i];
		return sum/size(); //return the mean
	}

	double sequence::standardDeviation() const
	{
		double stanDev=0.0;
		
		for(int i=0; i<used; ++i) //iterate through to calculate the numerator of standard deviation
			stanDev+=pow(data[i]-mean(),2);
		return sqrt(stanDev/used); //return the standard deviation
	}

	sequence::value_type summation(const sequence &s)
	{
		double total=0.0;
		for(int i=0; i<s.size(); ++i) //iterate through to calculate the sum
			total+=s.data[i];
		return total; //return the sum
	}

}
