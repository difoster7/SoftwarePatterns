#ifndef DOMDocumentAdapter_H
#define DOMDocumentAdapter_H

#include "DOMDocument.hpp"
#include "Document.H"
#include "DOMNodeAdapter.H"

namespace XERCES
{
	// DOMDocumentAdapter is an adapter in the adapter pattern
	class DOMDocumentAdapter : public virtual DOMDocument, DOMNodeAdapter
	{
	private:
		dom::Document* docRef;

	protected:

	public:
		DOMDocumentAdapter() { docRef = new Document_Impl(); setNodeRef(docRef); };
		DOMDocumentAdapter(dom::Document* doc) : docRef(doc), DOMNodeAdapter(doc) {};

		virtual ~DOMDocumentAdapter() {};
		virtual DOMElement* createElement(const XMLCh* tagName);
		virtual DOMText* createTextNode(const XMLCh* data);
		virtual DOMAttr* createAttribute(const XMLCh* name);
		virtual DOMElement* getDocumentElement() const ;


		// Below functions are unimplemented
		virtual DOMDocumentFragment* createDocumentFragment() { return nullptr; };
		virtual DOMComment* createComment(const XMLCh* data) { return nullptr; };
		virtual DOMCDATASection* createCDATASection(const XMLCh* data) { return nullptr; };
		virtual DOMProcessingInstruction* createProcessingInstruction(const XMLCh* target,
			const XMLCh* data) {return nullptr; };
		virtual DOMEntityReference* createEntityReference(const XMLCh* name) { return nullptr; };
		virtual DOMDocumentType* getDoctype() const { return nullptr; };
		virtual DOMImplementation* getImplementation() const { return nullptr; };
		virtual DOMNodeList* getElementsByTagName(const XMLCh* tagname) const { return nullptr; };
		virtual DOMNode* importNode(const DOMNode* importedNode, bool deep) { return nullptr; };
		virtual DOMElement* createElementNS(const XMLCh* namespaceURI,
			const XMLCh* qualifiedName) { return nullptr; };
		virtual DOMAttr* createAttributeNS(const XMLCh* namespaceURI,
			const XMLCh* qualifiedName) { return nullptr; };
		virtual DOMNodeList* getElementsByTagNameNS(const XMLCh* namespaceURI,
			const XMLCh* localName) const  { return nullptr; };
		virtual  DOMElement* getElementById(const XMLCh* elementId) const { return nullptr; };
		virtual const XMLCh* getInputEncoding() const { return nullptr; };
		virtual const XMLCh* getXmlEncoding() const { return nullptr; };
		virtual bool                   getXmlStandalone() const { return NULL; };
		virtual void                   setXmlStandalone(bool standalone) {};
		virtual const XMLCh* getXmlVersion() const { return nullptr; };
		virtual void                   setXmlVersion(const XMLCh* version) {};
		virtual const XMLCh* getDocumentURI() const { return nullptr; };
		virtual void                   setDocumentURI(const XMLCh* documentURI) {};
		virtual bool                   getStrictErrorChecking() const { return NULL; };
		virtual void                   setStrictErrorChecking(bool strictErrorChecking) {};
		virtual DOMNode* renameNode(DOMNode* n, const XMLCh* namespaceURI, const XMLCh* qualifiedName) { return nullptr; };
		virtual DOMNode* adoptNode(DOMNode* source) { return nullptr; };
		virtual void                   normalizeDocument() {};
		virtual DOMConfiguration* getDOMConfig() const { return nullptr; };
		virtual DOMEntity* createEntity(const XMLCh* name) { return nullptr; };
		virtual DOMDocumentType* createDocumentType(const XMLCh* name) { return nullptr; };
		virtual DOMDocumentType* createDocumentType(const XMLCh* qName,
			const XMLCh*,  //publicId,
			const XMLCh*   //systemId
		)
		{
			return createDocumentType(qName);
		}
		virtual DOMNotation* createNotation(const XMLCh* name) { return nullptr; };
		virtual DOMElement* createElementNS(const XMLCh* namespaceURI,
			const XMLCh* qualifiedName,
			const XMLFileLoc lineNum,
			const XMLFileLoc columnNum)  { return nullptr; };
	};
};

#endif // DOMDocumentAdapter_H