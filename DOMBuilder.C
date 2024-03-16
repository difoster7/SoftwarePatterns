#include "DOMBuilder.H"

void DOMBuilder_Impl::addElement(const std::string& tagName)
{
	dom::Element* newEle = doc->createElement(tagName);

	curNode->appendChild(newEle);
	curNode = newEle;

	ChangeManager* chgMngr = new ChangeManager_Impl();
	chgMngr->notify(ChangeManager::ChangeType::NEW_NODE, curNode);
}

void DOMBuilder_Impl::addAttr(const std::string& name, const std::string& value)
{
	dynamic_cast<dom::Element*>(curNode)->setAttribute(name, value);
}

void DOMBuilder_Impl::addText(const std::string& value)
{
	dom::Text* text = doc->createTextNode(value);
	dynamic_cast<dom::Element*>(curNode)->appendChild(text);

	ChangeManager* chgMngr = new ChangeManager_Impl();
	chgMngr->notify(ChangeManager::ChangeType::NEW_NODE, curNode);
}

void DOMBuilder_Impl::setParentAsCurrent()
{
	curNode = curNode->getParentNode();
	ChangeManager* chgMngr = new ChangeManager_Impl();
	chgMngr->notify(ChangeManager::ChangeType::NODE_COMPLETE, curNode);
}

dom::Node* DOMBuilder_Impl::getDoc()
{
	return doc;
}
