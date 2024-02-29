#pragma once
using namespace std;
#include <iostream>
#include <vector>
#include <random>

template <typename itemType>
struct DataNode {
	itemType data;
	DataNode* next;

	DataNode(const itemType& data, DataNode* next = nullptr) :
		data(data), next(next) {}
};

template <typename itemType>
class Single_Linked_List {
private:
	DataNode<itemType>* head;
	DataNode<itemType>* tail;
	size_t num_items;

public:

	Single_Linked_List(DataNode<itemType>* head = nullptr, DataNode<itemType>* tail = nullptr, size_t num_items = 0) :
		head(head), tail(tail), num_items(num_items) {}

	/*
		Pushes new data to the front of the list, which is held in a DataNode
		@ param constant itemType-by-reference "item" is the new data we're pushing to the front of the list
	*/
	void push_front(const itemType& item) {
		// Special case: Is the list empty?
		if (head == nullptr) {
			head = new DataNode<itemType>(item);
			tail = head;
		}
		// Special case: Is there exactly one item in the list?
		else if (head->next == nullptr) {
			DataNode<itemType>* newNode = new DataNode<itemType>(item);
			newNode->next = head;
			tail = head;
			head = newNode;
		}
		// Main case: The list already has multiple items
		else {
			DataNode<itemType>* newNode = new DataNode<itemType>(item);
			newNode->next = head;
			head = newNode;
		}
		++num_items;
	}

	/*
		Pushes new data to the back  of the list, which is held in a DataNode
		@ param constant itemType-by-reference "item" is the new data we're pushing to the back of the list
	*/
	void push_back(const itemType& item) {
		// Special case: Is the list empty?
		if (head == nullptr) {
			push_front(item);
		}
		// Main case: The list already has one or more items
		else {
			DataNode<itemType>* newNode = new DataNode<itemType>(item);
			tail->next = newNode;
			tail = newNode;
			++num_items;
		}
	}

	/*
		Removes the first item from the list
	*/
	void pop_front() {
		// Special case: Is the list empty?
		if (head == nullptr) {
			return;
		}
		// Special case: Is there exactly one item in the list?
		else if (head->next == nullptr) {
			DataNode<itemType>* markedNode = head;
			head = nullptr;
			tail = nullptr;
			delete markedNode;
			--num_items;
		}
		// Main case: There is more than one item in the list
		else {
			DataNode<itemType>* markedNode = head;
			head = head->next;
			delete markedNode;
			--num_items;
		}
	}

	/*
		Removes the last item from the list
	*/
	void pop_back() {
		// Special case: Is the list empty?
		if (tail == nullptr) {
			pop_front();
		}
		// Special case: Is there exactly one item in the list?
		else if (head->next == nullptr) {
			pop_front();
		}
		// Main case: There is more than one item in the list
		else {
			DataNode<itemType>* markedNode = tail;
			DataNode<itemType>* currentNode = head;
			while (currentNode->next != tail) {
				currentNode = currentNode->next;
			}
			tail = currentNode;
			tail->next = nullptr;
			delete markedNode;
			--num_items;
		}

	}

	/*
		Prints out contents of the list from first to last or "list empty" if it is empty.
	*/
	void print_list() {
		if (head != nullptr) {
			DataNode<itemType>* currentNode = head;
			while (currentNode != nullptr) {
				cout << currentNode->data << " ";
				currentNode = currentNode->next;
			}
			cout << endl;
		}
		else {
			cout << "List empty" << endl;
		}
	}

	/*
		@ returns By-reference itemType from the front of the list (head).
	*/
	itemType& front() {
		return head->data;
	}

	/*
		@ returns By-reference itemType from the back of the list (tail).
	*/
	itemType& back() {
		return tail->data;
	}

	/*
		@ returns True if the list is empty, false otherwise
	*/
	bool empty() {
		return (head == nullptr);
	}

