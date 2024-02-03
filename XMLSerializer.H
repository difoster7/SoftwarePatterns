#include <string>
#include <fstream>
#include <ios>

#include "Node.H"

/*
* XMLSerializer roles
* Strategy Patter : Context
*/
class XMLSerializer
{
private:
	std::fstream		file;
	int			indentationLevel;

public:
	XMLSerializer(const std::string & filename) : indentationLevel(0), file(filename.c_str(), std::ios_base::out)	{}
	~XMLSerializer() {}

	virtual void		serializePretty(dom::Node * node);	// Strategy pattern context interface
	virtual void		serializeMinimal(dom::Node * node);	// Strategy pattern context interface
};
