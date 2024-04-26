#include "NodeFlyweight.H"
#include "Document.H"

dom::Node * NodeFlyweight_Impl::findChild(dom::Node * parent, std::string name)
{
	dom::Node* parentMaybe;

	if (parent->hasChildNodes())
	{
		for (dom::NodeList::iterator i = parent->getChildNodes()->begin(); i != parent->getChildNodes()->end(); i++)
		{
			if (strcmp((*i)->getNodeName().c_str(), name.c_str()))
			{
				return *i;
			}

			if (parentMaybe = findChild(*i, name))
			{
				return parentMaybe;
			}
		}
	}

	return 0;
}

dom::Node* NodeFlyweight_Impl::getParentNode(void)
{
	return getParentNode(getNodeName());
}

dom::Node* NodeFlyweight_Impl::getParentNode(std::string name)
{
	dom::Node* parent;

	if (parent = findChild(getOwnerDocument(), name) )
	{
		return parent;
	}

	return 0;
}

void NodeFlyweight_Impl::setParent(dom::Node* parent)
{
}
