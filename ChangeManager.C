#include "ChangeManager.H"

// 0 to search eleList, 1 to search attrList, 2 to search textList
std::list<Observer*>::iterator ChangeManager_Impl::findMember(ChangeType chg, Observer* obs)
{
	std::list<Observer*>::iterator iter;

	if (chg == NEW_NODE)
	{
		for (iter = newNodeObs.begin(); iter != newNodeObs.end(); iter++) {
			if (*iter.operator->() == obs) {
				break;
			}
		}
	}
	else 
	{
		for (iter = nodeCompleteObs.begin(); iter != nodeCompleteObs.end(); iter++) {
			if (*iter.operator->() == obs) {
				break;
			}
		}
	}

	return iter;
}

void ChangeManager_Impl::registerObserver(ChangeType chg, Observer* obs)
{
	if (chg == NEW_NODE)
	{
		if (findMember(NEW_NODE, obs) == newNodeObs.end())
		{
			newNodeObs.push_back(obs);
		}
	}
	else
	{
		if (findMember(NODE_COMPLETE, obs) == nodeCompleteObs.end())
		{
			nodeCompleteObs.push_back(obs);
		}
	}

}

void ChangeManager_Impl::deregisterObserver(ChangeType chg, Observer* obs)
{
	if (chg == NEW_NODE)
	{
		if (findMember(NEW_NODE, obs) == newNodeObs.end())
		{
			newNodeObs.remove(obs);
		}
	}
	else
	{
		if (findMember(NODE_COMPLETE, obs) == nodeCompleteObs.end())
		{
			nodeCompleteObs.remove(obs);
		}
	}
}

void ChangeManager_Impl::notify(ChangeType chg, dom::Node* node)
{
	std::list<Observer*>::iterator i;

	if (chg == NEW_NODE)
	{
		for (i = newNodeObs.begin(); i != newNodeObs.end(); i++)
		{
			(*i)->update(node);
		}
	}
	else
	{
		for (i = nodeCompleteObs.begin(); i != nodeCompleteObs.end(); i++)
		{
			(*i)->update(node);
		}
	}

}
