#include "Node.H"

Node_Impl::Node_Impl(const std::string & n, short type) : name(n), nodeType(type), parent(0), document(0)
{
}

Node_Impl::~Node_Impl()
{
}

const std::string &	Node_Impl::getNodeName(void)
{
	return name;
}

const std::string &	Node_Impl::getNodeValue(void)
{
	return value;
}

void			Node_Impl::setNodeValue(const std::string & nodeValue)
{
	value	= nodeValue;
}

short			Node_Impl::getNodeType(void)
{
	return nodeType;
}

dom::Node *		Node_Impl::getParentNode(void)
{
	return parent;
}

dom::NodeList *		Node_Impl::getChildNodes(void)
{
	throw dom::DOMException(dom::DOMException::HIERARCHY_REQUEST_ERR, "Child management functions unavailable for this node.");

	return nullptr;
}

dom::Node *		Node_Impl::getFirstChild(void)
{
	throw dom::DOMException(dom::DOMException::HIERARCHY_REQUEST_ERR, "Child management functions unavailable for this node.");

	return nullptr;
}

dom::Node *		Node_Impl::getLastChild(void)
{
	throw dom::DOMException(dom::DOMException::HIERARCHY_REQUEST_ERR, "Child management functions unavailable for this node.");

	return nullptr;
}

dom::Node *		Node_Impl::getPreviousSibling(void)
{
	return getSibling(-1);
}

dom::Node *		Node_Impl::getNextSibling(void)
{
	return getSibling(1);
}

dom::Document *		Node_Impl::getOwnerDocument(void)
{
	return document;
}

dom::Node *		Node_Impl::insertBefore(dom::Node * newChild, dom::Node * refChild)
{
	throw dom::DOMException(dom::DOMException::HIERARCHY_REQUEST_ERR, "Child management functions unavailable for this node.");

	return nullptr;
}

dom::Node *		Node_Impl::replaceChild(dom::Node * newChild, dom::Node * oldChild)
{
	throw dom::DOMException(dom::DOMException::HIERARCHY_REQUEST_ERR, "Child management functions unavailable for this node.");

	return nullptr;
}

dom::Node *		Node_Impl::removeChild(dom::Node * oldChild)
{
	throw dom::DOMException(dom::DOMException::HIERARCHY_REQUEST_ERR, "Child management functions unavailable for this node.");

	return nullptr;
}

dom::Node *		Node_Impl::appendChild(dom::Node * newChild)
{
	throw dom::DOMException(dom::DOMException::HIERARCHY_REQUEST_ERR, "Child management functions unavailable for this node.");

	return nullptr;
}

bool			Node_Impl::hasChildNodes(void)
{
	throw dom::DOMException(dom::DOMException::HIERARCHY_REQUEST_ERR, "Child management functions unavailable for this node.");

	return false;
}

const std::string &	Node_Impl::getLocalName(void)
{
	return name;
}

void Node_Impl::setParent(dom::Node * parent)
{
	this->parent	= parent;
}

dom::Node *		Node_Impl::getSibling(int direction)
{
	if (parent == 0)
		return 0;

	dom::NodeList::iterator	i	= parent->getChildNodes()->find(this);

	if (direction < 0)
	{
		if (i == parent->getChildNodes()->begin())
			return 0;
		else
			return *(--i);
	}
	else
	{
		i++;

		if (i == parent->getChildNodes()->end())
			return 0;
		else
			return *i;
	}
}