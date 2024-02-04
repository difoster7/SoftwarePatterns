#include <string>
#include <fstream>
#include <ios>

#include "Node.H"
#include "OutputStream.H"

/*
* XMLSerializer roles
* Strategy Patter : Context
*/
class XMLSerializer
{
private:
	dom::OutputStream	* out;
	int			indentationLevel;

public:
	XMLSerializer(dom::OutputStream * out) : indentationLevel(0), out(out) {}
	~XMLSerializer() {}

	virtual void		serializePretty(dom::Node * node);	// Strategy pattern context interface
	virtual void		serializeMinimal(dom::Node * node);	// Strategy pattern context interface
};
