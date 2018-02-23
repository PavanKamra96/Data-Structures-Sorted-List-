/**
* Name: Pavan Kumar Kamra
* Date: 2017-11-18
* Course: BTP500
* Purpose: A assignment that works with doubly linked list, iterators, and sentinels. 
**/

#include <vector>
template <typename T>
// This is the sorted list class that defines the linked list and its functionalities. 
class SortedList{
	// This is a struct class for nodes that gives the blue print to how each node is suppose to be data and functionality wise. 
	struct Node
	{
		T data_;
		Node* next_;
		Node* prev_;
		
		Node(const T& data=T{},Node* nx=nullptr,Node* pr=nullptr)
		{
			data_ = data; 
			next_ = nx; 
			prev_ = pr; 
		}
	};
	
	Node* front_;
	Node* back_;
	int listSize; 

public:
	class const_iterator{
	friend class SortedList; 
		 
		 // overloaded constructor for const iterator. defines the current pointer to the node. 
		const_iterator(Node* n) 
		{
			curr_ = n; 
		}
	protected:
		Node* curr_;
	public:
		// default constructor that makes the current pointer to null. 
		const_iterator()
		{
			curr_ = nullptr; 
		}
		// this is a prefix operator that makes the current pointer point to the next. 
		// returns current object (*this)
		const_iterator operator++()
		{
			curr_ = curr_->next_;
			return *this; 
		}
		// this is a postfix operator that increments iterator so that it points to previous node in list.
		// return the previous node. 
		const_iterator operator++(int)
		{
			const_iterator old = *this; 
			curr_ = curr_->next_;
			return old; 
		}
		// this is a prefix operator that makes the current pointer point to the previous. return 
		// current object. 
		const_iterator operator--()
		{
			curr_ = curr_->prev_;
			return *this; 
		}
		//this is a prefix operator that increments iterator so that it points to previous node in list.
		//return previous node
		const_iterator operator--(int)
		{
			const_iterator old = *this; 
			curr_ = curr_->prev_;
			return old; 
		}
		// this checks if the two current pointers are the same 
		bool operator==(const_iterator rhs)
		{
			return curr_ == rhs.curr_; 
		}
		// this checks if the two current pointers are different
		bool operator!=(const_iterator rhs)
		{
			return curr_ != rhs.curr_;
		}
		// this obtains the data from the object. 
		const T& operator*()const
		{
			return curr_->data_;
		}
	};
	class iterator:public const_iterator{
		friend class SortedList;
		iterator(Node* n)
                {
			this->curr_ = n; 
		}
		
	public:
		// default constructor that makes the current pointer to null.
		iterator()
		{
			this->curr_=nullptr; 
		}
		// this is a prefix operator that makes the current pointer point to the next. 
		// returns current object (*this)
		iterator operator++()
		{
			this->curr_ = this->curr_->next_;
			return *this;
		}
		// this is a postfix operator that increments iterator so that it points to previous node in list.
		// return the previous node.
		iterator operator++(int)
		{
			iterator old = *this; 
			this->curr_ = this->curr_->next_;
			return old; 
		}
		// this is a prefix operator that makes the current pointer point to the previous. return 
		// current object. 
		iterator operator--()
		{
			this->curr_ = this->curr_->prev_;
			return *this;
		}
		//this is a prefix operator that increments iterator so that it points to previous node in list.
		//return previous node
		iterator operator--(int)
		{
			iterator old = *this; 
			this->curr_ = this->curr_->prev_;
			return old;
		}
		// obtains the data of the object. 
		T& operator*()
		{
			return this->curr_->data_;
		}
		
		const T& operator*()const
		{
			return this->curr_->data_;
		}
	};
	SortedList();
	~SortedList();
	SortedList(const SortedList& rhs);
	SortedList& operator=(const SortedList& rhs);
	SortedList(SortedList&& rhs);
	SortedList& operator=(SortedList&& rhs);
	// this is the beginning for the iterators. A starting point. 
	// it returns the first pointer. 
	iterator begin()
	{
		return iterator(front_->next_); 
	}
	// this is the ending of the iteration. A ending point.
	// it returns the last pointer. 
	iterator end()
	{
		return iterator(back_); 
	}
	// this is the beginning for the const iterators. A starting point. 
	// it returns the first pointer.
	const_iterator begin() const
	{
		return const_iterator(front_->next_);
	}
	// this is the ending of the const iteration. A ending point.
	// it returns the last pointer. 
	const_iterator end() const
	{
		return const_iterator(back_);
	}
	iterator insert(const T& data);
	iterator search(const T& data);
	const_iterator search(const T& data) const;
	iterator erase(iterator it);
	iterator erase(iterator first, iterator last);
	bool empty() const;
	int size() const;
};

/*
* This is the constructor and it creates a empty linked list with a front and back sentinel. 
*/
template <typename T>
SortedList<T>::SortedList()
{
	front_ = new Node(); // this is the front sentinel node 
	back_ = new Node(); // this is the back sentinel node 
	front_->next_ = back_;
	back_->prev_ = front_;
	listSize=0;	// this is the size of the linked list. 
}

