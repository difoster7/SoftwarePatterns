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

	return nullptr;
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

DOMNamedNodeMap* DOMNodeAdapter::getAttributes() const
{
	if (nodeRef->getNodeType() != 2)
	{
		return nullptr;
	}
	
	//dom::Attr* attr = dynamic_cast<dom::Element>(nodeRef)->getAttributeNode();

	// convert attr to a DOMNamedNodeMap* and return - cannot implement without DOMNamedNodeMap interface
	return nullptr;
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

DOMNode* DOMNodeAdapter::cloneNode(bool deep) const
{
	DOMNode* returnNode = new DOMNodeAdapter();
	returnNode->setNodeValue(nodeRef->getNodeValue().c_str());
	return returnNode;
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

void DOMNodeAdapter::normalize()
{
}

bool DOMNodeAdapter::isSupported(const XMLCh* feature, const XMLCh* version) const
{
	return false;
}

const XMLCh* DOMNodeAdapter::getNamespaceURI() const
{
	return nullptr;
}

const XMLCh* DOMNodeAdapter::getPrefix() const
{
	return nullptr;
}

const XMLCh* DOMNodeAdapter::getLocalName() const
{
	return nullptr;
}

void DOMNodeAdapter::setPrefix(const XMLCh* prefix)
{
}

bool DOMNodeAdapter::hasAttributes() const
{
	return false;
}

bool DOMNodeAdapter::isSameNode(const DOMNode* other) const
{
	return false;
}

bool DOMNodeAdapter::isEqualNode(const DOMNode* arg) const
{
	return false;
}

void* DOMNodeAdapter::setUserData(const XMLCh* key, void* data, DOMUserDataHandler* handler)
{
	return nullptr;
}

void* DOMNodeAdapter::getUserData(const XMLCh* key) const
{
	return nullptr;
}

const XMLCh* DOMNodeAdapter::getBaseURI() const
{
	return nullptr;
}

short DOMNodeAdapter::compareDocumentPosition(const DOMNode* other) const
{
	return 0;
}

const XMLCh* DOMNodeAdapter::getTextContent() const
{
	return nullptr;
}

void DOMNodeAdapter::setTextContent(const XMLCh* textContent)
{
}

const XMLCh* DOMNodeAdapter::lookupPrefix(const XMLCh* namespaceURI) const
{
	return nullptr;
}

bool DOMNodeAdapter::isDefaultNamespace(const XMLCh* namespaceURI) const
{
	return false;
}

const XMLCh* DOMNodeAdapter::lookupNamespaceURI(const XMLCh* prefix) const
{
	return nullptr;
}

void* DOMNodeAdapter::getFeature(const XMLCh* feature, const XMLCh* version) const
{
	return nullptr;
}

void DOMNodeAdapter::release()
{
}
