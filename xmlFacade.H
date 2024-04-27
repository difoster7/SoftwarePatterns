#ifndef XMLFACADE_H
#define XMLFACADE_H

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

// Facade pattern : Facade
class xmlFacade
{
private:
	void printUsage();

	void testTokenizer(int argc, char** argv);
	void testSerializer(int argc, char** argv);
	void testValidator(int argc, char** argv);
	void testDirector(int argc, char** argv);
	void testCoR(int argc, char** argv);
	void testMemento(int argc, char** argv);
	void testClone(int argc, char** argv);
	void testState(int argc, char** argv);
	void testVisitor(int argc, char** argv);
	void testFlyweight(int argc, char** argv);
	void testInterpreter(int argc, char** argv);

public:
	enum TestTypes
	{
		Tokenizer,
		Serializer,
		Validator,
		DirectorTest,
		CoR,
		Memento,
		Clone,
		State,
		Visitor,
		Flyweight,
		Interpreter
	};

	void runTest(TestTypes test, int argc, char** argv);

};

#endif // !XMLFACADE_H
