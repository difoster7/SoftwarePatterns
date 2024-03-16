#ifndef CHANGEMANAGER_H
#define CHANGEMANAGER_H

#include <list>

#include "DOMBuilder.H"
#include "Observer.H"
#include "Node.H"

class ChangeManager
{
public:
	enum ChangeType
	{
		NEW_NODE,
		NODE_COMPLETE
	};

	virtual void registerNewNode(Observer* obs) = 0;
	virtual void registerNodeComplete(Observer* obs) = 0;

	virtual void notify(ChangeType chg, dom::Node* node) = 0;
};

class ChangeManager_Impl : public virtual ChangeManager
{
private:
	inline static std::list<Observer*> newNodeObs{};
	inline static std::list<Observer*> nodeCompleteObs{};

	std::list<Observer*>::iterator findMember(ChangeType chg, Observer* obs);

public:
	ChangeManager_Impl() {}

	virtual void registerNewNode(Observer* obs);
	virtual void registerNodeComplete(Observer* obs);

	virtual void notify(ChangeType chg, dom::Node* node);
};

#endif // !CHANGEMANAGER_H
