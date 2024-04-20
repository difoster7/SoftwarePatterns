#include "SerializerVisitor.H"

void PrettySerializerVistor::serializeDocument(dom::Document* doc)
{
	out->write("<? xml version=\"1.0\" encoding=\"UTF-8\"?>");
	out->write("\n");
	doc->getDocumentElement()->accept(this);
}

void PrettySerializerVistor::serializeElement(dom::Element* ele)
{
	ele->prettyIndentation(indentationLevel, out);
	out->write("<");
	out->write(ele->getTagName());

	int attrCount = 0;

	for (dom::NamedNodeMap::iterator i = ele->getAttributes()->begin(); i != ele->getAttributes()->end(); i++)
	{
		(*i.operator->())->accept(this);
		attrCount++;
	}

	if (attrCount > 0)
	{
		out->write(" ");
	}

	if (ele->getChildNodes()->size() == 0)
	{
		out->write("/>");
		out->write("\n");
	}
	else
	{
		out->write(">");
		out->write("\n");
		++indentationLevel;

			for (dom::NodeList::iterator i = ele->getChildNodes()->begin(); i != ele->getChildNodes()->end(); i++)
			{
				if (dynamic_cast<dom::Element*>(*i) != 0 || dynamic_cast<dom::Text*>(*i) != 0)
				{
					(*i.operator->())->accept(this);
				}
			}

		--indentationLevel;

		ele->prettyIndentation(indentationLevel, out);
		out->write("</");
		out->write(ele->getTagName());
		out->write(">");
		out->write("\n");
	}
}

void PrettySerializerVistor::serializeAttr(dom::Attr* attr)
{
	out->write(" ");
	out->write(attr->getName());
	out->write("=\"");
	out->write(attr->getValue());
	out->write("\"");
}

void PrettySerializerVistor::serializeText(dom::Text* text)
{
	text->prettyIndentation(indentationLevel, out);

	out->write(text->getData());
	out->write("\n");
}

void MinimalSerializerVistor::serializeDocument(dom::Document* doc)
{
	out->write("<? xml version=\"1.0\" encoding=\"UTF-8\"?>");
	doc->getDocumentElement()->accept(this);
}

void MinimalSerializerVistor::serializeElement(dom::Element* ele)
{
	out->write("<");
	out->write(ele->getTagName());

	int attrCount = 0;

	for (dom::NamedNodeMap::iterator i = ele->getAttributes()->begin(); i != ele->getAttributes()->end(); i++)
	{
		(*i.operator->())->accept(this);
		attrCount++;
	}

	if (ele->getChildNodes()->size() == 0)
	{
		out->write("/>");
	}
	else
	{
		out->write(">");

		for (dom::NodeList::iterator i = ele->getChildNodes()->begin(); i != ele->getChildNodes()->end(); i++)
		{
			if (dynamic_cast<dom::Element*>(*i) != 0 || dynamic_cast<dom::Text*>(*i) != 0)
			{
				(*i.operator->())->accept(this);
			}
		}

		out->write("</");
		out->write(ele->getTagName());
		out->write(">");
	}
}

void MinimalSerializerVistor::serializeAttr(dom::Attr* attr)
{
	out->write(" ");
	out->write(attr->getName());
	out->write("=\"");
	out->write(attr->getValue());
	out->write("\"");
}

void MinimalSerializerVistor::serializeText(dom::Text* text)
{
	out->write(text->getData());
}
