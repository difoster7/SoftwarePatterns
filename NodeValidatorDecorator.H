#ifndef XMLVALIDATORDECORATOR_H
#define XMLVALIDATORDECORATOR_H

#include "Node.H"
#include "XMLValidator.H"
#include "NodeList.H"
#include "Document.H"
#include "Element.H"
#include "Attr.H"

/*
* NodeValidatorDecorator has the following roles:
* Decorator Pattern : Decorator
*/

class NodeValidatorDecorator : public virtual dom::Node
{
protected:
	XMLValidator* validator;
	Node* node;

public:
	NodeValidatorDecorator(XMLValidator* validator, Node* node) : validator(validator), node(node) {}
	
	virtual const std::string& getNodeName(void) { return node->getNodeName(); };
	virtual const std::string& getNodeValue(void) { return node->getNodeValue(); };
	virtual void			setNodeValue(const std::string& nodeValue) { return node->setNodeValue(nodeValue); };
	virtual short			getNodeType(void) { return node->getNodeType(); };
	virtual Node* getParentNode(void) { return node->getParentNode(); };
	virtual dom::NodeList* getChildNodes(void) { return node->getChildNodes(); };
	virtual Node* getFirstChild(void) { return node->getFirstChild(); };
	virtual Node* getLastChild(void) { return node->getLastChild(); };
	virtual Node* getPreviousSibling(void) { return node->getPreviousSibling(); };
	virtual Node* getNextSibling(void) { return node->getNextSibling(); };
	virtual dom::Document* getOwnerDocument(void) { return node->getOwnerDocument(); };
	virtual Node* insertBefore(Node* newChild, Node* refChild) { return node->insertBefore(newChild, refChild); };
	virtual Node* replaceChild(Node* newChild, Node* oldChild) { return node->replaceChild(newChild, oldChild); };
	virtual Node* removeChild(Node* oldChild) { return node->removeChild(oldChild); };
	virtual Node* appendChild(Node* newChild) { return node->appendChild(newChild); };
	virtual bool			hasChildNodes(void) { return node->hasChildNodes(); };
	virtual const std::string& getLocalName(void) { return node->getLocalName(); };

	//virtual int serializePrettyAlgorithm(int indentationLevel, dom::OutputStream* out) { return node->serializePrettyAlgorithm(indentationLevel, out); };	// Strategy Pattern Algorithm interface
	//virtual void serializeMinimalAlgorithm(dom::OutputStream* out) { return node->serializeMinimalAlgorithm(out); };	// Strategy Pattern Algorithm interface
	virtual void prettyIndentation(int indentationLevel, dom::OutputStream* out) { return node->prettyIndentation(indentationLevel, out); };

	virtual void setSerializerPretty() { node->setSerializerPretty(); };
	virtual void setSerializerMinimal() { node->setSerializerMinimal(); };
	virtual int serialize(int indentationLevel, dom::OutputStream* out) { return node->serialize(indentationLevel, out); };

	virtual void handleEvent(std::string& request) { return node->handleEvent(request); };

	virtual Node* clone() { return node->clone(); };
	virtual Node* clone(Node* clonedNode) { return node->clone(node); };


};

/*
* DocumentValidatorDecorator has the following roles:
* Decorator Pattern : Concrete Decorator
*/

class DocumentValidatorDecorator : public virtual NodeValidatorDecorator, public virtual dom::Document
{
private:
	dom::Document* doc;

public:
	DocumentValidatorDecorator(XMLValidator* validator, dom::Document* doc) : doc(doc), NodeValidatorDecorator(validator, doc) {};

	virtual dom::Element* createElement(const std::string& tagName) { return doc->createElement(tagName); };
	virtual dom::Text* createTextNode(const std::string& data) { return doc->createTextNode(data); };
	virtual dom::Attr* createAttribute(const std::string& name) { return doc->createAttribute(name); };
	virtual dom::Element* getDocumentElement() { return doc->getDocumentElement(); };

	virtual dom::Node* appendChild(Node* newChild);	// overriden decorated function

};

/*
* ElementValidatorDecorator has the following roles:
* Decorator Pattern : Concrete Decorator
*/

class ElementValidatorDecorator : public virtual NodeValidatorDecorator, public virtual dom::Element
{
private:
	dom::Element* element;

public:
	ElementValidatorDecorator(XMLValidator* validator, dom::Element* element) : element(element), NodeValidatorDecorator(validator, element) {};

	virtual const std::string& getAttribute(const std::string& name) { return element->getAttribute(name); };
	virtual dom::Attr* getAttributeNode(const std::string& name) { return element->getAttributeNode(name); };
	virtual dom::NodeList* getElementsByTagName(const std::string& tagName) { return element->getElementsByTagName(tagName); };
	virtual const std::string& getTagName(void) { return element->getTagName(); };
	virtual bool			hasAttribute(const std::string& name) { return element->hasAttribute(name); };
	virtual void			removeAttribute(const std::string& name) { return element->removeAttribute(name); };
	virtual dom::Attr* removeAttributeNode(dom::Attr* oldAttr) { return element->removeAttributeNode(oldAttr); };
	virtual void			setAttribute(const std::string& name, const std::string& value);	// overriden decorated function
	virtual dom::Attr* setAttributeNode(dom::Attr* newAttr);	// overriden decorated function
	virtual dom::Node* appendChild(Node* newChild);	// overriden decorated function

	virtual dom::NamedNodeMap* getAttributes(void) { return element->getAttributes(); };
	virtual bool			hasAttributes(void) { return element->hasAttributes(); };

	virtual dom::Element* getElement() { return element; };
};

#endif // !XMLVALIDATORDECORATOR_H
