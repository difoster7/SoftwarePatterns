#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>

#include "Node.H"

namespace dom
{
	class Element;
	class Text;
	class Attr;
	class NodeList;

	class Document : public virtual Node	// Factory method creator interface
	{
	public:
		virtual Element *	createElement(const std::string & tagName)	= 0;	// Factory method creator function
		virtual Text *		createTextNode(const std::string & data)	= 0;	// Factory method creator function
		virtual Attr *		createAttribute(const std::string & name)	= 0;	// Factory method creator function
		virtual Element *	getDocumentElement()				= 0;
	};
};

class Document_Impl : public virtual dom::Document, public virtual Node_Impl	// Factory method concrete creator
{
public:
	Document_Impl(void);

	virtual ~Document_Impl();

	virtual dom::Element *	createElement(const std::string & tagName);	// Factory method concrete creator function
	virtual dom::Text *	createTextNode(const std::string & data);	// Factory method concrete creator function
	virtual dom::Attr *	createAttribute(const std::string & name);	// Factory method concrete creator function
	virtual dom::Element *	getDocumentElement();
};

#endif // DOCUMENT_H
