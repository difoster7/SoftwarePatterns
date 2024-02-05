#include "NodeValidatorDecorator.H"

dom::Node* DocumentValidatorDecorator::appendChild(Node* newChild)
{
	if (validator->canRootElement(newChild->getNodeName()))
	{
		return doc->appendChild(newChild);
	}
	printf("Attempted invalid schema operation.");
	exit(0);
}

void ElementValidatorDecorator::setAttribute(const std::string& name, const std::string& value)
{
	if (validator->canAddAttribute(this->element, name))
	{
		return element->setAttribute(name, value);
	}

	printf("Attempted invalid schema operation.");
	exit(0);
}

dom::Attr* ElementValidatorDecorator::setAttributeNode(dom::Attr* newAttr)
{
	if (validator->canAddAttribute(this->element, newAttr->getNodeName()))
	{
		return element->setAttributeNode(newAttr);
	}

	printf("Attempted invalid schema operation.");
	exit(0);
}

dom::Node* ElementValidatorDecorator::appendChild(Node* newChild)
{
	switch (newChild->getNodeType())
	{
	case Node::ELEMENT_NODE:
		if (validator->canAddElement(element, newChild->getNodeName()))
		{
			return element->appendChild(newChild);
		}
		break;

	case Node::TEXT_NODE:
		if (validator->canAddText(element))
		{
			return element->appendChild(newChild);
		}
	}

	printf("Attempted invalid schema operation.");
	exit(0);
}

/*
	virtual bool					canRootElement(std::string newElement);
	virtual bool					canAddElement(dom::Element * element, std::string newElement);
	virtual bool					canAddText(dom::Element * element);
	virtual bool					canAddAttribute(dom::Element * element, std::string newAttribute);
*/