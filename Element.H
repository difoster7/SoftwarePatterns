#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>

#include "Node.H"
#include "NamedNodeMap.H"
#include "Text.H";

namespace dom
{
	class Attr;
	class NodeList;
	class Document;

	/*
	* ELement Class has the following roles
	* Factory Pattern : Product
	* Decorator Pattern : Component
	*/
	class Element : public virtual Node
	{
	public:
		virtual ~Element() {}

		virtual const std::string &	getAttribute(const std::string & name)					= 0;
		virtual Attr *			getAttributeNode(const std::string & name)				= 0;
		virtual NodeList *		getElementsByTagName(const std::string & tagName)			= 0;
		virtual const std::string &	getTagName(void)							= 0;
		virtual bool			hasAttribute(const std::string & name)					= 0;
		virtual void			removeAttribute(const std::string & name)				= 0;
		virtual Attr *			removeAttributeNode(Attr * oldAttr)					= 0;
		virtual void			setAttribute(const std::string & name, const std::string & value)	= 0;
		virtual Attr *			setAttributeNode(Attr * newAttr)					= 0;

		virtual dom::NamedNodeMap *	getAttributes(void)							= 0;
		virtual bool			hasAttributes(void)							= 0;
	};
};

/*
* ElementSerializer has the following roles
* Template Pattern : Abstract class
*/
class ElementSerializer
{
protected:
	dom::Element* ele;

	virtual void writeOpener(int indentationLevel, dom::OutputStream* out) {};	// Template pattern primitive method
	virtual void setNextSerializerNodeMap(dom::NamedNodeMap::iterator i) {};	// Template pattern primitive method
	virtual void setNextSerializerNodeList(dom::NodeList::iterator i) {};	// Template pattern primitive method
	virtual void writeSpace(dom::OutputStream* out) {};	// Template pattern primitive method
	virtual void writeNewLine(dom::OutputStream* out) {};	// Template pattern primitive method
	virtual int incrementIndentationLevel(int indentationLevel) { return indentationLevel; };	// Template pattern primitive method
	virtual int decrementIndentationLevel(int indentationLevel) { return indentationLevel; };	// Template pattern primitive method
	virtual void writeCloser(int indentationLevel, dom::OutputStream* out) {};	// Template pattern primitive method

public:
	ElementSerializer(dom::Element* ele) : ele(ele) {};

	int serialize(int indentationLevel, dom::OutputStream* out);	// Template pattern template method
};

/*
* Element_Impl class has the following roles
* Factory Pattern : Concrete Product
* Strategy Pattern : Concrete strategy
* Strategy Pattern : Context
* Decorator Pattern : Concrete Component
* Chain of Responsibility : Concrete Handler
* Prototype Pattern : Concrete Prototype
* Visitor Pattern : Concrete Element
*/
class Element_Impl : public virtual dom::Element, Node_Impl
{
private:
	NamedNodeMap_Impl	attributes;

	bool hasAttributeByValue(const std::string& name);

	ElementSerializer* serializer;

protected:
	Element_Impl(const std::string & tagName, dom::Document * document);

public:
	friend class Document_Impl;
	friend class Element_Impl_Proxy;

	virtual ~Element_Impl();

	virtual const std::string &	getAttribute(const std::string & name);
	virtual dom::Attr *		getAttributeNode(const std::string & name);
	virtual dom::NodeList *		getElementsByTagName(const std::string & tagName);
	virtual const std::string &	getTagName(void);
	virtual bool			hasAttribute(const std::string & name);
	virtual void			removeAttribute(const std::string & name);
	virtual dom::Attr *		removeAttributeNode(dom::Attr * oldAttr);
	virtual void			setAttribute(const std::string & name, const std::string & value);
	virtual dom::Attr *		setAttributeNode(dom::Attr * newAttr);

	virtual dom::NamedNodeMap *	getAttributes(void)	{ return &attributes; }
	virtual bool			hasAttributes(void)	{ return attributes.size() > 0; }

	//virtual int serializePrettyAlgorithm(int indentationLevel, dom::OutputStream* out);	// Strategy pattern algorithm interface implementation
	//virtual void serializeMinimalAlgorithm(dom::OutputStream* out);	// Strategy Pattern Algorithm interface implementation

	virtual void setSerializerPretty();
	virtual void setSerializerMinimal();
	virtual int serialize(int indentationLevel, dom::OutputStream* out);

	virtual void handleEvent(std::string& request); // Chain of Responsibility

	virtual dom::Node* clone();	// Prototype Pattern Clone method

