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
	return &nodes;
}

dom::Node *		Node_Impl::getFirstChild(void)
{
	return *nodes.begin();
}

dom::Node *		Node_Impl::getLastChild(void)
{
	return *(--nodes.end());
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
	if (newChild->getOwnerDocument() != getOwnerDocument())
		throw dom::DOMException(dom::DOMException::WRONG_DOCUMENT_ERR, "New Child is not a part of this document.");

	if (newChild->getParentNode() != 0)
		newChild->getParentNode()->removeChild(newChild);

	if (refChild == 0)
	{
		nodes.push_back(newChild);
		(dynamic_cast<Node_Impl *>(newChild))->setParent(this);
		return newChild;
	}

	dom::NodeList::iterator	index	= nodes.find(refChild);

	if (index == nodes.end())
		throw dom::DOMException(dom::DOMException::NOT_FOUND_ERR, "Reference Child is not a child of this node.");

	nodes.insert(++index, newChild);
	(dynamic_cast<Node_Impl *>(newChild))->setParent(this);

	return newChild;
}

dom::Node *		Node_Impl::replaceChild(dom::Node * newChild, dom::Node * oldChild)
{
	if (newChild->getOwnerDocument() != getOwnerDocument())
		throw dom::DOMException(dom::DOMException::WRONG_DOCUMENT_ERR, "New Child is not a part of this document.");

	if (newChild->getParentNode() != 0)
		newChild->getParentNode()->removeChild(newChild);

	dom::NodeList::iterator	index	= nodes.find(oldChild);

	if (index == nodes.end())
		throw dom::DOMException(dom::DOMException::NOT_FOUND_ERR, "Old Child is not a child of this node.");

	nodes.insert(index, newChild);
	(dynamic_cast<Node_Impl *>(newChild))->setParent(this);
	(dynamic_cast<Node_Impl *>(*index))->setParent(0);
	nodes.erase(index);

	return oldChild;
}

dom::Node *		Node_Impl::removeChild(dom::Node * oldChild)
{
	dom::NodeList::iterator	index	= nodes.find(oldChild);

	if (index == nodes.end())
		throw dom::DOMException(dom::DOMException::NOT_FOUND_ERR, "Old Child is not a child of this node.");

	(dynamic_cast<Node_Impl *>(*index))->setParent(0);
	nodes.erase(index);

	return oldChild;
}

dom::Node *		Node_Impl::appendChild(dom::Node * newChild)
{
	if (newChild->getOwnerDocument() != getOwnerDocument())
		throw dom::DOMException(dom::DOMException::WRONG_DOCUMENT_ERR, "New Child is not a part of this document.");

	if (newChild->getParentNode() != 0)
		newChild->getParentNode()->removeChild(newChild);

	nodes.push_back(newChild);
	(dynamic_cast<Node_Impl *>(newChild))->setParent(this);

	return newChild;
}

bool			Node_Impl::hasChildNodes(void)
{
	return nodes.size() > 0;
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

//// Strategy pattern algorithm interface implementation
//int Node_Impl::serializePrettyAlgorithm(int indentationLevel, dom::OutputStream* out)
//{
//	// TODO: Add error
//	printf("Error: serialize function called on a node.\n");
//	return -1;
//}

//// Strategy pattern algorithm interface implementation
//void Node_Impl::serializeMinimalAlgorithm(dom::OutputStream* out)
//{
//	// TODO: Add error
//	printf("Error: serialize function called on a node.\n");
//}

void Node_Impl::prettyIndentation(int indentationLevel, dom::OutputStream * out)
{
	for (int i = 0; i < indentationLevel; i++)
		out->write("\t");
}

// Chain of Responsibility
void Node_Impl::handleEvent(std::string& request)
{
	printf("Request \"%s\" unhandled\n", request.c_str());
}

// prototype
dom::Node* Node_Impl::clone()
{
	dom::Node* clonedNode = new Node_Impl(name, nodeType);
	return clone(clonedNode);
}

// prototype
dom::Node* Node_Impl::clone(Node* clonedNode)
{
	clonedNode->setNodeValue(getNodeValue());
	dynamic_cast<Node_Impl*>(clonedNode)->setParent(getParentNode());
	dynamic_cast<Node_Impl*>(clonedNode)->document = getOwnerDocument();
	if (hasChildNodes())
	{
		for (dom::NodeList::iterator i = getChildNodes()->begin(); i != getChildNodes()->end(); i++)
		{
			dom::Node* clonedChild = (*i)->clone();
			dynamic_cast<Node_Impl*>(clonedChild)->setParent(0);
			clonedNode->appendChild(clonedChild);
		}
	}
	 
	return clonedNode;
}

int Node_Impl::calculateValue()
{
	if (hasChildNodes())
	{
		return getFirstChild()->calculateValue();
	}

	return 0;
}