	/*
		Inserts new item BEFORE item at a certain index into the list
		@ param index (size_t): Index that the new item will be at once it is inserted
		@ param item (constant by-reference itemType): New item being inserted
	*/
	void insert(size_t index, const itemType& item) {
		// Special case: Is the list empty? Or, is the new item being inserted at the beginning?
		if (empty() || index <= 0) {
			push_front(item);
		}
		// Main case: New item is not being inserted at the beginning.
		else {
			// Iterate through the list until index is found or end is reached
			DataNode<itemType>* currentNode = head;
			size_t i = 0;
			while (currentNode != nullptr && i < index - 1) {
				currentNode = currentNode->next;
				++i;
			}

			// If i is about to reach its index
			if (i == index - 1) {
				// If the index is at the very end
				if (currentNode->next == nullptr) {
					push_back(item);
				}
				// If the index wasn't at the very end
				else {
					DataNode<itemType>* newNode = new DataNode<itemType>(item);
					newNode->next = currentNode->next;
					currentNode->next = newNode;
					++num_items;
				}
			}
			// If index was beyond the end of the list
			else if (currentNode == nullptr) {
				push_back(item);
			}
		}
	}

	/*
		Removes item at a given index from the list. Returns false if that index is beyond the list's range.
		@ param index (size_t): Index of item to be removed
		@ returns booleon value. True if removal was successful. False if there were no items to remove or if the index given was out of range.
	*/
	bool remove(size_t index) {
		// Special case: Is the list empty?
		if (empty()) {
			return false;
		}
		// Special case: Are we removing the element from the front of the list?
		else if (index == 0) {
			pop_front();
			return true;
		}
		else {
			DataNode<itemType>* currentNode = head;
			size_t i = 0;
			while (currentNode->next != nullptr && i < index - 1) {
				currentNode = currentNode->next;
				++i;
			}

			if (currentNode->next == nullptr) {
				return false;
			}

			if (i <= index - 1) {
				if (currentNode->next->next != nullptr) {
					DataNode<itemType>* markedNode = currentNode->next;
					currentNode->next = markedNode->next;
					delete markedNode;
					--num_items;
					return true;
				}
				else {
					pop_back();
					return true;
				}
			}
		}
	}

	/*
		Returns num_items in list (size_t)
	*/
	size_t size() {
		return num_items;
	}

	/*
		Returns the index of the first instance of a given value in the linked list
		@ param item (constant by-reference itemType): The data we are searching for in the linked list
		@ returns size_t of the index of the querry. If the item isn't in the list anywhere, the function simply returns the size of the list.
	*/
	size_t find(const itemType& item) {
		size_t i = 0;
		DataNode<itemType>* currentNode = head;

		// Special case: Is the list empty?
		if (empty()) {
			return num_items;
		}
		// Special case: Is the very first node the item being searched for?
		else if (head->data == item) {
			return 0;
		}
		else {
			while (i < num_items && currentNode->data != item) {
				++i;
				currentNode = currentNode->next;
			}

			// If item not found
			if (i >= num_items) {
				return num_items;
			}

			// If item found
			if (currentNode->data == item) {
				return i;
			}
		}
	}
};

class stack {
private:
	vector<int> v;
public:
	/*
		@ Returns True if the "stack" is empty and False otherwise.
	*/
	bool empty() {
		return v.empty();
	}

	/*
		Pushes integer onto the stack.
		@ item (constant by-reference integer): Integer value to add to the top of the stack
	*/
	void push(const int& item) {
		v.push_back(item);
	}

	/*
		Removes item at the top of the "stack." Does nothing if the stack is empty.
	*/
	void pop() {
		if (!empty()) {
			v.pop_back();
		}
	}

	/*
		Returns top-most value of the stack. Returns -1 if the stack is empty.
	*/
	int top() {
		if (!empty()) {
			return v.back();
		}
		return -1;
	}

	/*
		If the stack isn't empty, returns the average value of all integers in the stack. Returns -1 if the stack is empty.
	*/
	int get_average() {
		if (!empty()) {
			int sum = 0;
			for (int i : v) {
				sum += i;
			}
			return sum / v.size();
		}
	}

	/*
		Print out the values in the stack. Print "Stack empty" if it's empty.
	*/
	void print() {
		if (!empty()) {
			for (int i : v) {
				cout << i << " ";
			}
			cout << endl;
		}
		else {
			cout << "Stack empty";
		}
	}
};