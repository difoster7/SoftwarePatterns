#include "Attr.H"

Attr_Impl::Attr_Impl(const std::string & tagName, dom::Document * document) : Node_Impl(tagName, dom::Node::ATTRIBUTE_NODE)
{
	Node_Impl::document	= document;
}

Attr_Impl::Attr_Impl(const std::string & tagName, const std::string & value, dom::Document * document) :
  Node_Impl(tagName, dom::Node::ATTRIBUTE_NODE)
{
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

// Strategy pattern algorithm interface implementation
int Attr_Impl::serializePrettyAlgorithm(int indentationLevel, dom::OutputStream* out)
{
	out->write(" ");
	out->write(getName());
	out->write("=\"");
	out->write(getValue()); 
	out->write("\"");
	//*file << " " << getName() << "=\"" << getValue() << "\"";
	return indentationLevel;
}

// Strategy pattern algorithm interface implementation
void Attr_Impl::serializeMinimalAlgorithm(dom::OutputStream* out)
{
	out->write(" ");
	out->write(getName());
	out->write("=\"");
	out->write(getValue());
	out->write("\"");
	//*file << " " << getName() << "=\"" << getValue() << "\"";
}