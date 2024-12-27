#ifndef LINKEDLIST
#define LINKEDLIST

#include<iostream>
using namespace std;
template<typename ElementType>

class LinkedList {

	private:
		//Creating the class node in this list
		//like that it is only being accessed by private attributr of linked list
		class Node {
			public:
			ElementType data;
			Node* next;

			Node()
			:next(0)
			{}

			Node(ElementType value)
			:next(0), data(value)
			{}
		};
	    int size;

    public:
	    typedef Node* NodePointer;

    private:
	    NodePointer first;

	public:


	    LinkedList();
	    LinkedList(const LinkedList& original);
	    ~LinkedList();
	    const LinkedList & operator=(const LinkedList& righthandside);
	    bool empty() const;
	    void insert(ElementType dataval);
	    void insertInFront(ElementType dataval);
	    void erase(int pos);
	    void eraseLast();
	    void display(ostream& out) const;
	    int nodecount()const;
	    void clear();
	    void insertbeforelast(ElementType x);
	    bool Search(ElementType x) const;
	    void inseraftern(int n, ElementType dataval);
	    void deletenth(int n);
	    LinkedList merge(LinkedList & l1, LinkedList & l2);
	    NodePointer getHead();
};

template<typename ElementType>
LinkedList<ElementType>::LinkedList() :size(0), first(0) {}

template<typename ElementType>
LinkedList<ElementType>::LinkedList(const LinkedList& original) : first(0), size(original.size)
{
	if (size == 0) return;

	NodePointer OrigPtr, LastPtr;
	first = new Node(original.first->data);
	LastPtr = first;
	OrigPtr = original.first->next;

	while (OrigPtr != 0) {
		LastPtr->next = new Node(OrigPtr->data);
		LastPtr = LastPtr->next;
		OrigPtr = OrigPtr->next;
	}
}

template<typename ElementType>
LinkedList<ElementType>::~LinkedList(){
	LinkedList::NodePointer prev = first, pointer;

	while (prev != 0) {
		pointer = prev->next;
		delete prev;
		prev = pointer;
	}
}

template<typename ElementType>
const LinkedList<ElementType> & LinkedList<ElementType>::operator=(const LinkedList<ElementType> & righthandside){
	{	size = righthandside.size;
		first = 0;
		if (size == 0)return *this;

		if (this != &righthandside) {
			this->~LinkedList();
			LinkedList::NodePointer OrigPtr, LastPtr;
			first = new Node(righthandside.first->data);
			LastPtr = first;
			OrigPtr = righthandside.first->next;

			while (OrigPtr != 0) {
				LastPtr->next = new Node(OrigPtr->data);
				OrigPtr = OrigPtr->next;
				LastPtr = LastPtr->next;
			}
		}
		return *this;
	}
}

template<typename ElementType>
bool LinkedList<ElementType>::empty() const{
	return first == 0;
}

template<typename ElementType>
void LinkedList<ElementType>::insert(ElementType dataval) {
	NodePointer newptr = new Node(dataval);
	newptr->next = nullptr;

	if (size == 0) {
		first = newptr;
	} else {
		NodePointer predptr = first;
		for (int i = 0; i < size - 1; i++) {
			predptr = predptr->next;
		}
		predptr->next = newptr;
	}
	size++;
}

template<typename ElementType>
void LinkedList<ElementType>::insertInFront(ElementType dataval) {
	NodePointer newptr = new Node(dataval);
	newptr->next = first;
	first = newptr;
	size++;
}

template<typename ElementType>
void LinkedList<ElementType>::erase(int pos){
	{
		if (pos < 0 || pos >= size) {
			cerr << "This position you want to delete/erase is invalid \n";
			return;
		}
		size--;

		LinkedList::NodePointer ptr, Predptr = first;
		if (pos == 0) {

			ptr = first;
			first = Predptr->next;
			delete ptr;

		}
		else {
			for (int i = 1;i < pos;i++)
				Predptr = Predptr->next;
			ptr = Predptr->next;
			Predptr->next = ptr->next;
			delete ptr;
		}
	}
}

