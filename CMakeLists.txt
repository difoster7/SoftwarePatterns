cmake_minimum_required (VERSION 3.23)
project (Patterns)

add_executable(Patterns Test.C "OutputStream.C" "State.C")
set_property(TARGET Patterns PROPERTY CXX_STANDARD 20)
target_sources(Patterns PUBLIC
	Attr.C
	Attr.H
	Document.C
	Document.H
	Element.C
	Element.H
	NamedNodeMap.C
	NamedNodeMap.H
	Node.C
	Node.H
	NodeList.H
	Test.C
	Text.C
	Text.H
	XMLSerializer.C
	XMLSerializer.H
	XMLTokenizer.C
	XMLTokenizer.H
	XMLValidator.C
	XMLValidator.H
	OutputStream.H
	OutputStream.C
	NodeValidatorDecorator.H
	NodeValidatorDecorator.C
	DOMBuilder.H
	DOMBuilder.C
	Director.H
	Director.C
	ChangeManager.H
	ChangeManager.C
	Observer.H
	Observer.C
	EventHandler.H
	Command.H
	Command.C
	Tests.H
	UserInterface.H
	UserInterface.C
	Builder_State.H
	Builder_State.C
	Director_State.H
	Director_State.C "State.H" "State.C" "SerializerVisitor.H" "SerializerVisitor.C" "NodeFlyweight.H" "NodeFlyweight.C")
