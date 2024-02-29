#include "assignment2.h"

int main() {
	// Variables
	stack myStack;
	Single_Linked_List<int> myList;
	int chosen_class = 0;
	int chosen_value;
	size_t index;
	size_t value;

	while (chosen_class != 1 && chosen_class != 2) {
		cout << "Would you like:" << endl << "1) A linked list" << endl << "2) A stack" << endl << endl;
		cin >> chosen_class;
	}

	// User has selected to see the Single_Linked_List
	if (chosen_class == 1) {

		// Show off empty() function
		cout << endl << myList.empty() << "! The list is empty!" << endl << endl;

		myList.push_back(1);
		myList.push_back(7);
		myList.push_back(5);
		myList.push_back(8);
		myList.push_back(2);
		myList.print_list();

		cout << endl << myList.empty() << "! The list is not empty!" << endl << endl;

		// Show off push_front()
		cout << "Input three values to push to the front!" << endl;
		for (size_t i = 0; i < 3; i++) {
			cin >> chosen_value;
			myList.push_front(chosen_value);
		}
		cout << endl;
		myList.print_list();

		// Show off push_back()
		cout << "Input three values to push to the back!" << endl;
		for (size_t i = 0; i < 3; i++) {
			cin >> chosen_value;
			myList.push_back(chosen_value);
		}
		cout << endl;
		myList.print_list();

		// Show off pop functions
		cout << "Popping one at the front, and one at the back!" << endl;
		myList.pop_front();
		myList.pop_back();
		myList.print_list();
		cout << "Doing it again!" << endl;
		myList.pop_front();
		myList.pop_back();
		myList.print_list();
		cout << endl << endl;

		// Show off .front() and .back() functions
		cout << myList.front() << " at the front!" << endl;
		cout << myList.back() << " at the back!" << endl << endl;

		// Show off .insert() function.
		for (size_t i = 0; i < 3; ++i) {
			cout << "Input index to insert at: ";
			cin >> index;
			cout << "Input new value to insert: ";
			cin >> value;
			myList.insert(index, value);
			myList.print_list();
			cout << endl;
		}

		// Show off .remove function.
		for (size_t i = 0; i < 3; ++i) {
			cout << "Input index to remove from: ";
			cin >> index;
			myList.remove(index);
			myList.print_list();
			cout << endl;
		}

		// Show off .find function
		for (size_t i = 0; i < 3; ++i) {
			cout << "Input value to search for: ";
			cin >> value;
			cout << "Found at " << myList.find(value) << endl;
			cout << endl;
		}
	}

	// User has selected to see the stack
	if (chosen_class == 2) {
		// Show off .empty() function
		cout << ".empty shows " << myStack.empty() << " for being empty." << endl << endl;

		// Show off .push() function
		for (size_t i = 0; i < 3; ++i) {
			cout << "Input value " << i + 1 << ": ";
			cin >> value;
			myStack.push(value);
		}
		myStack.print();
		cout << endl;

		// Show off .empty() function
		cout << ".empty shows " << myStack.empty() << " for being empty." << endl << endl;

		// Show off .pop() functoin
		cout << "Removing top..." << endl;
		myStack.pop();
		cout << "Removing top..." << endl;
		myStack.pop();

		cout << endl;
		myStack.print();

		// Expand the stack
		cout << endl << "Adding some values..." << endl;
		for (size_t i = 0; i < 10; ++i) {
			myStack.push(i + (i * (i + 4)));
		}
		myStack.print();

		// Show off .top() function
		cout << "Top of the stack is " << myStack.top() << endl;

		// Show off .get_average() function
		cout << "Average value in the stack (rounded down) is " << myStack.get_average() << endl;
	}
}