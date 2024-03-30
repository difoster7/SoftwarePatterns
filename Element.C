#include "Element.H"
#include "Attr.H"
#include "Document.H"

Element_Impl::Element_Impl(const std::string & tagName, dom::Document * document) : Node_Impl(tagName, dom::Node::ELEMENT_NODE),
  attributes(document)
{
	Node_Impl::document	= document;
}

Element_Impl::~Element_Impl()
{
}

const std::string &	Element_Impl::getAttribute(const std::string & name)
{
	for (dom::NodeList::iterator i = attributes.begin(); i != attributes.end(); i++)
	{
		dom::Attr * attr = dynamic_cast<dom::Attr *>(*i.operator->());

		if (attr->getName().compare(name) == 0)
			return attr->getValue();
	}

	static const std::string	empty_string("");
	return empty_string;
}

dom::Attr *		Element_Impl::getAttributeNode(const std::string & name)
{
	for (dom::NodeList::iterator i = attributes.begin(); i != attributes.end(); i++)
	{
		dom::Attr * attr = dynamic_cast<dom::Attr *>(*i.operator->());

		if (attr->getName().compare(name) == 0)
			return attr;
	}

	return 0;
}

dom::NodeList *		Element_Impl::getElementsByTagName(const std::string & tagName)
{
	dom::NodeList *	nodeList	= new dom::NodeList();

	for (dom::NodeList::iterator i = getChildNodes()->begin(); i != getChildNodes()->end(); i++)
	{
		dom::Element *	element;

		if ((element = dynamic_cast<dom::Element *>(*i.operator->())) && element->getTagName().compare(tagName)==0)
			nodeList->push_back(*i.operator->());
	}

	return nodeList;
}

const std::string &	Element_Impl::getTagName(void)
{
	return getNodeName();
}

bool			Element_Impl::hasAttribute(const std::string & name)
{
	for (dom::NodeList::iterator i = attributes.begin(); i != attributes.end(); i++)
	{
		dom::Attr * attr = dynamic_cast<dom::Attr *>(*i.operator->());

		if (attr->getName().compare(name) == 0)
			return true;
	}

	return false;
}

void			Element_Impl::removeAttribute(const std::string & name)
{
	for (dom::NodeList::iterator i = attributes.begin(); i != attributes.end(); i++)
	{
		dom::Attr * attr = dynamic_cast<dom::Attr *>(*i.operator->());

		if (attr->getName().compare(name) == 0)
		{
			attributes.erase(i);
			return;
		}
	}
}

dom::Attr *		Element_Impl::removeAttributeNode(dom::Attr * oldAttr)
{
	for (dom::NodeList::iterator i = attributes.begin(); i != attributes.end(); i++)
		if (*i.operator->() == oldAttr)
		{
			dom::Attr *	attribute	= (dom::Attr *)i.operator->();
			attributes.erase(i);
			return attribute;
		}

	throw dom::DOMException(dom::DOMException::NOT_FOUND_ERR, "Attribute not found.");
}

void			Element_Impl::setAttribute(const std::string & name, const std::string & value)
{
	for (dom::NodeList::iterator i = attributes.begin(); i != attributes.end(); i++)
	{
		dom::Attr * attr = dynamic_cast<dom::Attr *>(*i.operator->());

		if (attr->getName().compare(name) == 0)
		{
			attr->setValue(value);
			return;
		}
	}

	dom::Attr *	attribute;
	attributes.push_back(attribute = new Attr_Impl(name, value, dynamic_cast<Document_Impl *>(getOwnerDocument())));
	dynamic_cast<Node_Impl *>(dynamic_cast<Node *>(attribute))->setParent(this);
}

dom::Attr *		Element_Impl::setAttributeNode(dom::Attr * newAttr)
{
	if (newAttr->getOwnerDocument() != getOwnerDocument())
		throw dom::DOMException(dom::DOMException::WRONG_DOCUMENT_ERR, "Attribute not created by this document.");

	if (newAttr->getParentNode() != 0)
		throw dom::DOMException(dom::DOMException::INUSE_ATTRIBUTE_ERR, "Attribute in use by other element.");

	dom::Attr *	oldAttribute	= 0;

	for (dom::NodeList::iterator i = attributes.begin(); i != attributes.end(); i++)
		if (dynamic_cast<dom::Attr *>(*i)->getName().compare(newAttr->getName()) == 0)
		{
			oldAttribute	= (dom::Attr *)i.operator->();
			attributes.erase(i);
			break;
		}

	dynamic_cast<Node_Impl *>(dynamic_cast<Node *>(newAttr))->setParent(this);
	attributes.push_back(newAttr);
	return oldAttribute;
}

void Element_Impl::setSerializerPretty()
{
	serializer = new ElementSerializerPretty(this);
}

void Element_Impl::setSerializerMinimal()
{
	serializer = new ElementSerializerMinimal(this);
}

int Element_Impl::serialize(int indentationLevel, dom::OutputStream* out)
{
	return serializer->serialize(indentationLevel, out);
}

