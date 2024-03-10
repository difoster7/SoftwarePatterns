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
		virtual DOMNamedNodeMap* getAttributes() const;
		virtual DOMDocument* getOwnerDocument() const;
		virtual DOMNode* cloneNode(bool deep) const;
		virtual DOMNode* insertBefore(DOMNode* newChild, DOMNode* refChild);
		virtual DOMNode* replaceChild(DOMNode* newChild, DOMNode* oldChild);
		virtual DOMNode* removeChild(DOMNode* oldChild);
		virtual DOMNode* appendChild(DOMNode* newChild);
		virtual bool hasChildNodes() const;
		virtual void setNodeValue(const XMLCh* nodeValue);
		virtual void normalize();
		virtual bool isSupported(const XMLCh* feature, const XMLCh* version) const;
		virtual const XMLCh* getNamespaceURI() const;
		virtual const XMLCh* getPrefix() const;
		virtual const XMLCh* getLocalName() const;
		virtual void setPrefix(const XMLCh* prefix);
		virtual bool hasAttributes() const;
		virtual bool isSameNode(const DOMNode* other) const;
		virtual bool isEqualNode(const DOMNode* arg) const;
		virtual void* setUserData(const XMLCh* key, void* data, DOMUserDataHandler* handler);
		virtual void* getUserData(const XMLCh* key) const;
		virtual const XMLCh* getBaseURI() const;
		virtual short compareDocumentPosition(const DOMNode* other) const;
		virtual const XMLCh* getTextContent() const;
		virtual void setTextContent(const XMLCh* textContent);
		virtual const XMLCh* lookupPrefix(const XMLCh* namespaceURI) const;
		virtual bool isDefaultNamespace(const XMLCh* namespaceURI) const;
		virtual const XMLCh* lookupNamespaceURI(const XMLCh* prefix) const;
		virtual void* getFeature(const XMLCh* feature, const XMLCh* version) const;
		virtual void release();

	};
};







#endif // DOMNodeAdapter_H