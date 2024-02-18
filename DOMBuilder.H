#ifndef DOMBUILDER_H
#define DOMBUILDER_H

#include "Document.H"
#include "Element.H"
#include "Attr.H"

// Document already has an abstract factory...just need the builder

class DOMBuilder
{
public:
	virtual void addElement(const std::string& tagName) = 0;
	virtual void addAttr(const std::string& name, const std::string& value) = 0;
	virtual void addText(const std::string& value) = 0;
	virtual void setParentAsCurrent() = 0;
	virtual dom::Node* getDoc() = 0;
	virtual dom::Node* getCurrent() = 0;
};

class DOMBuilder_Impl : public virtual DOMBuilder
{
private:
	dom::Document* doc;
	dom::Node* curNode;

public:
	DOMBuilder_Impl();

	virtual void addElement(const std::string& tagName);
	virtual void addAttr(const std::string& name, const std::string& value);
	virtual void addText(const std::string& value);
	virtual void setParentAsCurrent();
	virtual dom::Node* getDoc();
	virtual dom::Node* getCurrent();
};





#endif // !DOMBUILDER_H
