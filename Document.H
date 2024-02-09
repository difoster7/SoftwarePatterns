#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>

#include "Node.H"
#include "CompositeNode.H"

namespace dom
{
	class Element;
	class Text;
	class Attr;
	class NodeList;

	// Composite Pattern Interface for a Composite Component
	class Document : public virtual CompositeNode
	{
	public:
		virtual Element *	createElement(const std::string & tagName)	= 0;
		virtual Text *		createTextNode(const std::string & data)	= 0;
		virtual Attr *		createAttribute(const std::string & name)	= 0;
		virtual Element *	getDocumentElement()				= 0;
	};
};

// Composite Pattern Implmentation of a Composite Component
class Document_Impl : public virtual dom::Document, public virtual CompositeNode_Impl
{
public:
	Document_Impl(void);

	virtual ~Document_Impl();

	virtual dom::Element *	createElement(const std::string & tagName);
	virtual dom::Text *	createTextNode(const std::string & data);
	virtual dom::Attr *	createAttribute(const std::string & name);
	virtual dom::Element *	getDocumentElement();
};

#endif // DOCUMENT_H
