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
#include "EventHandler.H"
#include "NodeList.H"
#include "Tests.H";
#include "Builder_State.H"
#include "Director_State.H"
#include "SerializerVisitor.H"
#include "xmlFacade.H";

void printUsage(void)
{
	printf("Usage:\n");
	printf("\tTest t [file] ...\n");
	printf("\tTest s [file1] [file2]\n");
	printf("\tTest s\n");
	printf("\tTest v [file]\n");
	printf("\tTest d [file]\n");
	printf("\tTest c [file]\n");
	printf("\tTest m\n");
	printf("\tTest r\n");
	printf("\tTest A [file]\n");
	printf("\tTest b [file1] [file2]\n");
	printf("\tTest F\n");
}

int main(int argc, char** argv)
{
	xmlFacade facade;

	switch (argv[1][0])
	{
	case 'T':
	case 't':
		//testTokenizer(argc, argv);
		facade.runTest(xmlFacade::TestTypes::Tokenizer, argc, argv);
		break;
	case 'S':
	case 's':
		//testSerializer(argc, argv);
		facade.runTest(xmlFacade::TestTypes::Serializer, argc, argv);
		break;
	case 'V':
	case 'v':
		//testValidator(argc, argv);
		facade.runTest(xmlFacade::TestTypes::Validator, argc, argv);
		break;
	case 'D':
	case 'd':
		//testDirector(argc, argv);
		facade.runTest(xmlFacade::TestTypes::DirectorTest, argc, argv);
		break;
	case 'C':
	case 'c':
		//testCoR(argc, argv);
		facade.runTest(xmlFacade::TestTypes::CoR, argc, argv);
		break;
	case 'M':
	case 'm':
		//testMemento(argc, argv);
		facade.runTest(xmlFacade::TestTypes::Memento, argc, argv);
		break;
	case 'R':	// using R for "replica" to test clone because c is already taken
	case 'r':
		//testClone(argc, argv);
		facade.runTest(xmlFacade::TestTypes::Clone, argc, argv);
		break;
	case 'A':	// using A because I'm running out of letters
	case 'a':
		//testState(argc, argv);
		facade.runTest(xmlFacade::TestTypes::State, argc, argv);
		break;
	case 'B':
	case 'b':
		//testVisitor(argc, argv);
		facade.runTest(xmlFacade::TestTypes::Visitor, argc, argv);
		break;
	case 'F':
	case 'f':
		//testFlyweight(argc, argv);
		facade.runTest(xmlFacade::TestTypes::Flyweight, argc, argv);
		break;
	case 'I':
	case 'i':
		//testInterpreter(argc, argv);
		facade.runTest(xmlFacade::TestTypes::Interpreter, argc, argv);
		break;
	}
}

