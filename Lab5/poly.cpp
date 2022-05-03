// FILE: poly.cpp
//
// 
// 
//
//
// NOTE: current_degree is always equal to the largest exponent with a non-zero
//          coefficient. If all coeficients are 0.0, then current_degree is 0.

#include <iostream>
#include <iomanip>
#include <cassert>
#include <string.h>
#include <cmath>
#include <climits>
#include "poly.h"
#include "assert.h"

using namespace std;
using namespace coen79_lab5;

namespace coen79_lab5
{
	// CONSTRUCTOR
	polynomial::polynomial(double c ,unsigned int exponent)
	{
		size = 0; // set all values except for c equal to zero
		current_degree = 0;
		poly = NULL;
		reserve(exponent + 1);
		poly[exponent] = c;
	}

	polynomial::polynomial(const polynomial& source)
	{
		size = source.size; // copy of the source
		poly = new double[size];
		for(int i=0; i<size; i++)
			poly[i]=source.poly[i];
		current_degree = source.current_degree;
	}

	// DESTRUCTOR
	polynomial::~polynomial()
	{
		delete[] poly; // deletes the polynomial
	}

    	// HELPER FUNCTIONS
    	void polynomial::update_current_degree() 
	{
		for(int i=0; i<size; i++)
			if(poly[i] !=0)
				current_degree = i; // update the current degree to the highest exponent with a non-zero coefficient
	}

	// MODIFICATION MEMBER FUNCTIONS
	void polynomial::reserve(size_t number)
	{
		if(number > size) // guarantees that memory will only be allocated if the number is greater than the size
		{
			double *temp = poly;
			size = number;
			poly = new double[size];
			for(int i=0; i<size; i++)
				poly[i]=0;
			if(temp!=NULL)
			{
				for(int i = 0; i<=current_degree; i++)
					poly[i] = temp[i];
				delete[] temp;
			}
			current_degree = number-1;
		}
	}
	
	void polynomial::trim()
	{
		if(degree()!=0)
		{
			double *temp = new double[degree() +1]; // clears as much memory as possible meaning one higher than the degree
			std::copy(poly,poly+degree()+1,temp);
			delete[] poly;
			poly = temp;
			size = degree()+1;
		}
		else if(degree() == 0)
			delete[]poly;
	}

	void polynomial::assign_coef(double coefficient, unsigned int exponent)
	{
		if(exponent>current_degree)
			reserve(exponent+1);
		poly[exponent] = coefficient; // sets the coefficent for the specified exponent
		update_current_degree();
	}

    	void polynomial::add_to_coef(double amount, unsigned int exponent)
    	{
		if(exponent>current_degree)
			reserve(exponent+1);
        	poly[exponent] += amount; // adds the given amount to the specified coefficient of the specified exponent
		update_current_degree();
   	}

	void polynomial::clear()
	{
		for(int i = 0; i<size; ++i) // zero out all coeficients
			poly[i] = 0;
		current_degree = 0; // reset the current_degree
    	}

	// MODIFICATION OPERATORS for the polynomial class
	polynomial& polynomial::operator =(const polynomial& source)
	{
		if(this!=&source)
		{
			delete []poly;
			poly = new double[source.size];
			current_degree=source.current_degree;
			size = source.size;
			for(int i = 0; i<size; i++) 
				poly[i] = source.poly[i];
		}
		return *this;
	}
	polynomial& polynomial::operator =(double c)
	{
		clear();
		poly[0]=c;

		return *this;
	}

	// CONSTANT MEMBER FUNCTIONS
    	polynomial polynomial::antiderivative() const 
	{
		polynomial antiderivative;
		for(int i = (degree() + 1); i > 0; --i)
			if(i != 0)
				antiderivative.assign_coef((this->poly[i - 1])/i, i);
		return antiderivative;
    	}

	double polynomial::coefficient(unsigned int exponent) const
	{
		if(exponent > current_degree)
			return 0; // return 0 if the exponent is greater than current degree
		return poly[exponent];
    	}

    	double polynomial::definite_integral(double x0, double x1) const
	{
		return(antiderivative().eval(x1) - antiderivative().eval(x0));
    	}

