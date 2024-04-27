#include "DOMBuilder.H"
#include "EventHandler.H"

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
	std::string valueTrimmed = value.c_str();
	valueTrimmed = valueTrimmed.substr(1, valueTrimmed.size() - 2);

	valueTrimmed.erase(std::remove_if(valueTrimmed.begin(), valueTrimmed.end(), std::isspace), valueTrimmed.end());

	dynamic_cast<dom::Element*>(curNode)->setAttribute(name, valueTrimmed);
}

void DOMBuilder_Impl::addText(const std::string& value)
{
	std::string valueTrimmed = value.c_str();

	valueTrimmed.erase(std::remove_if(valueTrimmed.begin(), valueTrimmed.end(), std::isspace), valueTrimmed.end());

	dom::Text* text = doc->createTextNode(valueTrimmed);
	dynamic_cast<dom::Element*>(curNode)->appendChild(text);

	ChangeManager* chgMngr = new ChangeManager_Impl();
	chgMngr->notify(ChangeManager::ChangeType::NEW_NODE, curNode);
}

void DOMBuilder_Impl::setParentAsCurrent()
{
	ChangeManager* chgMngr = new ChangeManager_Impl();
	chgMngr->notify(ChangeManager::ChangeType::NODE_COMPLETE, curNode);

	if (curNode->getNodeType() == dom::Node::ELEMENT_NODE) {
		EventHandler* handlers = new EventHandler();
		handlers->addhandler(curNode);
	}
	curNode = curNode->getParentNode();
}

dom::Node* DOMBuilder_Impl::getDoc()
{
	return doc;
}
