#ifndef NODEITER_H
#define NODEITER_H

#include <iterator>
#include <stack>

#include "Node.H"
#include "NodeList.H"
#include "CompositeNode.H"

namespace dom
{
	// Iterator Pattern Iterator Interface
	class NodeIter
	{
	public:
		virtual Node* start() = 0;
		virtual Node* next() = 0;
		virtual bool isDone() = 0;
	};
};

class Memento 
{
private:
	dom::Node* compositeArray[100];
	int indexArray[100];
	int index;

public:
	void initialize(dom::Node* root);
	void push(dom::Node* comp, int indexInput);
	bool pop();
	void getAndIncrement(dom::Node** comp, int* indexInput);
};

// Iterator Pattern Concrete Iterator
class NodeIter_Impl : public virtual dom::NodeIter
{
private:
	dom::CompositeNode* first;
	Memento memento;
	bool done;


public:
	NodeIter_Impl(dom::CompositeNode* first);
	~NodeIter_Impl() {}

	virtual dom::Node* start();
	virtual dom::Node* next();
	virtual bool isDone();
};

#endif // !NODEITER_H