template<typename ElementType>
void LinkedList<ElementType>::eraseLast() {
	NodePointer ptr = first;
	if (size == 0) {
		cerr << "This position you want to delete/erase is invalid \n";
	}
	else if (size == 1)
	{
		delete first;
		first = nullptr;
	}
	else
	{
		while (ptr->next->next != nullptr)
			ptr = ptr->next;
		delete ptr->next;
		ptr->next = nullptr;
	}
	size--;
}

//not used in this project
template<typename ElementType>
void LinkedList<ElementType>::display(ostream& out) const {
	LinkedList::NodePointer ptr = first;

	while (ptr != 0) {
		cout << ptr->data << " ";
		ptr = ptr->next;
	}
}

/*Note: the node count is not a static variable because if it were it would be
		stored within the node class and not the list, because different lists can have a different
		node count that is not sa7*/
//not used in this project
template<typename ElementType>
int LinkedList<ElementType>::nodecount()const{

	if (this->empty())
		return 0;
	NodePointer ptr = first;

	int count = 1;

	while (ptr->next != 0) {
		ptr = ptr->next;
		count++;

	}

	return count;
}

template<typename ElementType>
void LinkedList<ElementType>::clear() {
	NodePointer pred = first, ptr = first->next;
	while (ptr != nullptr) {
		pred = ptr;
		ptr = ptr->next;
		delete pred;
	}
	first = 0;
	size = 0;
}

//not used in this project
template<typename ElementType>
void LinkedList<ElementType>::insertbeforelast(ElementType x) {

	NodePointer ptr = first, newptr = new Node(x);

	while (ptr->next != 0) {
		ptr = ptr->next;
	}
	newptr->next = ptr->next;
	ptr->next = newptr;
}

template<typename ElementType>
bool LinkedList<ElementType>::Search(ElementType x) const
{

	NodePointer pred = first;

	if (pred->data == x) {
		return true;
	}
	while (pred!= 0) {
		if (pred->data == x) {
			return true;
		}
		pred = pred->next;
	}

	return false;
}

//not used in this project
template<typename ElementType>
void LinkedList<ElementType>::inseraftern(int n, ElementType dataval)
{


	NodePointer ptr = first, newptr = new Node(dataval);
	//the n is 0 based stating from the first node

	// if 0 it inserts after the 0t =h node which is the first node
	if (n == 0) {
		newptr->next = first->next;
		first->next = newptr;
	}
	else {

		for (int i = 0;i < n;i++) {
			ptr = ptr->next;
		}
		newptr->next = ptr->next;
		ptr->next = newptr;
	}
}

//not used in this project
template<typename ElementType>
void LinkedList<ElementType>::deletenth(int n){
	NodePointer ptr = first, pred = first;

	if (n == 0) {
		first = ptr->next;
		delete ptr;
	}
	else {
		for (int i = 1;i < n;i++) {
			pred = pred->next;
		}
		ptr = pred->next;
		pred->next = ptr->next;
		delete ptr;
	}
}

//not used in this project
template<typename ElementType>
LinkedList<ElementType> LinkedList<ElementType>::merge(LinkedList & l1, LinkedList & l2){
	{

		NodePointer l1ptr = l1.first, l2ptr = l2.first;


		LinkedList myfinal;


		int index = 0;
		while (l1ptr != 0 && l2ptr != 0) {

			if ((l1ptr->data) < (l2ptr->data)) {
				myfinal.insert(l1ptr->data, index);
				index++;
				l1ptr = l1ptr->next;
			}
			else {
				myfinal.insert(l2ptr->data, index);
				index++;
				l2ptr = l2ptr->next;
			}

		}

		while (l1ptr != 0) {
			myfinal.insert(l1ptr->data, index);
			index++;
			l1ptr = l1ptr->next;
		}

		while (l2ptr != 0) {
			myfinal.insert(l2ptr->data, index);
			l2ptr = l2ptr->next;
			index++;
		}


		return myfinal;
	}
}

template<typename ElementType>
typename LinkedList<ElementType>::NodePointer LinkedList<ElementType>::getHead() {
	return first;
}




#endif