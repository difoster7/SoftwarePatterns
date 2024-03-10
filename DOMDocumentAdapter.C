#include "DOMDocumentAdapter.H"
#include "DOMElementAdapter.H"
#include "DOMAttrAdapter.H"
#include "DOMTextAdapter.H"

using namespace XERCES;

DOMElement* DOMDocumentAdapter::createElement(const XMLCh* tagName)
{
	return new DOMElementAdapter(docRef->createElement(tagName));
}

DOMText* DOMDocumentAdapter::createTextNode(const XMLCh* data)
{
	return new DOMTextAdapter(docRef->createTextNode(data));
}

DOMAttr* DOMDocumentAdapter::createAttribute(const XMLCh* name)
{
	return new DOMAttrAdapter(docRef->createAttribute(name));
}

DOMElement* DOMDocumentAdapter::getDocumentElement() const
{
	return new DOMElementAdapter(docRef->getDocumentElement());
}
