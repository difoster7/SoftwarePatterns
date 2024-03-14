#ifndef CHANGEMANAGER_H
#define CHANGEMANAGER_H

#include <list>

#include "DOMBuilder.H"
#include "Observer.H"
#include "Node.H"

class ChangeManager
{
public:
	virtual void attachAll(Observer* obs) = 0;
	virtual void attachElement(Observer* obs) = 0;
	virtual void attachAttr(Observer* obs) = 0;
	virtual void attachText(Observer* obs) = 0;

	virtual void detachAll(Observer* obs) = 0;
	virtual void detachElement(Observer* obs) = 0;
	virtual void detachAttr(Observer* obs) = 0;
	virtual void detachText(Observer* obs) = 0;

	virtual void notify(dom::Node* node) = 0;
};

class ChangeManager_Impl : public virtual ChangeManager
{
private:
	inline static std::list<Observer*> eleList{};
	inline static std::list<Observer*> attrList{};
	inline static std::list<Observer*> textList{};

	std::list<Observer*>::iterator findMember(int list, Observer* obs);

public:
	ChangeManager_Impl() {}

	virtual void attachAll(Observer* obs);
	virtual void attachElement(Observer* obs);
	virtual void attachAttr(Observer* obs);
	virtual void attachText(Observer* obs);

	virtual void detachAll(Observer* obs);
	virtual void detachElement(Observer* obs);
	virtual void detachAttr(Observer* obs);
	virtual void detachText(Observer* obs);

	virtual void notify(dom::Node* node);
};

#endif // !CHANGEMANAGER_H
