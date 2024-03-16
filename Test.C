#include <stdio.h>
#include "Attr.H"
#include "Document.H"
#include "Element.H"
#include "Text.H"
#include "XMLTokenizer.H"
#include "XMLSerializer.H"
#include "XMLValidator.H"
#include "OutputStream.H"
#include "NodeValidatorDecorator.H"
#include "DOMBuilder.H"
#include "Director.H"
#include "Observer.H"

void testTokenizer(int argc, char** argv);
void testSerializer(int argc, char** argv);
void testValidator(int argc, char** argv);
void testDirector(int argc, char** argv);

void printUsage(void)
{
	printf("Usage:\n");
	printf("\tTest t [file] ...\n");
	printf("\tTest s [file1] [file2]\n");
	printf("\tTest s\n");
	printf("\tTest v [file]\n");
	printf("\tTest d [file]\n");
}

int main(int argc, char** argv)
{

	if (argc < 2)
	{
		printUsage();
		exit(0);
	}

	switch(argv[1][0])
	{
	case 'T':
	case 't':
		testTokenizer(argc, argv);
		break;
	case 'S':
	case 's':
		testSerializer(argc, argv);
		break;
	case 'V':
	case 'v':
		testValidator(argc, argv);
		break;
	case 'D':
	case 'd':
		testDirector(argc, argv);
		break;
	}
}

// testTokenizer is the Builder Pattern Director
void testTokenizer(int argc, char** argv)
{
	if (argc < 3)
	{
		printUsage();
		exit(0);
	}

	dom::Document *	document	= new Document_Impl;

	dom::Element *	element	= document->createElement("NewElement");
	dom::Text *	text	= document->createTextNode("Text Data");
	dom::Attr *	attr	= document->createAttribute("NewAttribute");

	printf("Element Tag = '%s'\n", element->getTagName().c_str());
	printf("Text Data = '%s'\n", text->getValue().c_str());
	printf("Attr Name = '%s'\n", attr->getName().c_str());

	element->setAttributeNode(attr);
	printf("Element attribute '%s'='%s'\n", element->getTagName().c_str(), element->getAttribute("NewAttribute").c_str());

	delete element;
	delete text;
	delete attr;
	delete document;

	DOMBuilder* builder = new DOMBuilder_Impl;

	std::string attrName;

	for (int i = 2; i < argc; i++)
	{
		XMLTokenizer	tokenizer(argv[i]);

		XMLTokenizer::XMLToken *	token	= 0;
		int docLevel  = 0;
		bool ignoreNextElement = false;

		printf("File:  '%s'\n", argv[i]);

		do
		{
			delete	token;
			token	= tokenizer.getNextToken();

			printf("\tLine %d:  %s = '%s'\n", tokenizer.getLineNumber(),
			  token->toString(), token->getToken().size() == 0 ? "" : token->getToken().c_str());

			switch (token->getTokenType())
			{
			case XMLTokenizer::XMLToken::ELEMENT:
				if (!ignoreNextElement)
				{
					builder->addElement(token->getToken().c_str());
					docLevel++;
				}
				else 
				{
					ignoreNextElement = false;
				}
				break;

			case XMLTokenizer::XMLToken::ATTRIBUTE:
				if(docLevel) attrName = token->getToken();
				break;

			case XMLTokenizer::XMLToken::ATTRIBUTE_VALUE:
				if (docLevel) builder->addAttr(attrName, token->getToken());
				break;
			case XMLTokenizer::XMLToken::VALUE:
				if (docLevel) builder->addText(token->getToken());
				break;
			case XMLTokenizer::XMLToken::TAG_CLOSE_START:
				ignoreNextElement = true;
			case XMLTokenizer::XMLToken::NULL_TAG_END:
				if (docLevel) builder->setParentAsCurrent();
				docLevel--;
			}

		} while (token->getTokenType() != XMLTokenizer::XMLToken::NULL_TOKEN);

		// Test builder
		printf("\n~~~~~~~~~~~~Builder output~~~~~~~~~~\n\n");
		dom::OutputStream* outputPretty = new StdOutputStream();
		XMLSerializer	xmlSerializer(outputPretty);
		xmlSerializer.serializePretty(builder->getDoc());


		delete	token;
	}
}

