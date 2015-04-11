/* Name: Gabriel Beedles
* Filename: OrderedList.h
* Date Modified: 11/4/2015
*
* Purpose: Contains the definition of the template class ListNode and
* the template class OrderedList which is a doubly linked list of
* ordered ListNodes
*
*/

#include <iostream>

#ifndef _ListNode_
#define _ListNode_
template <class T>
class ListNode {
private:
	T data;
	ListNode * prev;
	ListNode * next;
public:
	// Constructors
	ListNode() {
		prev = NULL;
		next = NULL;
	}
	// Destructor
	~ListNode() {}
	// Set functions
	void setPrev(ListNode * newPrev) { prev = newPrev; }
	void setNext(ListNode * newNext) { next = newNext; }
	void setData(T newData) { data = newData; }
	// Get functions
	ListNode * getPrev() { return prev; }
	ListNode * getNext() { return next; }
	T getData() { return data; }
};
#endif

#ifndef _OrderedList_
#define _OrderedList_
template <class T>
class OrderedList {
private:
	ListNode<T> * head;
	ListNode<T> * tail;
public:
	// Constructors
	OrderedList() {
		head = NULL;
		tail = NULL;
	}
	OrderedList(OrderedList<T> & newOL);
	// Destructor
	~OrderedList();
	// Get functions
	ListNode<T> * begin() { return *head; }
	ListNode<T> * end() { return NULL; }
	ListNode<T> * exists(const T & data);
	// Set functions
	void insert(const T & newData);
	void remove(const T & oldData);
	// Overloaded Operators
	template <class U>
	friend std::ostream& operator<<(std::ostream& out, const OrderedList<U> rhs);
};

// OrderedList functions
// Constructors
// Copy constructor
template <class T>
OrderedList<T>::OrderedList(OrderedList<T> & newOL) {
	head = NULL;
	tail = NULL;

	ListNode<T> * temp = newOL.head;
	while (temp != NULL) {
		this->insert(temp->getData());
		temp = temp->getNext();
	}
} // OrderedList<T>::OrderedList(OrderedList<T> & newOL)

// Destructor
template <class T>
OrderedList<T>::~OrderedList() {
	ListNode<T> * current = head;
	while (current != NULL) {
		ListNode<T> * next = current->getNext();
		delete current;
		current = next;
	}
} // OrderedList<T>::~OrderedList()

// Get functions
template <class T>
ListNode<T> * OrderedList<T>::exists(const T & data) {

	ListNode<T> * currentNode = head;
	if (currentNode != NULL) {
		// Step through the list until we reach the end or find a
		// node that matches
		while (currentNode->getData() != data && currentNode
			!= NULL) {

			currentNode = currentNode->getNext();
		}
	}

	return currentNode;
} // ListNode<T> * OrderedList<T>::exists(const T & data)

// Set functions
template <class T>
void OrderedList<T>::insert(const T & newData) {
	ListNode<T> * temp = new ListNode<T>;
	temp->setData(newData);

	if (head == NULL) {
		head = temp;
		tail = temp;
	}
	else {
		ListNode<T> * current = head;
		while (current->getData() < newData &&
			current->getNext() != NULL)

			current = current->getNext();
		// This gives us either the node just after where the new node
		// will go or the last node
		// Last means the new node goes in after the current node and
		// is the new tail
		if (current->getNext() == NULL && current->getData() < newData) {
			// Set current next to point to the new node
			current->setNext(temp);
			// Set the new node prev to point to current
			temp->setPrev(current);
			// Set the tail to point to the new node
			tail = temp;
		}
		else {
			// Otherwise we insert the new node before the current node and
			// check if current was the head
			// Set the new nodes next to current
			temp->setNext(current);
			// Set the new node prev to current prev
			temp->setPrev(current->getPrev());
			// Set the next of the node previous to the current to
			// the new node
			// Check if current was the head
			if (head == current)
				head = temp;
			else {
				current = current->getPrev();
				current->setNext(temp);
				current = temp->getNext();
			}
			// Set current prev to the new node
			current->setPrev(temp);

		}
	}
} // void OrderedList<T>::insert(const T & newData)

template <class T>
void OrderedList<T>::remove(const T & oldData) {
	ListNode<T> * currentNode = head;
	if (currentNode != NULL) {
		// Step through the list until we reach the end or find a
		// node that matches
		while (currentNode->getData() != oldData && currentNode
			!= NULL) {

			currentNode = currentNode->getNext();
		}
	}
	if (currentNode != NULL) {
		ListNode<T> * previous = currentNode->getPrev();
		ListNode<T> * next = currentNode->getNext();
		previous->setNext(next);
		next->setPrev(previous);
		delete currentNode;
	}
} // void OrderedList<T>::remove(const T & oldData)

// Overloaded Operators
template <class T>
std::ostream& operator<<(std::ostream& out, const OrderedList<T> rhs) {
	ListNode<T> * currentNode = rhs.head;
	while (currentNode != NULL) {
		out << currentNode->getData() << std::endl;
		currentNode = currentNode->getNext();
	}

	return out;
} // std::ostream& operator<<(std::ostream& out, const OrderedList<T> rhs)
#endif