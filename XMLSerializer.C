#include "XMLSerializer.H"

#include "Document.H"
#include "Element.H"
#include "Attr.H"
#include "Text.H"

// Stratgy pattern context
void XMLSerializer::serializePretty(dom::Node * node)
{
	node->setSerializerPretty();
	indentationLevel = node->serialize(indentationLevel, out);
}

// Strategy pattern context
void XMLSerializer::serializeMinimal(dom::Node * node)
{
	node->setSerializerMinimal();
	node->serialize(0, out);
}
