#ifndef DIRECTOR_STATE_H
#define DIRECTOR_STATE_H

#include <string>
#include "State.H"
//#include "XMLTokenizer.H"

class Builder_State;

// State Pattern : Context
class Director_State
{
private:
	//enum State
	//{
	//	BEFORE_PROLOG	= 1,
	//	AFTER_PROLOG,
	//	PARSING_ELEMENT,
	//	IN_NONNULL_ELEMENT,
	//	END
	//};

	State* state;

public:
	Director_State(const std::string & filename, Builder_State * builder); // State Pattern : Request method in the constructor
};

#endif // DIRECTOR_STATE_H