//// Strategy pattern algorithm interface implementation
//int Element_Impl::serializePrettyAlgorithm(int indentationLevel, dom::OutputStream* out)
//{
//
//	prettyIndentation(indentationLevel, out);
//	out->write("<");
//	out->write(getTagName());
//
//	int	attrCount = 0;
//
//	for (dom::NamedNodeMap::iterator i = getAttributes()->begin(); i != getAttributes()->end(); i++)
//	{
//		indentationLevel = (*i.operator->())->serializePrettyAlgorithm(indentationLevel, out);
//		attrCount++;
//	}
//
//	if (attrCount > 0)
//		out->write(" ");
//
//	if (getChildNodes()->size() == 0)
//	{
//		out->write("/>");
//		out->write("\n");
//	}
//	else
//	{
//		out->write(">");
//		out->write("\n");
//		indentationLevel++;
//
//		for (dom::NodeList::iterator i = getChildNodes()->begin(); i != getChildNodes()->end(); i++)
//		{
//			if (dynamic_cast<dom::Element*>(*i) != 0 || dynamic_cast<dom::Text*>(*i) != 0)
//			{
//				indentationLevel = (*i.operator->())->serializePrettyAlgorithm(indentationLevel, out);
//			}
//		}
//
//		indentationLevel--;
//		prettyIndentation(indentationLevel, out);
//		out->write("</");
//		out->write(getTagName());
//		out->write(">");
//		out->write("\n");
//	}
//
//	return indentationLevel;
//}
//
//// Strategy pattern algorithm interface implementation
//void Element_Impl::serializeMinimalAlgorithm(dom::OutputStream* out)
//{
//	out->write("<");
//	out->write(getTagName());
//
//	for (dom::NamedNodeMap::iterator i = getAttributes()->begin(); i != getAttributes()->end(); i++)
//	{
//
//		(*i.operator->())->serializeMinimalAlgorithm(out);
//	}
//
//	if (getChildNodes()->size() == 0)
//		out->write("/>");
//	else
//	{
//		out->write(">");
//
//		for (dom::NodeList::iterator i = getChildNodes()->begin(); i != getChildNodes()->end(); i++)
//		{
//			if (dynamic_cast<dom::Element*>(*i) != 0 || dynamic_cast<dom::Text*>(*i) != 0)
//			{
//				(*i.operator->())->serializeMinimalAlgorithm(out);
//			}
//		}
//		out->write("</");
//		out->write(getTagName());
//		out->write(">");
//	}
//}

int ElementSerializer::serialize(int indentationLevel, dom::OutputStream* out)
{
	writeOpener(indentationLevel, out);

	int attrCount = 0;

	for (dom::NamedNodeMap::iterator i = ele->getAttributes()->begin(); i != ele->getAttributes()->end(); i++)
	{
		setNextSerializerNodeMap(i);
		indentationLevel = (*i.operator->())->serialize(indentationLevel, out);
		attrCount++;
	}

	if (attrCount > 0)
	{
		writeSpace(out);
	}

	if (ele->getChildNodes()->size() == 0)
	{
		out->write("/>");
		writeNewLine(out);
	}
	else
	{
		out->write(">");
		writeNewLine(out);
		indentationLevel = incrementIndentationLevel(indentationLevel);

		for (dom::NodeList::iterator i = ele->getChildNodes()->begin(); i != ele->getChildNodes()->end(); i++)
		{
			if (dynamic_cast<dom::Element*>(*i) != 0 || dynamic_cast<dom::Text*>(*i) != 0)
			{
				setNextSerializerNodeList(i);
				indentationLevel = (*i.operator->())->serialize(indentationLevel, out);
			}
		}

		indentationLevel = decrementIndentationLevel(indentationLevel);
		writeCloser(indentationLevel, out);
	}

	return indentationLevel;
}

void ElementSerializerPretty::writeOpener(int indentationLevel, dom::OutputStream* out)
{
	ele->prettyIndentation(indentationLevel, out);
	out->write("<");
	out->write(ele->getTagName());
}

void ElementSerializerPretty::setNextSerializerNodeMap(dom::NamedNodeMap::iterator i)
{
	(*i.operator->())->setSerializerPretty();
}

void ElementSerializerPretty::setNextSerializerNodeList(dom::NodeList::iterator i)
{
	(*i.operator->())->setSerializerPretty();
}

void ElementSerializerPretty::writeSpace(dom::OutputStream* out)
{
	out->write(" ");
}

void ElementSerializerPretty::writeNewLine(dom::OutputStream* out)
{
	out->write("\n");
}

int ElementSerializerPretty::incrementIndentationLevel(int indentationLevel)
{
	return ++indentationLevel;
}

int ElementSerializerPretty::decrementIndentationLevel(int indentationLevel)
{
	return --indentationLevel;
}

void ElementSerializerPretty::writeCloser(int indentationLevel, dom::OutputStream* out)
{
	ele->prettyIndentation(indentationLevel, out);
	out->write("</");
	out->write(ele->getTagName());
	out->write(">");
	out->write("\n");
}

void ElementSerializerMinimal::writeOpener(int indentationLevel, dom::OutputStream* out)
{
	out->write("<");
	out->write(ele->getTagName());
}

void ElementSerializerMinimal::setNextSerializerNodeMap(dom::NamedNodeMap::iterator i)
{
	(*i.operator->())->setSerializerMinimal();
}

void ElementSerializerMinimal::setNextSerializerNodeList(dom::NodeList::iterator i)
{
	(*i.operator->())->setSerializerMinimal();
}

void ElementSerializerMinimal::writeCloser(int indentationLevel, dom::OutputStream* out)
{
	out->write("</");
	out->write(ele->getTagName());
	out->write(">");
}

// Chain of Responsibility
void Element_Impl::handleRequest(std::string& request)
{
	if (hasAttributeByValue(request)) {
		printf("Handled request \"%s\"", request);
	}
	else {
		getParentNode()->handleRequest(request);
	}
}

bool Element_Impl::hasAttributeByValue(const std::string& value)
{
	for (dom::NodeList::iterator i = attributes.begin(); i != attributes.end(); i++)
	{
		dom::Attr* attr = dynamic_cast<dom::Attr*>(*i.operator->());

		if (attr->getValue().compare(value) == 0)
			return true;
	}

	return false;
}
