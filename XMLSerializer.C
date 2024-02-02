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

void XMLSerializer::serializeMinimal(dom::Node * node)
{
	if (dynamic_cast<dom::Document *>(node) != 0)
	{
		file << "<? xml version=\"1.0\" encoding=\"UTF-8\"?>";
		serializeMinimal(dynamic_cast<dom::Document *>(node)->getDocumentElement());
	}
	else if (dynamic_cast<dom::Element *>(node) != 0)
	{
		file << "<" << dynamic_cast<dom::Element *>(node)->getTagName();

		for (dom::NamedNodeMap::iterator i = dynamic_cast<dom::Element *>(node)->getAttributes()->begin();
		  i != dynamic_cast<dom::Element *>(node)->getAttributes()->end();
		  i++)
			serializeMinimal(*i);

		if (dynamic_cast<dom::Element *>(node)->getChildNodes()->size() == 0)
			file << "/>";
		else
		{
			file << ">";

			for (dom::NodeList::iterator i = dynamic_cast<dom::Element *>(node)->getChildNodes()->begin();
			  i != dynamic_cast<dom::Element *>(node)->getChildNodes()->end();
			  i++)
				if (dynamic_cast<dom::Element *>(*i) != 0 || dynamic_cast<dom::Text *>(*i) != 0)
					serializeMinimal(*i);

			file << "</" << dynamic_cast<dom::Element *>(node)->getTagName() + ">";
		}
	}
	else if (dynamic_cast<dom::Attr *>(node) != 0)
	{
		file <<
		  " " << dynamic_cast<dom::Attr *>(node)->getName() << "=\"" << dynamic_cast<dom::Attr *>(node)->getValue() << "\"";
	}
	else if (dynamic_cast<dom::Text *>(node) != 0)
		file << dynamic_cast<dom::Text *>(node)->getData();
}
