// FILE: database.cpp
// CLASS implemented: database (see database.h for documentation)

// INVARIANT for the database ADT:
//   1. The items in the database are stored in a dynamic array, where each entry of the array includes
//      a company name, a pointer to the head of the linked list of products, and a
//      a pointer to the tail of the linked list of products
//   2. The number of slots in the array of companies is stored in member varibale aloc_slots
//   3. The number of used slots of the array of companies is stored in member varibale used_slots


#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "database.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif

using namespace std;

namespace coen79_lab7
{
    
    database::database(const size_type& initial_capacity) {
        used_slots = 0;
        aloc_slots = initial_capacity;
        company_array = new company[aloc_slots];
    }
    
    
    database::database(const database &src) {
        Debug("Copy constructor..." << std::endl);

        used_slots = src.used_slots;
	   aloc_slots = src.aloc_slots;
	   company_array = new company[aloc_slots];
	   for(int i = 0; i < used_slots; i++)
		   company_array[i] = src.company_array[i];
    }
    
    
    database& database::operator= (const database &rhs) {
        Debug("Assignment operator..." << std::endl);

        if(this == &rhs)
		   return *this;

	   company_array = NULL;
	   used_slots = rhs.used_slots;
	   aloc_slots = rhs.aloc_slots;
	   company_array = new company[aloc_slots];

	   for(int i = 0; i<rhs.used_slots; i++)
		   company_array[i] = rhs.company_array[i];

	   return *this;
    }
    
    
    database::~database() {
        company_array = NULL;
    }
    
    
    void database::reserve(size_type new_capacity) {
        Debug("Reserve..." << std::endl);

        if (new_capacity == aloc_slots)
	   {
		   cout << "memory is right size" << endl;
            return; // The allocated memory is already the right size.
	   }
        
        if (new_capacity < used_slots)
	   {
		   cout << "memory is already big enough" << endl;
            new_capacity = used_slots; // Can??t allocate less than we are using.
	   }

	   cout << "start" << endl;
        company *tmp_array = new company[new_capacity];
	   cout << "what the freak" << endl;
	   std::copy(company_array, company_array + used_slots, tmp_array);
	   cout << "ohmygod it was the copy" << endl;
	   company_array = NULL;
	   cout << "perhaps the delete was causing a ruckus" << endl;
	   company_array = tmp_array;
	   cout << "i hate my life" << endl;
	   aloc_slots = new_capacity;
	   cout << "why is my brain so smooth" << endl;
    }
    
    
    bool database::insert_company(const std::string &entry) {
        
        Debug("Insert company..." << std::endl);

        assert(entry.length() > 0);

	   cout << "B R U H" << endl;
        
        size_type pos = search_company(entry);

	   cout << "PROBLEM" << endl;
        
        // If you find a company that is false, because there are duplicates
        if (pos != COMPANY_NOT_FOUND) {
            return false;
        }
	   if(used_slots == aloc_slots)
	   {
		   cout << "reserve is being called" << endl;
		   reserve(aloc_slots+1);
	   }
	   company insert = company(entry);
	   company_array[used_slots] = insert;
	   used_slots++;
	   return true;
    }
    
    
    bool database::insert_item(const std::string &company, const std::string &product_name, const float &price) {
        Debug("Insert item..." << std::endl);

        assert(company.length() > 0 && product_name.length() > 0);

        size_type company_index = search_company(company);
	   if(company_index != COMPANY_NOT_FOUND)
	   {
		   company_array[company_index].insert(product_name, price);
		   used_slots++;
	   }
	   return false;
    }
    
    
    bool database::erase_company(const std::string &company) {
        
        size_type company_index = search_company(company);
        
        if(company_index != COMPANY_NOT_FOUND)
	   {
		   for(size_type i = company_index+1; i < used_slots-1; i++)
			   company_array[i-1] = company_array[i];
		   used_slots--;
		   return true;
	   }
	   else
		   return false;
    }
    
    
    bool database::erase_item(const std::string& cName, const std::string& pName) {
        
        assert(cName.length() > 0 && pName.length() > 0);

        size_type company_index = search_company(cName);
	   return company_array[company_index].erase(pName);
    }
    
    
    
    database::size_type database::search_company(const std::string& company) {
        assert(company.length() > 0);

	   for (size_type i = 0; i < used_slots; i++)
	   {
		   if(company_array[i].get_name() == company)
		   {
			   return i;
		   }
	   }
	   return COMPANY_NOT_FOUND;
    }
    
    
    bool database::print_items_by_company(const std::string& cName) {
        assert(cName.length() > 0);

        size_type c_index = search_company(cName);
        
        if (c_index == COMPANY_NOT_FOUND) {
            return false;
        }
        
        std::cout << "Printing the products of " << cName << ":"<< std::endl;
        company_array[c_index].print_items();
        std::cout << std::endl;
        
        return true;
    }
    
    
    void database::print_companies() {
        
        std::cout << "Company List" << std::endl;
        for (int i = 0; i < used_slots; i++) {
            std::cout << "- " << company_array[i].get_name() << std::endl;
        }
    }
}

#endif
