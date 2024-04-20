#include "Builder_State.H"
#include <iostream>

#include <ctype.h>
#include "Document.H"
#include "Element.H"
#include "Attr.H"
#include "Text.H"

void Builder_State::addValue(const std::string & text)
{
	elementStack.top()->appendChild(static_cast<dom::Node *>(factory->createTextNode(trim(text))));
}

void Builder_State::confirmElement(const std::string & tag)
{
	// Throw an exception if trim(tag) != currentElement.getTagName()
}

void Builder_State::createAttribute(const std::string & attribute)
{
	std::string	trimmed	= trim(attribute);
	currentAttr	= factory->createAttribute(std::string(trimmed, 0, trimmed.size() - 1));
}

void Builder_State::createElement(const std::string & tag)
{
	currentElement	= factory->createElement(trim(tag));

	if (elementStack.size() == 0)	// This is the root element.
	{
		factory->appendChild(currentElement);
	}
	else
	{
		elementStack.top()->getNodeName();
		elementStack.top()->appendChild(currentElement);
	}
}

void Builder_State::createProlog(void)
{
	// null method in this implementation
}

void Builder_State::endProlog(void)
{
	// null method in this implementation
}

void Builder_State::identifyProlog(const std::string & id)
{
	// null method in this implementation
}

bool Builder_State::popElement(void)
{
	currentElement	= elementStack.top();
	elementStack.pop();
	return elementStack.size() > 0;
}

void Builder_State::pushElement(void)
{
	if (currentElement)
	elementStack.push(currentElement);
	currentElement	= 0;
}

void Builder_State::valueAttribute(const std::string & value)
{
	std::string	trimmed	= trim(value);
	currentAttr->setValue(std::string(trimmed, 1, trimmed.size() - 2));

	if (currentElement != 0)	// Discard prolog attributes.  This implementation currently doesn't have
					// anything to do with them.
		currentElement->setAttributeNode(currentAttr);
}

const std::string Builder_State::trim(const std::string & s) const
{
	int	start_index;
	int	stop_index;

	for (start_index = 0; start_index < s.size() && isspace(s[start_index]); start_index++);
	for (stop_index = s.size() - 1; stop_index >= start_index && isspace(s[stop_index]); stop_index--);

	return std::string(s, start_index, stop_index - start_index + 1);
}
