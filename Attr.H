#ifndef ATTR_H
#define ATTR_H

#include <string>

#include "Node.H"
#include "NodeFlyweight.H"

namespace dom
{
	class Document;
	class Element;

	/*
	* Attr roles
	* Factory Pattern : Product
	*/
	class Attr : public virtual Node
	{
	public:
		virtual ~Attr() {}

		virtual const std::string &	getName(void)				= 0;
		virtual const std::string &	getValue(void)				= 0;
		virtual void			setValue(const std::string & value)	= 0;
		virtual Element *		getOwnerElement(void)			= 0;
	};
};

class AttrSerializer
{
protected:
	dom::Attr* attr;

public:
	AttrSerializer(dom::Attr* attr) : attr(attr) {};
	int serialize(int indentationLevel, dom::OutputStream* out);
};

/*
* Attr_Impl roles
* Factory pattern : Concrete Product
* Strategy pattern : Concrete Strategy
* Strategy pattern : Context
* Prototype Pattern : Concrete Prototype
* Visitor Pattern : Concrete Element
*/
class Attr_Impl : public virtual dom::Attr, Node_Impl	// Factory method concrete product
{
private:
	AttrSerializer* serializer;

protected:
	Attr_Impl(const std::string& tagName, dom::Document* document);
	Attr_Impl(const std::string & tagName, const std::string & value, dom::Document * document);
public:
	friend class Document_Impl;
	friend class Element_Impl;

	virtual ~Attr_Impl();

	virtual const std::string &	getName(void);
	virtual const std::string &	getValue(void);
	virtual void			setValue(const std::string & value);
	virtual dom::Element *		getOwnerElement(void);
	
	virtual int serialize(int indentationLevel, dom::OutputStream* out);

	virtual dom::Node* clone();	// Prototype Pattern Clone Method

	//virtual int serializePrettyAlgorithm(int indentationLevel, dom::OutputStream* out);	// Strategy pattern algorithm interface implementation
	//virtual void serializeMinimalAlgorithm(dom::OutputStream* out);	// Strategy Pattern Algorithm interface implementation

	virtual void accept(SerializerVisitor* serialV);	// Visitor pattern : Accept Method

};

class AttrFlyweight : public virtual dom::Attr, public virtual Attr_Impl, public virtual NodeFlyweight_Impl 
{
protected:
	AttrFlyweight(const std::string& tagName, dom::Document* document) : Attr_Impl(tagName, document) {}

public:
	friend class Document_Impl;
};

#endif // ATTR_H
