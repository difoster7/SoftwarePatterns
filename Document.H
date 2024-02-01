#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <fstream>

#include "Node.H"

namespace dom
{
	class Element;
	class Text;
	class Attr;
	class NodeList;

	/* Document Class has the following roles
	* Factory Pattern : Creator Interface
	* Strategy Pattern : Algorithm Interface
	*/
	class Document : public virtual Node
	{
	public:
		virtual Element *	createElement(const std::string & tagName)	= 0;	// Factory pattern creator method
		virtual Text *		createTextNode(const std::string & data)	= 0;	// Factory pattern creator method
		virtual Attr *		createAttribute(const std::string & name)	= 0;	// Factory pattern creator method
		virtual Element *	getDocumentElement()				= 0;

		virtual void		serializePretty(std::fstream file) = 0;	// Strategy pattern algorithm method
	};
};

/* Document_Impl class has the following roles
* Factory Pattern : Concrete Creator
* Strategy Pattern : Concrete Algorithm
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

	virtual void serializePretty(std::fstream file);	// Strategy pattern concerte algorithm method
};

#endif // DOCUMENT_H
