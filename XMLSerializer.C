#include "XMLSerializer.H"

#include "Document.H"
#include "Element.H"
#include "Attr.H"
#include "Text.H"

// Stratgy pattern context
void XMLSerializer::serializePretty(dom::Node * node)
{
	indentationLevel = node->serializePretty(indentationLevel, &file);
}

// Strategy pattern context
void XMLSerializer::serializeMinimal(dom::Node * node)
{
	node->serializeMinimal(&file);
}
