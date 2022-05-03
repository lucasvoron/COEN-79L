// FILE: statistician.cpp
// CLASS IMPLEMENTED: statistician (see stats.h for documentation)

#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include "statistician.h"

using namespace std;

namespace coen79_lab2
{
	//Constructor
	statistician::statistician( )
    {
        //TO DO
        //In Constructor, initialize member variables' values
    }
    
    void statistician::next(double r)
    {
        //TO DO
        //Think about what variables you need to update when the next function is called
    }
    
    void statistician::reset( )
    {
        //TO DO
        //Used for initialzing variables
    }
    
    double statistician::mean( ) const
    {
        //TO DO
        //Only works when the sequence is not empty
    }
    
    double statistician::minimum( ) const
    {
        //TO DO
        //Only works when the sequence is not empty
    }
    
    double statistician::maximum( ) const
    {
        //TO DO
        //Only works when the sequence is not empty
    }
    
    //FRIEND function +
    statistician operator +(const statistician& s1, const statistician& s2)
    {
    	//TO DO
    	//The function returns a statistician object
    	//After combination, think about how to assign values to the returned object's member variables
    }
    
    //NON-MEMBER function ==
    bool operator ==(const statistician& s1, const statistician& s2)
    {
    	//TO DO
    	//2 situations:1. If at least one of the sequence is empty; 2. Both sequences are NOT empty
    }
    
    //FRIEND function *
    statistician operator *(double scale, const statistician& p)
    {
    	//TO DO
    	//The function returns a statistician object
    	//Pay attention to the scale, it could be either positive or negative       
        //Assume we have 4 and -2 added to the object
        //The total is 2
        //If the scale is 4, then the total will be 8, and if the scale is -4, the total will be -8
        //If the scale is 4, then the largest and tiniest will be the same, if the scale is -4, the largest becomes the tiniest and the tiniest becomes the largest
        //Therefore, you need to distinguish between these 2 situations
    }
}


