#ifndef DOMNodeAdapter_H
#define DOMNodeAdapter_H

#include "DOMNode.hpp"
#include "Node.H"

namespace XERCES
{
	class DOMNodeAdapter : public virtual DOMNode
	{
	private:
		dom::Node* nodeRef;

	protected:
		DOMNodeAdapter() {};
		DOMNodeAdapter(const DOMNode&) {};

	public:
		virtual ~DOMNodeAdapter() {};
		virtual const XMLCh* getNodeName() const;
		virtual const XMLCh* getNodeValue() const;
		virtual NodeType getNodeType() const;
		virtual DOMNode* getParentNode() const;
		virtual DOMNodeList* getChildNodes() const;
		virtual DOMNode* getFirstChild() const;
		virtual DOMNode* getLastChild() const;
		virtual DOMNode* getPreviousSibling() const;
		virtual DOMNode* getNextSibling() const;
		virtual DOMNamedNodeMap* getAttributes() const { return nullptr; };	// unsupported
		virtual DOMDocument* getOwnerDocument() const;
		virtual DOMNode* cloneNode(bool deep) const { return nullptr; }; 	// unsupported
		virtual DOMNode* insertBefore(DOMNode* newChild, DOMNode* refChild);
		virtual DOMNode* replaceChild(DOMNode* newChild, DOMNode* oldChild);
		virtual DOMNode* removeChild(DOMNode* oldChild);
		virtual DOMNode* appendChild(DOMNode* newChild);
		virtual bool hasChildNodes() const;
		virtual void setNodeValue(const XMLCh* nodeValue);
		virtual void normalize() {};	// unsupported
		virtual bool isSupported(const XMLCh* feature, const XMLCh* version) const { return 0; };	// unsupported
		virtual const XMLCh* getNamespaceURI() const { return nullptr; };	// unsupported
		virtual const XMLCh* getPrefix() const { return nullptr; };	// unsupported
		virtual const XMLCh* getLocalName() const;
		virtual void setPrefix(const XMLCh* prefix) {};	// unsupported
		virtual bool hasAttributes() const { return 0; };	// unsupported
		virtual bool isSameNode(const DOMNode* other) const { return 0; };	// unsupported
		virtual bool isEqualNode(const DOMNode* arg) const { return 0; };	// unsupported
		virtual void* setUserData(const XMLCh* key, void* data, DOMUserDataHandler* handler) { return nullptr; };	// unsupported
		virtual void* getUserData(const XMLCh* key) const { return nullptr; };	// unsupported
		virtual const XMLCh* getBaseURI() const { return nullptr; };	// unsupported
		virtual short compareDocumentPosition(const DOMNode* other) const { return NULL; };	// unsupported
		virtual const XMLCh* getTextContent() const { return 0; };	// unsupported
		virtual void setTextContent(const XMLCh* textContent) {};	// unsupported
		virtual const XMLCh* lookupPrefix(const XMLCh* namespaceURI) const { return nullptr; };	// unsupported
		virtual bool isDefaultNamespace(const XMLCh* namespaceURI) const { return 0; };	// unsupported
		virtual const XMLCh* lookupNamespaceURI(const XMLCh* prefix) const { return nullptr; };	// unsupported
		virtual void* getFeature(const XMLCh* feature, const XMLCh* version) const { return nullptr; };	// unsupported
		virtual void release() {};	// unsupported

	};
};







#endif // DOMNodeAdapter_H