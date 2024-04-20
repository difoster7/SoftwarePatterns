#ifndef SERIALIZER_VISITOR_H
#define SERIALIZER_VISITOR_H

#include "OutputStream.H"
#include "Document.H"
#include "Element.H"
#include "Attr.H"
#include "Text.H"

class SerializerVisitor
{
protected:
	dom::OutputStream* out;

	SerializerVisitor(dom::OutputStream* out) : out(out) {}

public:
	virtual void serializeDocument(dom::Document* doc) = 0;
	virtual void serializeElement(dom::Element* doc) = 0;
	virtual void serializeAttr(dom::Attr* doc) = 0;
	virtual void serializeText(dom::Text* doc) = 0;

};

class PrettySerializerVistor : public virtual SerializerVisitor
{
private:
	int indentationLevel;

public:
	PrettySerializerVistor(dom::OutputStream* out) : SerializerVisitor(out) {}

	void serializeDocument(dom::Document* doc);
	void serializeElement(dom::Element* doc);
	void serializeAttr(dom::Attr* doc);
	void serializeText(dom::Text* doc);
};

class MinimalSerializerVistor : public virtual SerializerVisitor
{
public:
	MinimalSerializerVistor(dom::OutputStream* out) : SerializerVisitor(out) {}

	void serializeDocument(dom::Document* doc);
	void serializeElement(dom::Element* doc);
	void serializeAttr(dom::Attr* doc);
	void serializeText(dom::Text* doc);
};

#endif // !SERIALIZER_VISITOR_H
