#include "DOMDocumentAdapter.H"

using namespace XERCES;

DOMElement* XERCES::DOMDocumentAdapter::createElement(const XMLCh* tagName)
{
    return nullptr;
}

DOMDocumentFragment* XERCES::DOMDocumentAdapter::createDocumentFragment()
{
    return nullptr;
}

DOMText* XERCES::DOMDocumentAdapter::createTextNode(const XMLCh* data)
{
    return nullptr;
}

DOMComment* XERCES::DOMDocumentAdapter::createComment(const XMLCh* data)
{
    return nullptr;
}

DOMCDATASection* XERCES::DOMDocumentAdapter::createCDATASection(const XMLCh* data)
{
    return nullptr;
}

DOMProcessingInstruction* XERCES::DOMDocumentAdapter::createProcessingInstruction(const XMLCh* target, const XMLCh* data)
{
    return nullptr;
}

DOMAttr* XERCES::DOMDocumentAdapter::createAttribute(const XMLCh* name)
{
    return nullptr;
}

DOMEntityReference* XERCES::DOMDocumentAdapter::createEntityReference(const XMLCh* name)
{
    return nullptr;
}

DOMDocumentType* XERCES::DOMDocumentAdapter::getDoctype() const
{
    return nullptr;
}

DOMImplementation* XERCES::DOMDocumentAdapter::getImplementation() const
{
    return nullptr;
}

DOMElement* XERCES::DOMDocumentAdapter::getDocumentElement() const
{
    return nullptr;
}

DOMNodeList* XERCES::DOMDocumentAdapter::getElementsByTagName(const XMLCh* tagname) const
{
    return nullptr;
}

DOMNode* XERCES::DOMDocumentAdapter::importNode(const DOMNode* importedNode, bool deep)
{
    return nullptr;
}

DOMElement* XERCES::DOMDocumentAdapter::createElementNS(const XMLCh* namespaceURI, const XMLCh* qualifiedName)
{
    return nullptr;
}

DOMAttr* XERCES::DOMDocumentAdapter::createAttributeNS(const XMLCh* namespaceURI, const XMLCh* qualifiedName)
{
    return nullptr;
}

DOMNodeList* XERCES::DOMDocumentAdapter::getElementsByTagNameNS(const XMLCh* namespaceURI, const XMLCh* localName) const
{
    return nullptr;
}

DOMElement* XERCES::DOMDocumentAdapter::getElementById(const XMLCh* elementId) const
{
    return nullptr;
}

const XMLCh* XERCES::DOMDocumentAdapter::getInputEncoding() const
{
    return nullptr;
}

const XMLCh* XERCES::DOMDocumentAdapter::getXmlEncoding() const
{
    return nullptr;
}

bool XERCES::DOMDocumentAdapter::getXmlStandalone() const
{
    return false;
}

void XERCES::DOMDocumentAdapter::setXmlStandalone(bool standalone)
{
}

const XMLCh* XERCES::DOMDocumentAdapter::getXmlVersion() const
{
    return nullptr;
}

void XERCES::DOMDocumentAdapter::setXmlVersion(const XMLCh* version)
{
}

const XMLCh* XERCES::DOMDocumentAdapter::getDocumentURI() const
{
    return nullptr;
}

void XERCES::DOMDocumentAdapter::setDocumentURI(const XMLCh* documentURI)
{
}

bool XERCES::DOMDocumentAdapter::getStrictErrorChecking() const
{
    return false;
}

void XERCES::DOMDocumentAdapter::setStrictErrorChecking(bool strictErrorChecking)
{
}

DOMNode* XERCES::DOMDocumentAdapter::renameNode(DOMNode* n, const XMLCh* namespaceURI, const XMLCh* qualifiedName)
{
    return nullptr;
}

DOMNode* XERCES::DOMDocumentAdapter::adoptNode(DOMNode* source)
{
    return nullptr;
}

void XERCES::DOMDocumentAdapter::normalizeDocument()
{
}

DOMConfiguration* XERCES::DOMDocumentAdapter::getDOMConfig() const
{
    return nullptr;
}

DOMEntity* XERCES::DOMDocumentAdapter::createEntity(const XMLCh* name)
{
    return nullptr;
}

DOMDocumentType* createDocumentType(const XMLCh* name)
{
    return nullptr;
}

DOMNotation* XERCES::DOMDocumentAdapter::createNotation(const XMLCh* name)
{
    return nullptr;
}

DOMElement* XERCES::DOMDocumentAdapter::createElementNS(const XMLCh* namespaceURI, const XMLCh* qualifiedName, const XMLFileLoc lineNum, const XMLFileLoc columnNum)
{
    return nullptr;
}
