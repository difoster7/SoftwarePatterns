#ifndef DIRECTOR_H
#define DIRECTOR_H

#include <string>

//#include "XMLTokenizer.H"
#include "DOMBuilder.H"


class Director
{
private:
	DOMBuilder* builder;
	std::string&  file;

public:
	Director(std::string& file, DOMBuilder* builder) : file(file), builder(builder) {}
	void build();

};


#endif // !DIRECTOR_H
