#ifndef SERIALIZER_VISITOR_H
#define SERIALIZER_VISITOR_H

#include "OutputStream.H"
#include "Document.H"
#include "Element.H"
#include "Attr.H"
#include "Text.H"

// Visitor Pattern : Abstract Visitor
class SerializerVisitor
{
protected:
	dom::OutputStream* out;

	SerializerVisitor(dom::OutputStream* out) : out(out) {}

public:
	virtual void serializeDocument(dom::Document* doc) = 0;
	virtual void serializeElement(dom::Element* ele) = 0;
	virtual void serializeAttr(dom::Attr* attr) = 0;
	virtual void serializeText(dom::Text* text) = 0;

};

// Visitor Pattern : Concrete Visitor
class PrettySerializerVistor : public virtual SerializerVisitor
{
private:
	int indentationLevel;

public:
	PrettySerializerVistor(dom::OutputStream* out) : SerializerVisitor(out) {}

	void serializeDocument(dom::Document* doc);
	void serializeElement(dom::Element* ele);
	void serializeAttr(dom::Attr* attr);
	void serializeText(dom::Text* text);
};

// Visitor Pattern : Concrete Visitor
class MinimalSerializerVistor : public virtual SerializerVisitor
{
public:
	MinimalSerializerVistor(dom::OutputStream* out) : SerializerVisitor(out) {}

	void serializeDocument(dom::Document* doc);
	void serializeElement(dom::Element* ele);
	void serializeAttr(dom::Attr* attr);
	void serializeText(dom::Text* text);
};

#endif // !SERIALIZER_VISITOR_H
