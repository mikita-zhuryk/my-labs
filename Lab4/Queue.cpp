#include "..\Lab4\Queue.h"
#include <cstring>
#include <iostream>
#pragma warning(disable: 4996)

using namespace std;

Queue::Queue() {
	head = nullptr;
	tail = nullptr;
}

Queue::Queue(Address address) {
	head = new QueueNode(address);
	tail = head;
}

Queue::Queue(const Queue& origin) {
	QueueNode* tmpPtr = origin.head;
	head = new QueueNode(*tmpPtr);
	tail = head;
	while (tmpPtr) {
		tail = new QueueNode(tmpPtr->address, tail, nullptr);
		tmpPtr = tmpPtr->nextNode;
	}
}

Queue::~Queue() {
	QueueNode* tmpPtr = head;
	while (tmpPtr)
	{
		head = head->nextNode;
		delete tmpPtr;
		tmpPtr = head;
	}
}

Queue::QueueNode::QueueNode(Address address, QueueNode* prevNode, QueueNode* nextNode) {
	this->address = address;
	this->prevNode = prevNode;
	this->nextNode = nextNode;
}

Queue::QueueNode::QueueNode(const QueueNode& origObj) {
	this->address = origObj.address;
	prevNode = origObj.prevNode;
	nextNode = origObj.nextNode;
}

Queue::QueueNode::~QueueNode() {
}

bool Queue::empty() {
	return (!head);
}

void Queue::show() {
	if (empty()) { cout << "Queue is empty.\n"; }
	else {
		QueueNode* tmpPtr = head;
		size_t count = 0;
		while (tmpPtr)
		{
			cout << count + 1 << ". " << tmpPtr->address.street << ", " << tmpPtr->address.house << ", " << tmpPtr->address.building << ", " << tmpPtr->address.flat << ".\n";
			count++;
			tmpPtr = tmpPtr->nextNode;
		}
		printf("Queue contains %d records.\n", count);
	}
}

void Queue::add(Address address) {
	if (empty()) {
		head = new QueueNode(address, tail);
		tail = head;
	}
	else {
		QueueNode* tmp = tail;
		tail = new QueueNode(address, tail);
		tmp->nextNode = tail;
	}
}

Queue::QueueNode Queue::pop() {
	if (empty()) { 
		cout << "Error. Queue is empty, nothing to delete.\n";
		return QueueNode(Address("\0", 0, 0, 0), 0, 0);
	}
	else {
		QueueNode tmp(*head);
		QueueNode* tmpPtr = head;
		head = head->nextNode;
		delete tmpPtr;
		return tmp;
	}
}

Address::Address() {
	street = new char[STRING_SIZE];
	street[0] = '\0';
	house = -1;
	building = -1;
	flat = -1;
}

Address::Address(const char* street, int house, int building, int flat) {
	if ((house < 0) || (building < 0) || (flat < 0) || (!street)) {
		throw invalid_argument("Address constructor error");
	}
	int length = strlen(street);
	this->street = new char[length + 1];
	this->street[length] = '\0';
	//strcpy_s(this->street, length, street);
	strcpy(this->street, street);
	this->building = building;
	this->flat = flat;
	this->house = house;
}

Address::Address(const Address& origObj) {
	int length = strlen(origObj.street);
	street = new char[length + 1];
	this->street[length] = '\0';
	//strcpy_s(street, length, origObj.street);
	strcpy(street, origObj.street);
	building = origObj.building;
	flat = origObj.flat;
	house = origObj.house;
}

Address& Address::operator=(const Address& origObj) {
	int length = strlen(origObj.street);
	street = new char[length + 1];
	street[length] = '\0';
	strcpy(street, origObj.street);
	house = origObj.house;
	building = origObj.building;
	flat = origObj.flat;
	return *this;
}

Address::~Address() {
	delete[] street;
}
