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

	/* 
	* Document Class has the following roles
	* Factory Pattern : Creator Interface
	*/
	class Document : public virtual Node
	{
	public:
		virtual Element *	createElement(const std::string & tagName)	= 0;	// Factory pattern creator method
		virtual Text *		createTextNode(const std::string & data)	= 0;	// Factory pattern creator method
		virtual Attr *		createAttribute(const std::string & name)	= 0;	// Factory pattern creator method
		virtual Element *	getDocumentElement()				= 0;
	};
};

/* 
* Document_Impl class has the following roles
* Factory Pattern : Concrete Creator
* Strategy Pattern : Concrete Algorithm
* Strategy Pattern : Context
*/
class Document_Impl : public virtual dom::Document, public virtual Node_Impl
{
public:
	Document_Impl(void);

	virtual ~Document_Impl();

	virtual dom::Element *	createElement(const std::string & tagName);	// Factory pattern concrete creator method
	virtual dom::Text *	createTextNode(const std::string & data);	// Factory pattern concrete creator method
	virtual dom::Attr *	createAttribute(const std::string & name);	// Factory pattern concrete creator method
	virtual dom::Element *	getDocumentElement();

	virtual int serializePrettyAlgorithm(int indentationLevel, dom::OutputStream* out);	// Strategy pattern algorithm interface implementation
	virtual void serializeMinimalAlgorithm(dom::OutputStream* out);	// Factory Pattern Algorithm interface implementation

};

#endif // DOCUMENT_H