void testSerializer(int argc, char** argv)
{
	//if (argc < 4)
	//{
	//	printUsage();
	//	exit(0);
	//}

	//
	// Create tree of this document:
	// <? xml version="1.0" encoding="UTF-8"?>
	// <document>
	//   <element attribute="attribute value"/>
	//   <element/>
	//   <element attribute="attribute value" attribute2="attribute2 value">
	//     Element Value
	//   </element>
	//   <element>
	//   </element>
	// </document>
	//

	dom::OutputStream* outputPretty;
	dom::OutputStream* outputMinimal;

	switch (argc)
	{
	case 2:
		outputPretty = new StdOutputStream();
		outputMinimal = new StdOutputStream();
		break;

	case 3:
		outputPretty = new FileOutputStream(argv[2]);
		outputMinimal = new StdOutputStream();
		break;

	case 4:
		outputPretty = new FileOutputStream(argv[2]);
		outputMinimal = new FileOutputStream(argv[3]);
	}

	dom::Document *	document	= new Document_Impl;
	dom::Element *	root		= document->createElement("document");
	document->appendChild(root);

	dom::Element *	child		= document->createElement("element");
	dom::Attr *	attr		= document->createAttribute("attribute");
	attr->setValue("attribute value");
	child->setAttributeNode(attr);
	root->appendChild(child);

	child				= document->createElement("element");
	root->appendChild(child);

	child				= document->createElement("element");
	child->setAttribute("attribute", "attribute value");
	child->setAttribute("attribute2", "attribute2 value");
	dom::Text *	text		= document->createTextNode("Element Value");
	child->appendChild(text);
	root->appendChild(child);

	child				= document->createElement("element");
	root->appendChild(child);

	//
	// Serialize
	//
	XMLSerializer	xmlSerializer(outputPretty);
	xmlSerializer.serializePretty(document);
	XMLSerializer	xmlSerializer2(outputMinimal);
	xmlSerializer2.serializeMinimal(document);

	// delete Document and tree.
}

void testValidator(int argc, char** argv)
{
	if (argc < 3)
	{
		printUsage();
		exit(0);
	}

	//
	// Create tree of this document:
	// <? xml version="1.0" encoding="UTF-8"?>
	// <document>
	//   <element attribute="attribute value"/>
	//   <element/>
	//   <element attribute="attribute value" attribute2="attribute2 value">
	//     Element Value
	//   </element>
	//   <element>
	//   </element>
	// </document>
	//
	// Schema for this document:
	// document contains:  element
	// element contains:  element
	// element contains attributes:  attribute, attribute2
	//
	XMLValidator	xmlValidator;
	ValidChildren *	schemaElement	= xmlValidator.addSchemaElement("");
	schemaElement->addValidChild("document", false);
	schemaElement	= xmlValidator.addSchemaElement("document");
	schemaElement->addValidChild("element", false);
	schemaElement	= xmlValidator.addSchemaElement("element");
	schemaElement->addValidChild("element", false);
	schemaElement->addValidChild("attribute", true);
	schemaElement->addValidChild("attribute2", true);
	schemaElement->setCanHaveText(true);

	DocumentValidatorDecorator* document = new DocumentValidatorDecorator(&xmlValidator, new Document_Impl);
	ElementValidatorDecorator* root = 0;
	ElementValidatorDecorator* child = 0;
	dom::Attr* attr = 0;

	root = new ElementValidatorDecorator(&xmlValidator, document->createElement("document"));
	document->appendChild(root->getElement());
	
	child = new ElementValidatorDecorator(&xmlValidator, document->createElement("element"));
	attr = document->createAttribute("attribute");
	attr->setValue("attribute value");
	child->setAttributeNode(attr);
	root->appendChild(child->getElement());

	child = new ElementValidatorDecorator(&xmlValidator, document->createElement("element"));
	root->appendChild(child->getElement());

	child = new ElementValidatorDecorator(&xmlValidator, document->createElement("element"));
	child->setAttribute("attribute", "attribute value");
	child->setAttribute("attribute2", "attribute2 value");

	dom::Text* text = document->createTextNode("Element Value");
	child->appendChild(text);
	root->appendChild(child->getElement());
	
	child = new ElementValidatorDecorator(&xmlValidator, document->createElement("element"));
	root->appendChild(child->getElement());

	//
	// Serialize
	//
	dom::OutputStream* out = new FileOutputStream(argv[2]);
	XMLSerializer	xmlSerializer(out);
	xmlSerializer.serializePretty(document);

	// delete Document and tree.
}

void testDirector(int argc, char** argv)
{
	Observer* newNodeObserver = new NewNodeObserver_Impl();
	Observer* nodeCompleteObserver = new NodeCompleteObserver_Impl();

	DOMBuilder* builder = new DOMBuilder_Impl();
	std::string s1 = argv[2];
	Director director(s1, builder);
	director.build();

	dom::OutputStream* outputPretty = new StdOutputStream();
	XMLSerializer	xmlSerializer(outputPretty);
	xmlSerializer.serializePretty(builder->getDoc());
}