	polynomial polynomial::derivative() const
	{
		polynomial derivative;
		for(int e = 0; e < current_degree + 1; ++e)
			derivative.assign_coef(poly[e + 1] * (e + 1), e);
		return derivative;
    	}

	double polynomial::eval(double x) const 
	{
       	double sum = 0;

		for(int i = 0; i <= this->degree(); ++i) // a specified value for x is given
			if(poly[i] != 0)
				sum += (poly[i] * pow(x,i));
		return sum;
    	}

    	bool polynomial::is_zero( ) const 
	{
		return(degree() == 0 && poly[0] == 0); // whether it is a zero polynomial
    	}

	unsigned int polynomial::next_term(unsigned int e) const 
	{
     	++e;

		while(e < current_degree + 1)
		{
			if(poly[e] != 0)
				return e; // return the next exponent value (array location) if it exists
			++e;
		}
		return 0; // otherwise return 0
    	}

	unsigned int polynomial::previous_term(unsigned int e) const
	{
        	//return the previous valid exponent
		//following loop skips over 0 coefficients until it finds the previous term in the array
		for(int i = e-1; i >= 0; --i) 
			if(poly[i] != 0)
				return i; //return the previous exponent value (array location) if it exists
			else
				return 0;
		return UINT_MAX;
    	}

    	// NON-MEMBER BINARY OPERATORS
    	polynomial operator +(const polynomial& p1, const polynomial& p2)
    	{
		polynomial added = p1; //set the polynomial to be returned equal to the first polynomial passed 
		int e = p2.degree();
		
		//loop through the second polynomial adding like terms together
		while(e != UINT_MAX)
		{
			added.add_to_coef(p2.coefficient(e), e);
			e = p2.previous_term(e);
		}
		return added;
    	}

    	polynomial operator -(const polynomial& p1, const polynomial& p2)
	{
		polynomial sub = p1;
		int e = p2.degree();
		
		while(e != UINT_MAX) 
		{
			sub.add_to_coef((p2.coefficient(e) * -1), e);
			e = p2.previous_term(e);
		}
		return sub;
    	}

    	polynomial operator *(const polynomial& p1, const polynomial& p2) {
		assert((p1.degree() + p2.degree()) <= polynomial::MAXIMUM_DEGREE); // for * we need to check the MAXIMUM_DEGREE
		polynomial multiplied; // polynomial that is returned

		for(int p1e = p1.degree(); p1e != UINT_MAX; p1e = p1.previous_term(p1e))
		{
			for(int p2e = p2.degree(); p2e != UINT_MAX; p2e = p2.previous_term(p2e))
			{
				//following if else statments will test if there is already a like term in the array or not
				if(multiplied.coefficient(p1e + p2e) == 0)
					multiplied.assign_coef((p1.coefficient(p1e) * p2.coefficient(p2e)), (p1e + p2e));
				else
					multiplied.add_to_coef((p1.coefficient(p1e) * p2.coefficient(p2e)), (p1e + p2e));
			}
		}
		return multiplied;
    	}

    	// NON-MEMBER OUTPUT FUNCTIONS
    	std::ostream& operator << (std::ostream& out, const polynomial& p)
    	{
		int e = p.degree();
		
		if(e > 0)
		{
			out <<  p.coefficient(e) << "x^" << e << " ";
			e = p.previous_term(e);

			while(e != UINT_MAX)
			{
				//each element will be tested for the degree to output correctly 
				if(e > 1) 
				{ 
					//if the degree n is greater than 1, the degree will be printed "^n"
					//also test each coefficient to print either a - or + between each term
					if(p.coefficient(e) < 0)
						out << " - " << (p.coefficient(e) * -1) << "x^" << e;
					else
						out << " + " << p.coefficient(e) << "x^" << e;
				}
				//if n = 1. do not print the degree, just the variable x
				else if (e == 1) {
					if(p.coefficient(e) < 0)
						out << " - " << (p.coefficient(e) * -1) << "x";
					else
						out << " + " << p.coefficient(e) << "x";
				}
				e = p.previous_term(e); //iterator
			}
		}
		if(p.coefficient(0) < 0)
			out << " - " << (p.coefficient(0) * -1); // final term we print jus the coefficient
		else if (p.coefficient(0) > 0)
			out << " + " << p.coefficient(0);
		return out;
    	}
}
