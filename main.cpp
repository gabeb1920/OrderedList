/* Name: Gabriel Beedles
* Filename: main.cpp
* Date Modified: 11/4/2015
*
* Purpose: Contains a main function to test the implementation of an ordered linked list
*
*/

#include "OrderedList.h"
#include <iostream>
using namespace std;

int main() {

	OrderedList<int> intList;

	// Insert in reverse order to show that the list will insert ordered with duplicates
	for (int i = 10; i > 0; --i)
		for (int x = 0; x < 2; ++x)
			intList.insert(i);

	cout << intList << endl;

	// Demonstrate exists function
	ListNode<int> * int2;
	int2 = intList.exists(2);
	if (int2 != NULL)
		cout << "Found int 2 in OrderedList: " << int2->getData() << endl;

	// Demonstrate remove function with data
	intList.remove(2);
	cout << "Now with the first 2 removed:" << endl;
	cout << intList << endl;

	// Demonstrate deleteDups function
	intList.deleteDups();
	cout << "Now after deleteDups():" << endl;
	cout << intList << endl;

	int temp = 0;
	cin >> temp;

	return 0;
}