#ifndef CHANGEMANAGER_H
#define CHANGEMANAGER_H

#include <list>

#include "DOMBuilder.H"
#include "Observer.H"
#include "Node.H"

// Observer pattern : abstract change manager
// Mediator pattern : abstract mediator
class ChangeManager
{
public:
	enum ChangeType
	{
		NEW_NODE,
		NODE_COMPLETE
	};

	virtual void registerObserver(ChangeType chg, Observer* obs) = 0;
	virtual void deregisterObserver(ChangeType chg, Observer* obs) = 0;

	virtual void notify(ChangeType chg, dom::Node* node) = 0;
};

// Observer pattern : concrete change manager
// Mediator pattern : concrete mediator
class ChangeManager_Impl : public virtual ChangeManager
{
private:
	inline static std::list<Observer*> newNodeObs{};
	inline static std::list<Observer*> nodeCompleteObs{};

	std::list<Observer*>::iterator findMember(ChangeType chg, Observer* obs);

public:
	ChangeManager_Impl() {}

	virtual void registerObserver(ChangeType chg, Observer* obs);
	virtual void deregisterObserver(ChangeType chg, Observer* obs);

	virtual void notify(ChangeType chg, dom::Node* node);
};

#endif // !CHANGEMANAGER_H