	virtual void accept(SerializerVisitor* serialV);	// Visitor pattern : Accept Method

};

class Element_Impl_Proxy : public virtual dom::Element, Node_Impl_Proxy
{
private:
	dom::Element* ele;	// reference to actual element when it needs to be constructed

	// required to create the real element
	const std::string& tagName;
	dom::Document* document;

	// required to resume parsing the XML when real element is needed
	int lineNumber;
	int docLevel;

	void createRealElement();

protected:
	Element_Impl_Proxy(const std::string& tagName, dom::Document* document) : tagName(tagName), document(document) {}

public:

	void setLineNumber(int lineNumber) { lineNumber = lineNumber; }
	void setDocLevel(int docLevel) { docLevel = docLevel; }

	// Node_Impl_Proxy overloads
	virtual const std::string& getNodeName(void);
	virtual const std::string& getNodeValue(void);
	virtual void			setNodeValue(const std::string& nodeValue);
	virtual short			getNodeType(void);
	virtual dom::Node* getParentNode(void);
	virtual dom::NodeList* getChildNodes(void);
	virtual dom::Node* getFirstChild(void);
	virtual dom::Node* getLastChild(void);
	virtual dom::Node* getPreviousSibling(void);
	virtual dom::Node* getNextSibling(void);
	virtual dom::Document* getOwnerDocument(void);
	virtual dom::Node* insertBefore(dom::Node* newChild, dom::Node* refChild);
	virtual dom::Node* replaceChild(dom::Node* newChild, dom::Node* oldChild);
	virtual dom::Node* removeChild(dom::Node* oldChild);
	virtual dom::Node* appendChild(dom::Node* newChild);
	virtual bool			hasChildNodes(void);
	virtual const std::string& getLocalName(void);

	virtual void setParent(dom::Node* parent);

	virtual void prettyIndentation(int indentationLevel, dom::OutputStream* out);

	virtual void setSerializerPretty();
	virtual void setSerializerMinimal();
	virtual int serialize(int indentationLevel, dom::OutputStream* out);

	// Element overloads
	virtual const std::string& getAttribute(const std::string& name);
	virtual dom::Attr* getAttributeNode(const std::string& name);
	virtual dom::NodeList* getElementsByTagName(const std::string& tagName);
	virtual const std::string& getTagName(void);
	virtual bool			hasAttribute(const std::string& name);
	virtual void			removeAttribute(const std::string& name);
	virtual dom::Attr* removeAttributeNode(dom::Attr* oldAttr);
	virtual void			setAttribute(const std::string& name, const std::string& value);
	virtual dom::Attr* setAttributeNode(dom::Attr* newAttr);

	virtual dom::NamedNodeMap* getAttributes(void);
	virtual bool			hasAttributes(void);
};

/*
* ElementSerializerPretty has the following roles
* Template Pattern : Concrete class
*/
class ElementSerializerPretty : public virtual ElementSerializer
{
protected:
	virtual void writeOpener(int indentationLevel, dom::OutputStream* out);	// Template pattern primitive method
	virtual void setNextSerializerNodeMap(dom::NamedNodeMap::iterator i);	// Template pattern primitive method
	virtual void setNextSerializerNodeList(dom::NodeList::iterator i);	// Template pattern primitive method
	virtual void writeSpace(dom::OutputStream* out);	// Template pattern primitive method
	virtual void writeNewLine(dom::OutputStream* out);	// Template pattern primitive method
	virtual int incrementIndentationLevel(int indentationLevel);	// Template pattern primitive method
	virtual int decrementIndentationLevel(int indentationLevel);	// Template pattern primitive method
	virtual void writeCloser(int indentationLevel, dom::OutputStream* out);	// Template pattern primitive method

public:
	ElementSerializerPretty(dom::Element* ele) : ElementSerializer(ele) {};
};

/*
* ElementSerializerMinimal has the following roles
* Template Pattern : Concrete class
*/
class ElementSerializerMinimal : public virtual ElementSerializer
{
protected:
	virtual void writeOpener(int indentationLevel, dom::OutputStream* out);	// Template pattern primitive method
	virtual void setNextSerializerNodeMap(dom::NamedNodeMap::iterator i);	// Template pattern primitive method
	virtual void setNextSerializerNodeList(dom::NodeList::iterator i);	// Template pattern primitive method
	virtual void writeCloser(int indentationLevel, dom::OutputStream* out);	// Template pattern primitive method

public:
	ElementSerializerMinimal(dom::Element* ele) : ElementSerializer(ele) {};
};

#endif // ELEMENT_H
