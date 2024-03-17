#ifndef OBSERVER_H
#define OBSERVER_H

#include "Node.H"

// Observer pattern : Abstract observer
class Observer
{
public:
	virtual void update(dom::Node* node) {}
};

// Observer pattern : Concrete observer
// Mediator pattern : colleague
class NewNodeObserver_Impl : public virtual Observer
{
public:
	NewNodeObserver_Impl();
	~NewNodeObserver_Impl();
	void update(dom::Node* node);
};

// Observer pattern : Concrete observer
// Mediator pattern : colleague
class NodeCompleteObserver_Impl : public virtual Observer
{
public:
	NodeCompleteObserver_Impl();
	~NodeCompleteObserver_Impl();
	void update(dom::Node* node);
};

#endif // !OBSERVER_H