/*
* This is the deconstructor that safely deletes the linked list out of memory. 
* There is no return.
*/
template <typename T>
SortedList<T>::~SortedList()
{
	Node* curr_ = front_;
	while(curr_)
	{
		Node* rm = curr_;
		curr_ = curr_->next_;
		delete rm;
		listSize--;
	}
}

/*
* a copy constructor is a constructor for creating a new object as a copy of an existing object. 
* There is no return; however, the current function (*this) is set to the object being copied. 
*/
template <typename T>
SortedList<T>::SortedList(const SortedList& rhs)
{
	listSize = 0;  
	front_ = new Node();
	back_ = new Node();
	front_->next_ = back_;
	back_->prev_ = front_;
	*this = rhs;
}

/*
* an assignment operator is equal ( = ), which assigns the values of its 
* right operand to the left operand. It returns *this or current object. 
*/
//assignment operator 
template <typename T>
SortedList<T>& SortedList<T>::operator=(const SortedList& rhs)
{
	if (this != &rhs)
	{
		//delete front_;
		listSize = 0; 
		front_ = nullptr; 
		front_ = new Node();
		back_ = new Node();
		front_->next_ = back_;
		back_->prev_ = front_;
		for (auto iter = rhs.begin(); iter != rhs.end(); iter++)
		{
			Node* curr_ = new Node (*iter, back_, back_->prev_);  
			back_->prev_->next_ = curr_; 
			back_->prev_ = curr_;
			listSize++; 
		}
	}
	return *this;
}

/*
* The move constructor moves the data from the right operand to the left operand. 
* There is no return but it does set *this to the left operand. 
*/
template <typename T>
SortedList<T>::SortedList(SortedList&& rhs)
{	
	front_ = new Node();
	back_ = new Node();
	listSize = 0; 
	front_->next_ = back_;
	back_->prev_ = front_; 
	*this = std::move(rhs);
}

/*
* The move assignment operator (=) the data from the right operand to the left operant.
* It returns the current *this object. 
*/
template <typename T>
SortedList<T>& SortedList<T>::operator=(SortedList&& rhs)
{
	if (this != &rhs) 
	{
		 Node* temp = new Node();
		temp = front_;
		front_ = rhs.front_;
		rhs.front_ = temp;

		temp = back_;
		back_ = rhs.back_;
		rhs.back_ = temp;
	}
	return *this; 
	
}

/*
* this function inserts a new node with data into the list before the node referred to by lines of code.
* function returns iterator to the newly inserted node.
* the line of code is allowed be end()
*/
template <typename T>
typename SortedList<T>::iterator SortedList<T>::insert(const T& data)
{		
	iterator iter;	
	Node* dummy = new Node(data);
	iter = begin();
	while (iter != end() && (*iter) < dummy->data_ )
	{
		iter++;
	}
	dummy->next_ = iter.curr_; 
	dummy->prev_ = iter.curr_->prev_; 
	iter.curr_->prev_->next_ = dummy; 
	iter.curr_->prev_ = dummy; 
	listSize++;
	return iterator(dummy);	
}

/*
* This is the search function that uses iterators to go through the list and locate the node with the same data,
* it returns either the iterator with the location of the data being searched or returns the end function.
*/
template <typename T>
typename SortedList<T>::iterator SortedList<T>::search(const T& data)
{
	iterator iter = begin(); 
	while (iter != end() &&  (*iter) != data)
	{
		iter++;
	}
	if (*iter == data)
	{
		return iter; 
	}
	else 
	{
		return end();
	}
	
}

/*
* This is the search function that uses const iterators to go through the list and locate the node with the same data,
* it returns either the const iterator with the location of the data being searched or returns the end function. 
*/
template <typename T>
typename SortedList<T>::const_iterator SortedList<T>::search(const T& data) const
{

	const_iterator iter = begin(); 
	while (iter != end() && *iter != data)
	{
		iter++;
	}
	if (*iter == data)
	{
		return iter; 
	}
	else
	{
		return end();
	}
		
}

/*
* This is the erase function that erases the node that the user asks to delete. 
* it returns the pointer for the iterator after the one it asked to delete. 
*/
template <typename T>
typename SortedList<T>::iterator SortedList<T>::erase(iterator it)
{
	iterator iter = it.curr_->next_; 
	

	it.curr_->prev_->next_ = iter.curr_; 
	it.curr_->next_->prev_ = it.curr_->prev_; 
	
	delete it.curr_;
    
	listSize--;
	return iter;
}

/*
* This function erases all the linked list nodes between the asked "first" and "last" iterator the user puts in
* it returns the last iterator after its done erasing the nodes. 
*/
template <typename T>
typename SortedList<T>::iterator SortedList<T>::erase(iterator first, iterator last)
{
	
	while (first != last) 
	{
		erase(first++);
	}
	return last; 
}

/*
* This function calls the size() function and checks if the linked list is empty or not
* it either returns true or false.
*/
template <typename T>
bool SortedList<T>::empty() const
{
	return size()==0; 
}

/*
* This size function just checks and returns the size of the linked list. 
* it returns the size of the linked list. 
*/
template <typename T>
int SortedList<T>::size() const
{
	return listSize; 
}
