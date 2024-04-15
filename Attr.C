#include "Attr.H"

Attr_Impl::Attr_Impl(const std::string & tagName, dom::Document * document) : Node_Impl(tagName, dom::Node::ATTRIBUTE_NODE)
{
	serializer = new AttrSerializer(this);
	Node_Impl::document	= document;
}

Attr_Impl::Attr_Impl(const std::string & tagName, const std::string & value, dom::Document * document) :
  Node_Impl(tagName, dom::Node::ATTRIBUTE_NODE)
{
	serializer = new AttrSerializer(this);
	Node_Impl::document	= document;
	setValue(value);
}

Attr_Impl::~Attr_Impl() {}

const std::string &	Attr_Impl::getName(void)
{
	return Node_Impl::getNodeName();
}

const std::string &	Attr_Impl::getValue(void)
{
	return Node_Impl::getNodeValue();
}

void			Attr_Impl::setValue(const std::string & value)
{
	Node_Impl::setNodeValue(value);
}

dom::Element *		Attr_Impl::getOwnerElement(void)
{
	return (dom::Element *)Node_Impl::getParentNode();
}

int Attr_Impl::serialize(int indentationLevel, dom::OutputStream* out)
{
	return serializer->serialize(indentationLevel, out);
}

// prototype pattern clone method
dom::Node* Attr_Impl::clone()
{
	dom::Node* clonedNode = new Attr_Impl(getName(), getValue(), getOwnerDocument());

	return Node_Impl::clone(clonedNode);
}

//// Strategy pattern algorithm interface implementation
//int Attr_Impl::serializePrettyAlgorithm(int indentationLevel, dom::OutputStream* out)
//{
//	out->write(" ");
//	out->write(getName());
//	out->write("=\"");
//	out->write(getValue()); 
//	out->write("\"");
//	return indentationLevel;
//}
//
//// Strategy pattern algorithm interface implementation
//void Attr_Impl::serializeMinimalAlgorithm(dom::OutputStream* out)
//{
//	out->write(" ");
//	out->write(getName());
//	out->write("=\"");
//	out->write(getValue());
//	out->write("\"");
//}

int AttrSerializer::serialize(int indentationLevel, dom::OutputStream* out)
{
	out->write(" ");
	out->write(attr->getName());
	out->write("=\"");
	out->write(attr->getValue());
	out->write("\"");
	return indentationLevel;
}
