//FILE: sequence.cpp
//CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
//
//
//  COEN 79
//  --- Farokh Eskafi, COEN, SCU ---
//
//
//INVARIANT for the sequence class
//  1. The number of items in the sequence is stored in the member variable "many_nodes"
//
//  2. For an empty sequence, we do not care what is stored in any of data and head_ptr
//      and tail_ptr point to NULL; for a non-empty sequence, the items stored in the
//      sequence can be accessed using head_ptr and tail_ptr and we don't care what is
//      stored in the rest of the data.
//
//  3. If there is a current item, then it lies in *cursor; if there is no
//     current item, then cursor* equals NULL.
//
//  4. If there is a previous item, then it lies in precursor*.  If there is no previous
//       item, then precursor equals NULL.


#include <iostream>
#include <algorithm> //provides copy function
#include <cassert> //for assert function
#include "sequence.h" //header file for class
#include "node.h" // provides node class

using namespace std; //For copy function

namespace coen79_lab6
{
    // Default private member variable initialization function.
    void sequence::init()
    {
        //Initializing pointers to NULL
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        //Initializiing many_nodes (or our counter) to 0
        many_nodes = 0;
    }

    //CONSTRUCTOR IMPLEMENTATION for default constructor
    sequence :: sequence ()
    {
        init();
    }

    //Copy Constructor
    sequence :: sequence(const sequence& source)
    {
        init();
        *this = source;
    }
	
    	sequence::~sequence()
	{
		list_clear(head_ptr);
		many_nodes = 0;
	}
	        
	void sequence::start()
	{
		if(head_ptr != NULL)
		{
			cursor = head_ptr;
			precursor = head_ptr;
		}
	}

	void sequence::end()
	{
    		cursor = tail_ptr;
        	if(head_ptr == tail_ptr)
			precursor = NULL;
	     else
		{
			precursor = head_ptr;
			while(precursor->link() != cursor)
				precursor = precursor->link();
		}
		return;
	}

	void sequence::advance()
	{
    		assert(is_item());
            
        	if(cursor == tail_ptr)
		{
			cursor = NULL;
			return;
		}

		precursor = cursor;
		cursor = cursor->link();
		return;
	}

	void sequence::insert(const value_type& entry)
	{
		if(head_ptr == NULL)
		{
			list_head_insert(head_ptr, entry);
			cursor = head_ptr;
			precursor = NULL;
			tail_ptr = head_ptr;
		}
		else if(is_item() && cursor == head_ptr)
		{
			list_head_insert(head_ptr, entry);
			cursor = head_ptr;
			precursor = NULL;
		}
		else if(is_item() && cursor != head_ptr)
		{
			list_insert(precursor, entry);
			cursor = precursor -> link();
		}
		else if(!is_item())
		{
			list_head_insert(head_ptr, entry);
			tail_ptr = precursor->link();
			cursor = head_ptr;
			precursor = NULL;
		}
		many_nodes++;
		return;
	}

	void sequence::attach(const value_type& entry)
	{
    		if(head_ptr == NULL)
		{
	    		list_head_insert(head_ptr, entry);
			cursor = head_ptr;
			precursor = NULL;
			tail_ptr = head_ptr;
		}
		
		else if(is_item() && many_nodes == 1)
		{
			list_insert(head_ptr, entry);
			precursor = head_ptr;
			tail_ptr = precursor->link();
			cursor = tail_ptr;
		}
		else if(is_item() && many_nodes > 1 && cursor == head_ptr)
		{
			list_insert(head_ptr, entry);
			precursor = head_ptr;
			cursor = precursor->link();
		}
		
		else if(is_item() && cursor != head_ptr)
		{
			if(cursor != tail_ptr)
			{
				list_insert(cursor, entry);
				advance();
			}
			else
			{
				list_insert(tail_ptr, entry);
				tail_ptr = cursor->link();
				precursor = cursor;
				cursor = tail_ptr;
			}
		}
		
		else if(!is_item() && many_nodes > 0)
		{
			list_insert(tail_ptr, entry);
			precursor = tail_ptr;
			cursor = precursor->link();
			tail_ptr = cursor;
		}
		many_nodes++;
		return;
	}

	void coen79_lab6::sequence::operator =(const sequence& source)
	{
     	if(this == &source)
			return;
		list_clear(head_ptr);
		many_nodes = 0;
		node* tmp_tail;
		list_copy(source.head_ptr, head_ptr,tmp_tail);
		cursor = head_ptr;
		tail_ptr = tmp_tail;
					          
		node* tmp = source.head_ptr;
		precursor = head_ptr;
		if(source.cursor == NULL)
		{
			cursor = NULL;
			precursor = tail_ptr;
		}
		else
		{	
			while(tmp != source.precursor)
			{
				tmp = tmp->link();
				precursor = precursor->link();
			}
			if(precursor != NULL)
				cursor = precursor->link();
		}
		many_nodes = source.many_nodes;        
	}

	coen79_lab6::sequence::size_type coen79_lab6::sequence::size() const
	{
		return many_nodes;
	}

	void coen79_lab6::sequence::remove_current()
	{
    		assert(is_item());
        	if(head_ptr->link() == NULL)
		{
			delete cursor;
			head_ptr = NULL;
			tail_ptr = NULL;
			precursor = NULL;
			cursor = NULL;
		}
		
		else if(cursor == head_ptr && head_ptr ->link() !=NULL)
		{
			cursor = head_ptr->link();
			list_head_remove(head_ptr);
			precursor = NULL;
		}
		
		else if (cursor == tail_ptr && many_nodes > 1)
		{
			tail_ptr = precursor;
			delete cursor;
			cursor = NULL;
			tail_ptr->set_link(NULL);
		}
		
		else if(cursor != head_ptr && cursor != tail_ptr)
		{
			precursor->set_link(cursor->link());
			delete cursor;
			cursor = precursor->link();
		}
		many_nodes--;
	}

	bool coen79_lab6::sequence::is_item() const
	{
		if(cursor != NULL)
			return true;
		else
			return false;			            
	}

	coen79_lab6::sequence::value_type coen79_lab6::sequence::current() const
	{
		assert(is_item() == true);
		return cursor->data();
	}
}
