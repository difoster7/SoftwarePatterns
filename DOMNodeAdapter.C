#include "DOMNodeAdapter.H"
#include "DOMDocumentAdapter.H"

using namespace XERCES;

XERCES::DOMNodeAdapter::DOMNodeAdapter(dom::Node* node)
{
	nodeRef = node;
}

const XMLCh* DOMNodeAdapter::getNodeName() const
{
	return nodeRef->getNodeName().c_str();
}

const XMLCh* DOMNodeAdapter::getNodeValue() const
{
	return nodeRef->getNodeValue().c_str();
}

DOMNode::NodeType DOMNodeAdapter::getNodeType() const
{
	short nodeType = nodeRef->getNodeType();
	switch (nodeType)
	{
	case 0: return DOMNode::NodeType(ATTRIBUTE_NODE);
	case 1: return DOMNode::NodeType(DOCUMENT_NODE);
	case 2: return DOMNode::NodeType(ELEMENT_NODE);
	case 3: return DOMNode::NodeType(TEXT_NODE);
	}
}

DOMNode* DOMNodeAdapter::getParentNode() const
{
	return new DOMNodeAdapter(nodeRef->getParentNode());
}

DOMNodeList* DOMNodeAdapter::getChildNodes() const
{
	dom::NodeList* nl = nodeRef->getChildNodes();

	for (dom::NodeList::iterator i = nl->begin(); i != nl->end(); i++)
	{
		// add *i to a new DOMNodeList - cannot implement without the DOMNodeList interface
	}

	return nullptr;	// should return the created DOMNodeList
}

DOMNode* DOMNodeAdapter::getFirstChild() const
{
	return new DOMNodeAdapter(nodeRef->getFirstChild());
}

DOMNode* DOMNodeAdapter::getLastChild() const
{
	return new DOMNodeAdapter(nodeRef->getLastChild());
}

DOMNode* DOMNodeAdapter::getPreviousSibling() const
{
	return new DOMNodeAdapter(nodeRef->getPreviousSibling());
}

DOMNode* DOMNodeAdapter::getNextSibling() const
{
	return new DOMNodeAdapter(nodeRef->getNextSibling());
}

DOMDocument* DOMNodeAdapter::getOwnerDocument() const
{
	return new DOMDocumentAdapter(nodeRef->getOwnerDocument());
}

DOMNode* DOMNodeAdapter::insertBefore(DOMNode* newChild, DOMNode* refChild)
{ 
	dom::Node* domNewChild = dynamic_cast<DOMNodeAdapter*>(newChild)->getNodeRef();
	dom::Node* domRefChild = dynamic_cast<DOMNodeAdapter*>(refChild)->getNodeRef();
	return new DOMNodeAdapter(nodeRef->insertBefore(domNewChild, domRefChild));
}

DOMNode* DOMNodeAdapter::replaceChild(DOMNode* newChild, DOMNode* oldChild)
{
	dom::Node* domNewChild = dynamic_cast<DOMNodeAdapter*>(newChild)->getNodeRef();
	dom::Node* domOldChild = dynamic_cast<DOMNodeAdapter*>(oldChild)->getNodeRef();
	return new DOMNodeAdapter(nodeRef->replaceChild(domNewChild, domOldChild));
}

DOMNode* DOMNodeAdapter::removeChild(DOMNode* oldChild)
{
	dom::Node* domOldChild = dynamic_cast<DOMNodeAdapter*>(oldChild)->getNodeRef();
	return new DOMNodeAdapter(nodeRef->removeChild(domOldChild));
}

DOMNode* DOMNodeAdapter::appendChild(DOMNode* newChild)
{
	dom::Node* domNewChild = dynamic_cast<DOMNodeAdapter*>(newChild)->getNodeRef();
	return new DOMNodeAdapter(nodeRef->appendChild(domNewChild));
}

bool DOMNodeAdapter::hasChildNodes() const
{
	return nodeRef->hasChildNodes();
}

void DOMNodeAdapter::setNodeValue(const XMLCh* nodeValue)
{
	nodeRef->setNodeValue(nodeValue);
}

const XMLCh* DOMNodeAdapter::getLocalName() const
{
	return nodeRef->getLocalName().c_str();
}