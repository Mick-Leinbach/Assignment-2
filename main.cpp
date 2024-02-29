using namespace std;
#include <iostream>

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
};

int main() {
	Single_Linked_List<int> myList;

	myList.push_back(4);
	myList.print_list();

	myList.push_back(2);
	myList.print_list();

	myList.push_back(8);
	myList.print_list();

	myList.push_back(5);
	myList.print_list();
}