// FILE: statistician.cpp
// CLASS IMPLEMENTED: statistician (see stats.h for documentation)

#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include "statistician.h"

using namespace std;

namespace coen79_lab2
{
	statistician::statistician() //constructor resets values
	{			
		count = 0;
		total = 0;
	}
	void statistician::next(double r)
	{
		total += r;
		if(count == 0) // if there are no other elements, then the number passed in is both the smallest and largest
		{
			min = r;
			max = r;
		}
		else // checks if the number passed in is smaller than or greater than the smallest and largest numbers
		{
			if(r < min)
				min = r;
			if(r > max)
				max = r;
		}
		count++;
	}
	void statistician::reset()
	{
		count = 0;
		total = 0;
	}
	int statistician::length() const
	{
		return count;
	}
	double statistician::sum() const
	{
		return total;
	}
	double statistician::mean() const
	{
		return(total/count);
	}
	double statistician::minimum() const
	{
		assert(count > 0);
		return min;
	}
	double statistician::maximum() const
	{
		assert(count > 0);
		return max;
	}

	// NON-MEMBER functions for the statistician class:
	// statistician operator +(const statistician& s1, const statistician& s2)
	// 	Postcondition: The statistician that is returned contains all them numbers of the sequences of s1 and s2.
	// statistician operator *(double scale, const statistician& s)
	// 	Postcondition: The statistician that is returned contains the same numbers that s does, but each number has been multiplied by the scale number.
	// bool operator ==(const statistician& s1, const statistician& s2)
	// 	Postcondition: The return value is true if s1 and s2 have the zero length. Also, if the length is greater than zero, then s1 and s2 must have the same length, the same mean, the same minimum, the same maximum, and the same sum.
	
	statistician operator +(const statistician& s1, const statistician& s2)
	{
		statistician s3; // creates object
		s3.count = s1.count + s2.count; // updates the count
		
		if(s1.min < s2.min) // s3 is given the smaller of the two minimums
			s3.min = s1.min;
		else
			s3.min = s2.min;
		if(s1.max > s2.max) // s3 is given the larger of the two maximums
			s3.max = s1.max;
		else
			s3.max = s2.max;

		s3.total = s1.total + s2.total;
		return s3;
	}

	statistician operator *(double scale, const statistician& s)
	{
		statistician s1; // creates object
		s1.count = s.count; // updates the count
		if(scale > 0) // positive scale - largest and smallest stay the same
		{
			s1.min = s.min * scale;
	 		s1.max = s.max * scale;
		}
		else // negative scale - largest and smallest are switched
		{
			s1.min = s.max * scale;
			s1.max = s.min * scale;
		}
		s1.total = s.total * scale;
		return s1;
	}

	bool operator ==(const statistician& s1, const statistician& s2)
	{
		if(s1.length() == 0 & s2.length() == 0) // returns true if empty
			return true;
		else if(s1.length() == s2.length() && s1.minimum() == s2.minimum() && s1.mean() == s2.mean() && s1.maximum() == s2.maximum()) // returns true if the length, min, max, and mean are all the same
			return true;
		return false;
	}
}

