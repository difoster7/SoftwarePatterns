#ifndef DOMDocumentAdapter_H
#define DOMDocumentAdapter_H

#include "DOMDocument.hpp"
#include "Document.H"
#include "DOMNodeAdapter.H"

namespace XERCES
{
	class DOMDocumentAdapter : public virtual DOMNodeAdapter
	{
	private:
		dom::Document* docRef;

	protected:

	public:
		DOMDocumentAdapter() {};

		virtual ~DOMDocumentAdapter() {};

		virtual DOMElement* createElement(const XMLCh* tagName);
		virtual DOMDocumentFragment* createDocumentFragment();
		virtual DOMText* createTextNode(const XMLCh* data);
		virtual DOMComment* createComment(const XMLCh* data);
		virtual DOMCDATASection* createCDATASection(const XMLCh* data);
		virtual DOMProcessingInstruction* createProcessingInstruction(const XMLCh* target, const XMLCh* data);
		virtual DOMAttr* createAttribute(const XMLCh* name);
		virtual DOMEntityReference* createEntityReference(const XMLCh* name);
		virtual DOMDocumentType* getDoctype() const;
		virtual DOMImplementation* getImplementation() const;
		virtual DOMElement* getDocumentElement() const;
		virtual DOMNodeList* getElementsByTagName(const XMLCh* tagname) const;
		virtual DOMNode* importNode(const DOMNode* importedNode, bool deep);
		virtual DOMElement* createElementNS(const XMLCh* namespaceURI, const XMLCh* qualifiedName);
		virtual DOMAttr* createAttributeNS(const XMLCh* namespaceURI, const XMLCh* qualifiedName);
		virtual DOMNodeList* getElementsByTagNameNS(const XMLCh* namespaceURI, const XMLCh* localName) const;
		virtual DOMElement* getElementById(const XMLCh* elementId) const;
		virtual const XMLCh* getInputEncoding() const;
		virtual const XMLCh* getXmlEncoding() const;
		virtual bool getXmlStandalone() const;
		virtual void setXmlStandalone(bool standalone);
		virtual const XMLCh* getXmlVersion() const;
		virtual void setXmlVersion(const XMLCh* version);
		virtual const XMLCh* getDocumentURI() const;
		virtual void setDocumentURI(const XMLCh* documentURI);
		virtual bool getStrictErrorChecking() const;
		virtual void setStrictErrorChecking(bool strictErrorChecking);
		virtual DOMNode* renameNode(DOMNode* n, const XMLCh* namespaceURI, const XMLCh* qualifiedName);
		virtual DOMNode* adoptNode(DOMNode* source);
		virtual void normalizeDocument();
		virtual DOMConfiguration* getDOMConfig() const;
		virtual DOMEntity* createEntity(const XMLCh* name);
		virtual DOMDocumentType* createDocumentType(const XMLCh* name);
		virtual DOMNotation* createNotation(const XMLCh* name);
		virtual DOMElement* createElementNS(const XMLCh* namespaceURI,
			const XMLCh* qualifiedName,
			const XMLFileLoc lineNum,
			const XMLFileLoc columnNum);

	};
};







#endif // DOMDocumentAdapter_H