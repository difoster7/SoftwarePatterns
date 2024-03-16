#ifndef OBSERVER_H
#define OBSERVER_H

#include "Node.H"

class Observer
{
public:
	virtual void update(dom::Node* node) {}
};

class NewNodeObserver_Impl : public virtual Observer
{
public:
	NewNodeObserver_Impl();
	~NewNodeObserver_Impl();
	void update(dom::Node* node);
};

class NodeCompleteObserver_Impl : public virtual Observer
{
public:
	NodeCompleteObserver_Impl();
	~NodeCompleteObserver_Impl();
	void update(dom::Node* node);
};

#endif // !OBSERVER_H
