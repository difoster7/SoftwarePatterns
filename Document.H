#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include "Node.H"

class ElementFlyweight;
class TextFlyweight;
class AttrFlyweight;


namespace dom
{
	class Element;
	class Text;
	class Attr;
	class NodeList;
	class NamedNodeMap;
	
	/* 
	* Document Class has the following roles
	* Factory Pattern : Creator Interface
	* Decorator Pattern : Component
	* Abstract Factory Pattern : Abstract Factory
	*/
	class Document : public virtual Node
	{
	public:
		virtual Element *	createElement(const std::string & tagName)	= 0;	// Factory pattern creator method
		virtual Text *		createTextNode(const std::string & data)	= 0;	// Factory pattern creator method
		virtual Attr *		createAttribute(const std::string & name)	= 0;	// Factory pattern creator method
		virtual Element *	getDocumentElement()				= 0;

		virtual ElementFlyweight* createElementFlyweight(const std::string& tagName) = 0;
		virtual TextFlyweight* createTextFlyweight(const std::string& data) = 0;
		virtual AttrFlyweight* createAttrFlyweight(const std::string& name) = 0;
	};
};

/*
* DocumentSerializer has the following roles
* Template Pattern : Abstract class
*/
class DocumentSerializer
{
protected:
	dom::Document* doc;

	virtual void writeOpener(dom::OutputStream* out) {};	// Template pattern primitive method
	virtual void setNextSerializer() {};	// Template pattern primitive method

public:
	DocumentSerializer(dom::Document* doc) : doc(doc) {};
	int serialize(int indentationLevel, dom::OutputStream* out);	// Template pattern template method
};

/* 
* Document_Impl class has the following roles
* Factory Pattern : Concrete Creator
* Strategy Pattern : Concrete Algorithm
* Strategy Pattern : Context
* Decorator Pattern : Concrete Component
* Abstract Facotry Pattern : Concrete Factory
* Prototype Pattern : Concrete prototype
* Visitor Pattern : Concrete Element
*/
class Document_Impl : public virtual dom::Document, public virtual Node_Impl
{
private:
	DocumentSerializer* serializer;

	dom::NamedNodeMap* textFlyweights;
	dom::NamedNodeMap* attrFlyweights;

public:
	Document_Impl(void);

	virtual ~Document_Impl();

	virtual dom::Element *	createElement(const std::string & tagName);	// Factory pattern concrete creator method
	virtual dom::Text *	createTextNode(const std::string & data);	// Factory pattern concrete creator method
	virtual dom::Attr *	createAttribute(const std::string & name);	// Factory pattern concrete creator method
	virtual dom::Element *	getDocumentElement();

	//virtual int serializePrettyAlgorithm(int indentationLevel, dom::OutputStream* out);	// Strategy pattern algorithm interface implementation
	//virtual void serializeMinimalAlgorithm(dom::OutputStream* out);	// Strategy Pattern Algorithm interface implementation

	virtual void setSerializerPretty();
	virtual void setSerializerMinimal();
	virtual int serialize(int indentationLevel, dom::OutputStream* out);
	
	virtual dom::Node* clone();	// prototype pattern clone method

	virtual void accept(SerializerVisitor* serialV);	// Visitor pattern : Accept Method

	virtual ElementFlyweight* createElementFlyweight(const std::string& tagName);
	virtual TextFlyweight* createTextFlyweight(const std::string& data);
	virtual AttrFlyweight* createAttrFlyweight(const std::string& name);
};

/*
* DocumentSerializerPretty has the following roles
* Template Pattern : Concrete class
*/
class DocumentSerializerPretty : public virtual DocumentSerializer
{
protected:
	virtual void writeOpener(dom::OutputStream* out);	// Template pattern primitive method
	virtual void setNextSerializer();	// Template pattern primitive method

public:
	DocumentSerializerPretty(dom::Document* doc) : DocumentSerializer(doc) {};
};

/*
* DocumentSerializerMinimal has the following roles
* Template Pattern : Concrete class
*/
class DocumentSerializerMinimal : public virtual DocumentSerializer
{
protected:
	virtual void writeOpener(dom::OutputStream* out);	// Template pattern primitive method
	virtual void setNextSerializer();	// Template pattern primitive method

public:

	DocumentSerializerMinimal(dom::Document* doc) : DocumentSerializer(doc) {};
};

#endif // DOCUMENT_H
