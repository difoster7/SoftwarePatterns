#ifndef TEXT_H
#define TEXT_H

#include <string>

#include "Node.H"
#include "NodeFlyweight.H"

namespace dom
{
	class Element;
	class Document;

	/* Class Text roles
	* Factory method : product
	*/
	class Text : public virtual Node
	{
	public:
		virtual ~Text()	{}

		virtual const std::string &	getName(void)							= 0;
		virtual const std::string &	getData(void)							= 0;
		virtual const std::string &	getValue(void)							= 0;
		virtual void			setData(const std::string & value)				= 0;
		virtual void			setValue(const std::string & value)				= 0;
		virtual int			getLength(void)							= 0;
		virtual const std::string &	substringData(int offset, int count)				= 0;
		virtual void			appendData(const std::string & arg)				= 0;
		virtual void			insertData(int offset, const std::string & arg)			= 0;
		virtual void			deleteData(int offset, int count)				= 0;
		virtual void			replaceData(int offset, int count, const std::string & arg)	= 0;
		virtual Text *			splitText(int offset)						= 0;
	};
};

/*
* TextSerializer has the following roles
* Template Pattern : Abstract class
*/
class TextSerializer
{
protected:
	dom::Text* text;

	virtual void writeData(int indentationLevel, dom::OutputStream* out) {};	// Template pattern primitive method

public:
	TextSerializer(dom::Text* text) : text(text) {};
	int serialize(int indentationLevel, dom::OutputStream* out);	// Template pattern template method
};

/*
* Text_Impl roles
* Factory Pattern : Concrete Product
* Strategy Pattern : Concrete Strategy
* Strategy Pattern : Context
* Prototype Pattern : Concrete Prototype
* Visitor Pattern : Concrete Element
* Interpreter Pattern : Terminal Expression
*/
class Text_Impl : public virtual dom::Text, Node_Impl
{
private:
	TextSerializer* serializer;

protected:
	Text_Impl(const std::string value, dom::Document * document);

public:
	friend class Document_Impl;

	virtual ~Text_Impl();

	virtual const std::string &	getName(void);
	virtual const std::string &	getData(void);
	virtual const std::string &	getValue(void);
	virtual void			setData(const std::string & value);
	virtual void			setValue(const std::string & value);
	virtual int			getLength(void);
	virtual const std::string &	substringData(int offset, int count);
	virtual void			appendData(const std::string & arg);
	virtual void			insertData(int offset, const std::string & arg);
	virtual void			deleteData(int offset, int count);
	virtual void			replaceData(int offset, int count, const std::string & arg);
	virtual dom::Text *		splitText(int offset);

	//virtual int serializePrettyAlgorithm(int indentationLevel, dom::OutputStream* out);	// strategy pattern algorithm interface implementation
	//virtual void serializeMinimalAlgorithm(dom::OutputStream* out);	// Strategy Pattern Algorithm interface implementation

	virtual void setSerializerPretty();
	virtual void setSerializerMinimal();
	virtual int serialize(int indentationLevel, dom::OutputStream* out);

	virtual Node* clone();	// Prototype patter clone method

	virtual void accept(SerializerVisitor* serialV);	// Visitor pattern : Accept Method

	virtual int calculateValue();	// Interpreter Pattern : Interpret Method

};

/*
* TextSerializerPretty has the following roles
* Template Pattern : Concrete class
*/
class TextSerializerPretty : public virtual TextSerializer
{
protected:
	virtual void writeData(int indentationLevel, dom::OutputStream* out);	// Template pattern primitive method

public:
	TextSerializerPretty(dom::Text* text) : TextSerializer(text) {};
};

/*
* TextSerializerMinimal has the following roles
* Template Pattern : Concrete class
*/
class TextSerializerMinimal : public virtual TextSerializer
{
protected:
	virtual void writeData(int indentationLevel, dom::OutputStream* out);	// Template pattern primitive method

public:
	TextSerializerMinimal(dom::Text* text) : TextSerializer(text) {};
};

// Flyweight Pattern : Concrete Flyweight
class TextFlyweight : public virtual dom::Text, public virtual Text_Impl, public virtual NodeFlyweight_Impl 
{
protected:
	TextFlyweight(const std::string value, dom::Document* document) : Text_Impl(value, document) {}

public: 
	friend class Document_Impl;

};

#endif // TEXT_H
