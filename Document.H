#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include "Node.H"

namespace dom
{
	class Element;
	class Text;
	class Attr;
	class NodeList;

	/* 
	* Document Class has the following roles
	* Factory Pattern : Creator Interface
	* Decorator Pattern : Component
	* Abstract Factory Pattern : Abstract Factory
	* Adapter Pattern : Adaptee
	*/
	class Document : public virtual Node
	{
	public:
		virtual Element *	createElement(const std::string & tagName)	= 0;	// Factory pattern creator method
		virtual Text *		createTextNode(const std::string & data)	= 0;	// Factory pattern creator method
		virtual Attr *		createAttribute(const std::string & name)	= 0;	// Factory pattern creator method
		virtual Element *	getDocumentElement()				= 0;
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
*/
class Document_Impl : public virtual dom::Document, public virtual Node_Impl
{
private:
	DocumentSerializer* serializer;

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
