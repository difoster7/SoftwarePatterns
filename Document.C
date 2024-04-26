#include "Document.H"
#include "Element.H"
#include "Text.H"
#include "Attr.H"
#include "NodeList.H"
#include "SerializerVisitor.H"
#include "NamedNodeMap.H"


Document_Impl::Document_Impl(void) : Node_Impl("", dom::Node::DOCUMENT_NODE)
{
	Node_Impl::document	= this;

	textFlyweights = new NamedNodeMap_Impl(this);
	attrFlyweights = new NamedNodeMap_Impl(this);
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

void Document_Impl::setSerializerPretty()
{
	serializer = new DocumentSerializerPretty(this);
}

void Document_Impl::setSerializerMinimal()
{
	serializer = new DocumentSerializerMinimal(this);
}

int Document_Impl::serialize(int indentationLevel, dom::OutputStream* out)
{
	return serializer->serialize(indentationLevel, out);
}

dom::Node* Document_Impl::clone()
{
	dom::Node* clonedNode = new Document_Impl();

	if (!serializer)
	{
		if (dynamic_cast<DocumentSerializerPretty*>(serializer))
		{
			clonedNode->setSerializerPretty();
		}
		if (dynamic_cast<DocumentSerializerMinimal*>(serializer))
		{
			clonedNode->setSerializerMinimal();
		}
	}

	return Node_Impl::clone(clonedNode);
}

// Visitor Pattern : accept method
void Document_Impl::accept(SerializerVisitor* serialV)
{
	serialV->serializeDocument(this);
}

ElementFlyweight* Document_Impl::createElementFlyweight(const std::string& tagName)
{
	return new ElementFlyweight(tagName, this);
}

TextFlyweight* Document_Impl::createTextFlyweight(const std::string& data)
{
	TextFlyweight* text;

	if (textFlyweights->getNamedItem(data))
	{
		text = dynamic_cast<TextFlyweight*>(textFlyweights->getNamedItem(data));
	}
	else
	{
		text = new TextFlyweight(data, this);
		textFlyweights->push_back(text);
	}

	return text;
}

AttrFlyweight* Document_Impl::createAttrFlyweight(const std::string& name)
{
	AttrFlyweight* attr;

	if (attrFlyweights->getNamedItem(name))
	{
		attr = dynamic_cast<AttrFlyweight*>(attrFlyweights->getNamedItem(name));
	}
	else
	{
		attr = new AttrFlyweight(name, this);
		attrFlyweights->push_back(attr);
	}

	return attr;
}

//// Strategy pattern algorithm interface implementation
//int Document_Impl::serializePrettyAlgorithm(int indentationLevel, dom::OutputStream* out)
//{
//	out->write("<? xml version=\"1.0\" encoding=\"UTF-8\"?>");
//	out->write("\n");
//	return getDocumentElement()->serializePrettyAlgorithm(indentationLevel, out);
//}
//
//// Strategy pattern algorithm interface implementation
//void Document_Impl::serializeMinimalAlgorithm(dom::OutputStream* out)
//{
//	out->write("<? xml version=\"1.0\" encoding=\"UTF-8\"?>");
//	getDocumentElement()->serializeMinimalAlgorithm(out);
//}

int DocumentSerializer::serialize(int indentationLevel, dom::OutputStream* out)
{
	writeOpener(out);

	setNextSerializer();
	return doc->getDocumentElement()->serialize(indentationLevel, out);
}

void DocumentSerializerPretty::writeOpener(dom::OutputStream* out)
{
	out->write("<? xml version=\"1.0\" encoding=\"UTF-8\"?>");
	out->write("\n");
}

void DocumentSerializerPretty::setNextSerializer()
{
	dom::Node* foo = doc->getDocumentElement();
	doc->getDocumentElement()->setSerializerPretty();
}

void DocumentSerializerMinimal::writeOpener(dom::OutputStream* out)
{
	out->write("<? xml version=\"1.0\" encoding=\"UTF-8\"?>");
}

void DocumentSerializerMinimal::setNextSerializer()
{
	doc->getDocumentElement()->setSerializerMinimal();
}