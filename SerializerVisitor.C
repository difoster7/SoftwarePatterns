#include "SerializerVisitor.H"

void PrettySerializerVistor::serializeDocument(dom::Document* doc)
{
	out->write("<? xml version=\"1.0\" encoding=\"UTF-8\"?>");
	out->write("\n");
	doc->getDocumentElement()->accept(this);
}

void PrettySerializerVistor::serializeElement(dom::Element* doc)
{
}

void PrettySerializerVistor::serializeAttr(dom::Attr* doc)
{
}

void PrettySerializerVistor::serializeText(dom::Text* doc)
{
}

void MinimalSerializerVistor::serializeDocument(dom::Document* doc)
{
}

void MinimalSerializerVistor::serializeElement(dom::Element* doc)
{
}

void MinimalSerializerVistor::serializeAttr(dom::Attr* doc)
{
}

void MinimalSerializerVistor::serializeText(dom::Text* doc)
{
}
