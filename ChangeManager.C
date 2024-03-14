#include "ChangeManager.H"

// 0 to search eleList, 1 to search attrList, 2 to search textList
std::list<Observer*>::iterator ChangeManager_Impl::findMember(int list, Observer* obs)
{
	std::list<Observer*>::iterator iter = eleList.begin();

	switch (list) {
	case 0:
		for (iter = eleList.begin(); iter != eleList.end(); iter++) {
			if (*iter.operator->() == obs) {
				break;
			}
		}
		break;
	case 1:
		for (iter = attrList.begin(); iter != attrList.end(); iter++) {
			if (*iter.operator->() == obs) {
				break;
			}
		}
		break;
	case 2:
		for (iter = textList.begin(); iter != textList.end(); iter++) {
			if (*iter.operator->() == obs) {
				break;
			}
		}
		break;
	}

	return iter;
}

void ChangeManager_Impl::attachAll(Observer* obs)
{
	attachElement(obs);
	attachAttr(obs);
	attachText(obs);
}

void ChangeManager_Impl::attachElement(Observer* obs)
{
	if (findMember(0, obs) == eleList.end())
	{
		eleList.push_back(obs);
	}
}

void ChangeManager_Impl::attachAttr(Observer* obs)
{
	if (findMember(1, obs) == attrList.end())
	{
		attrList.push_back(obs);
	}
}

void ChangeManager_Impl::attachText(Observer* obs)
{
	if (findMember(2, obs) == textList.end())
	{
		textList.push_back(obs);
	}
}

void ChangeManager_Impl::detachAll(Observer* obs)
{
	detachElement(obs);
	detachAttr(obs);
	detachText(obs);
}

void ChangeManager_Impl::detachElement(Observer* obs)
{
	std::list<Observer*>::iterator i = findMember(0, obs);
	if (i != eleList.end())
	{
		eleList.erase(i);
	}
}

void ChangeManager_Impl::detachAttr(Observer* obs)
{
	std::list<Observer*>::iterator i = findMember(1, obs);
	if (i != attrList.end())
	{
		attrList.erase(i);
	}
}

void ChangeManager_Impl::detachText(Observer* obs)
{
	std::list<Observer*>::iterator i = findMember(2, obs);
	if (i != textList.end())
	{
		textList.erase(i);
	}
}

void ChangeManager_Impl::notify(dom::Node* node)
{
	std::list<Observer*>::iterator i;

	if (dynamic_cast<dom::Element*>(node))
	{
		for (i = eleList.begin(); i != eleList.end(); i++)
		{
			(*i)->update(node);
		}
	}

	if (dynamic_cast<dom::Attr*>(node))
	{
		for (i = eleList.begin(); i != eleList.end(); i++)
		{
			(*i)->update(node);
		}
	}

	if (dynamic_cast<dom::Text*>(node))
	{
		for (i = eleList.begin(); i != eleList.end(); i++)
		{
			(*i)->update(node);
		}
	}
}