/*

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

void testCoR(int argc, char** argv)
{
	DOMBuilder* builder = new DOMBuilder_Impl();
	std::string s1 = argv[2];
	Director director(s1, builder);
	director.build();

	EventHandler* handlers = new EventHandler();
	dom::NodeList* handlerList = handlers->getHandlers();

	printf("Now attempting to handle type 1 events.\n");
	std::string eventType = "\"type1\"";
	for (dom::NodeList::iterator i = handlerList->begin(); i != handlerList->end(); i++) {
		(*i)->handleEvent(eventType);
	}

	printf("Now attempting to handle type 2 events.\n");
	eventType = "\"type2\"";
	for (dom::NodeList::iterator i = handlerList->begin(); i != handlerList->end(); i++) {
		(*i)->handleEvent(eventType);
	}

	printf("Now attempting to handle type 3 events.\n");
	eventType = "\"type3\"";
	for (dom::NodeList::iterator i = handlerList->begin(); i != handlerList->end(); i++) {
		(*i)->handleEvent(eventType);
	}
			
}

void testMemento(int argc, char** argv)
{
	XMLValidator	xmlValidator;
	ValidChildren* schemaElement = xmlValidator.addSchemaElement("");
	schemaElement->addValidChild("document", false);
	schemaElement = xmlValidator.addSchemaElement("document");
	schemaElement->addValidChild("element", false);
	schemaElement = xmlValidator.addSchemaElement("element");
	schemaElement->addValidChild("element", false);
	schemaElement->addValidChild("attribute", true);
	schemaElement->addValidChild("attribute2", true);
	schemaElement->setCanHaveText(true);

	printf("Saving Validator state\n");
	XMLValidator_Caretaker caretaker;
	caretaker.saveState(&xmlValidator);

	printf("Resetting the validator to a new Object with no state\n");
	xmlValidator = *(new XMLValidator);

	printf("Restoring validator state\n");
	caretaker.restoreState(&xmlValidator);


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

	dom::OutputStream* outputPretty = new StdOutputStream();
	XMLSerializer	xmlSerializer(outputPretty);
	xmlSerializer.serializePretty(document);
}

void testClone(int argc, char** argv)
{
	dom::Document* document = new Document_Impl;
	dom::Element* root = document->createElement("document");
	document->appendChild(root);

	dom::Element* child = document->createElement("element");
	dom::Attr* attr = document->createAttribute("attribute");
	attr->setValue("attribute value");
	child->setAttributeNode(attr);
	root->appendChild(child);

	child = document->createElement("element");
	root->appendChild(child);

	child = document->createElement("element");
	child->setAttribute("attribute", "attribute value");
	child->setAttribute("attribute2", "attribute2 value");
	dom::Text* text = document->createTextNode("Element Value");
	child->appendChild(text);
	root->appendChild(child);

	child = document->createElement("element");
	root->appendChild(child);

	dom::Node* document2 = document->clone();

	printf("\nNow printing original document\n\n");
	dom::OutputStream* outputPretty = new StdOutputStream();
	XMLSerializer	xmlSerializer(outputPretty);
	xmlSerializer.serializePretty(document);

	printf("\nNow printing cloned document\n\n");
	xmlSerializer.serializePretty(document2);

}

void testState(int argc, char** argv)
{
	dom::Document* document = new Document_Impl;
	Builder_State		builder(document);
	Director_State	director(argv[2], &builder);
	//std::fstream	file(argv[3], std::ios_base::out);
	//XMLSerializer	xmlSerializer(&file);
	//xmlSerializer.serializePretty(document);
	dom::OutputStream* outputPretty = new StdOutputStream();
	XMLSerializer	xmlSerializer(outputPretty);
	xmlSerializer.serializePretty(document);
}

void testVisitor(int argc, char** argv)
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

	dom::Document* document = new Document_Impl;
	dom::Element* root = document->createElement("document");
	document->appendChild(root);

	dom::Element* child = document->createElement("element");
	dom::Attr* attr = document->createAttribute("attribute");
	attr->setValue("attribute value");
	child->setAttributeNode(attr);
	root->appendChild(child);

	child = document->createElement("element");
	root->appendChild(child);

	child = document->createElement("element");
	child->setAttribute("attribute", "attribute value");
	child->setAttribute("attribute2", "attribute2 value");
	dom::Text* text = document->createTextNode("Element Value");
	child->appendChild(text);
	root->appendChild(child);

	child = document->createElement("element");
	root->appendChild(child);

	//
	// Serialize
	//
	SerializerVisitor* prettyVisitor = new PrettySerializerVistor(outputPretty);
	SerializerVisitor* minimalVisitor = new MinimalSerializerVistor(outputMinimal);

	printf("Pretty Serialization:\n\n");
	document->accept(prettyVisitor);

	printf("\nMinimal Serialization:\n\n");
	document->accept(minimalVisitor);
}

void testFlyweight(int argc, char** argv)
{
	dom::Document* document = new Document_Impl;
	dom::Element* root = document->createElementFlyweight("document");
	document->appendChild(root);

	dom::Element* child = document->createElementFlyweight("element");
	dom::Attr* attr = document->createAttrFlyweight("attribute");
	attr->setValue("attribute value");
	child->setAttributeNode(attr);
	root->appendChild(child);

	child = document->createElementFlyweight("element");
	root->appendChild(child);

	child = document->createElementFlyweight("element");
	child->setAttribute("attribute", "attribute value");
	child->setAttribute("attribute2", "attribute2 value");
	dom::Text* text = document->createTextFlyweight("Element Value");
	child->appendChild(text);
	root->appendChild(child);

	child = document->createElementFlyweight("element");
	root->appendChild(child);

	dom::Node* document2 = document->clone();

	printf("\nGetting parent node of attribute: %s\n", attr->getParentNode()->getNodeName().c_str());

}

void testInterpreter(int argc, char** argv)
{
	DOMBuilder* builder = new DOMBuilder_Impl();
	std::string s1 = argv[2];
	Director director(s1, builder);
	director.build();

	printf("Value is: %d\n", builder->getDoc()->calculateValue());
}

*/