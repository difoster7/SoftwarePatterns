#include "DOMNodeAdapter.H"
#include "DOMDocumentAdapter.H"

using namespace XERCES;

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
	DOMNode* returnNode = new DOMNodeAdapter();
	dom::Node* parent = nodeRef->getParentNode();
	returnNode->setNodeValue(parent->getNodeValue().c_str());
	return returnNode;
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
	DOMNode* returnNode = new DOMNodeAdapter();
	dom::Node* firstChild = nodeRef->getFirstChild();
	returnNode->setNodeValue(firstChild->getNodeValue().c_str());
	return returnNode;
}

DOMNode* DOMNodeAdapter::getLastChild() const
{
	DOMNode* returnNode = new DOMNodeAdapter();
	dom::Node* lastChild = nodeRef->getLastChild();
	returnNode->setNodeValue(lastChild->getNodeValue().c_str());
	return returnNode;
}

DOMNode* DOMNodeAdapter::getPreviousSibling() const
{
	DOMNode* returnNode = new DOMNodeAdapter();
	dom::Node* previousSibling = nodeRef->getPreviousSibling();
	returnNode->setNodeValue(previousSibling->getNodeValue().c_str());
	return returnNode;
}

DOMNode* DOMNodeAdapter::getNextSibling() const
{

	DOMNode* returnNode = new DOMNodeAdapter();
	dom::Node* nextSibling = nodeRef->getNextSibling();
	returnNode->setNodeValue(nextSibling->getNodeValue().c_str());
	return returnNode;
}

DOMDocument* DOMNodeAdapter::getOwnerDocument() const
{
	// the below code fails to compile due to DOMDocumentAdapter being an abstract class for some reason...
	/*
	DOMDocument* returnNode = new DOMDocumentAdapter();
	dom::Document* ownerDoc = nodeRef->getOwnerDocument();
	returnNode->setNodeValue(ownerDoc->getNodeValue().c_str());
	return returnNode;
	*/
	return nullptr;
}

DOMNode* DOMNodeAdapter::insertBefore(DOMNode* newChild, DOMNode* refChild)
{ 
	return nullptr;
}

DOMNode* DOMNodeAdapter::replaceChild(DOMNode* newChild, DOMNode* oldChild)
{
	// For these child management functions, cast the inputs to adaptee's, then use the reference node as inputs to 
	return nullptr;
}

DOMNode* DOMNodeAdapter::removeChild(DOMNode* oldChild)
{
	return nullptr;
}

DOMNode* DOMNodeAdapter::appendChild(DOMNode* newChild)
{
	return nullptr;
}

bool DOMNodeAdapter::hasChildNodes() const
{
	return false;
}

void DOMNodeAdapter::setNodeValue(const XMLCh* nodeValue)
{
}

const XMLCh* DOMNodeAdapter::getLocalName() const
{
	return nullptr;
}