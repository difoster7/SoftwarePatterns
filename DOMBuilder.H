#ifndef DOMBUILDER_H
#define DOMBUILDER_H

#include "Document.H"
#include "Element.H"
#include "Attr.H"

// DOMBuilder is the Builder Pattern Abstract Builder
class DOMBuilder
{
public:
	virtual void addElement(const std::string& tagName) = 0;
	virtual void addAttr(const std::string& name, const std::string& value) = 0;
	virtual void addText(const std::string& value) = 0;
	virtual void setParentAsCurrent() = 0;
	virtual dom::Node* getDoc() = 0;
};

// DOMBuilder_Impl has the following roles:
// Builder Pattern : Concrete Builder
// Abstract Factory : Pattern Client
// Monostate
class DOMBuilder_Impl : public virtual DOMBuilder
{
private:
	inline static dom::Document* doc = new Document_Impl();
	inline static dom::Node* curNode = doc;

public:
	DOMBuilder_Impl() {}

	virtual void addElement(const std::string& tagName);
	virtual void addAttr(const std::string& name, const std::string& value);
	virtual void addText(const std::string& value);
	virtual void setParentAsCurrent();
	virtual dom::Node* getDoc();
};

#endif // !DOMBUILDER_H
