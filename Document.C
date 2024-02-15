#include "Document.H"
#include "Element.H"
#include "Text.H"
#include "Attr.H"
#include "NodeList.H"

Document_Impl::Document_Impl(void) : Node_Impl("", dom::Node::DOCUMENT_NODE)
{
	Node_Impl::document	= this;
}

Document_Impl::~Document_Impl() {}

// Factory pattern concrete creator
dom::Element *	Document_Impl::createElement(const std::string & tagName)
{
	return new Element_Impl(tagName, this);
}

// Factory pattern concrete creator
dom::Text *	Document_Impl::createTextNode(const std::string & data)
{
	return new Text_Impl(data, this);
}

// Factory pattern concrete creator
dom::Attr *	Document_Impl::createAttribute(const std::string & name)
{
	return new Attr_Impl(name, this);
}

dom::Element * Document_Impl::getDocumentElement()
{
	for (dom::NodeList::iterator i = getChildNodes()->begin(); i != getChildNodes()->end(); i++)
		if (dynamic_cast<dom::Element *>(*i.operator->()) != 0)
			return dynamic_cast<dom::Element *>(*i.operator->());

	return 0;
}

// Strategy pattern algorithm interface implementation
int Document_Impl::serializePrettyAlgorithm(int indentationLevel, dom::OutputStream* out)
{
	out->write("<? xml version=\"1.0\" encoding=\"UTF-8\"?>");
	out->write("\n");
	return getDocumentElement()->serializePrettyAlgorithm(indentationLevel, out);
}

// Strategy pattern algorithm interface implementation
void Document_Impl::serializeMinimalAlgorithm(dom::OutputStream* out)
{
	out->write("<? xml version=\"1.0\" encoding=\"UTF-8\"?>");
	getDocumentElement()->serializeMinimalAlgorithm(out);
}