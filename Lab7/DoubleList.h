#pragma once
#include "List.h"

class DoubleList : public List {

	struct DoubleListNode {
		double data_;
		DoubleListNode* next;

		DoubleListNode(double);
	};

	DoubleListNode* head;

public:

	DoubleList();

	DoubleList(double);

	DoubleList(double*, double);

	DoubleList(const DoubleList&);

	~DoubleList();

	void print(ostream&) const;

	bool empty() const;

};