#include "DOMBuilder.H"

DOMBuilder_Impl::DOMBuilder_Impl()
{
	doc = new Document_Impl();
	curNode = doc;
}

void DOMBuilder_Impl::addElement(const std::string& tagName)
{
	dom::Element* newEle = doc->createElement(tagName);

	curNode->appendChild(newEle);
	curNode = newEle;
	dynamic_cast<dom::Element*>(curNode);
}

void DOMBuilder_Impl::addAttr(const std::string& name, const std::string& value)
{
	dynamic_cast<dom::Element*>(curNode)->setAttribute(name, value);
}

void DOMBuilder_Impl::addText(const std::string& value)
{
	dom::Text* text = doc->createTextNode(value);
	dynamic_cast<dom::Element*>(curNode)->appendChild(text);
}

void DOMBuilder_Impl::setParentAsCurrent()
{
	curNode = curNode->getParentNode();
}

dom::Node* DOMBuilder_Impl::getDoc()
{
	return doc;
}
