#ifndef STATE_H
#define STATE_H

#include "XMLTokenizer.H"
#include "Builder_State.H"

// State pattern : Abstract State
class State
{
public:
	virtual State* handle(XMLTokenizer::XMLToken::TokenTypes lastToken, XMLTokenizer::XMLToken::TokenTypes currentToken, XMLTokenizer::XMLToken* token, Builder_State* builder) = 0; // State Pattern : Abstract Handle Interface
};

// State pattern : Concrete State
class BeforePrologState : public virtual State
{
public:
	virtual State* handle(XMLTokenizer::XMLToken::TokenTypes lastToken, XMLTokenizer::XMLToken::TokenTypes currentToken, XMLTokenizer::XMLToken* token, Builder_State* builder); // State Pattern : Handle Implementation
};

// State pattern : Concrete State
class AfterPrologState : public virtual State
{
public:
	virtual State* handle(XMLTokenizer::XMLToken::TokenTypes lastToken, XMLTokenizer::XMLToken::TokenTypes currentToken, XMLTokenizer::XMLToken* token, Builder_State* builder); // State Pattern : Handle Implementation
};

// State pattern : Concrete State
class ParsingElementState : public virtual State
{
public:
	virtual State* handle(XMLTokenizer::XMLToken::TokenTypes lastToken, XMLTokenizer::XMLToken::TokenTypes currentToken, XMLTokenizer::XMLToken* token, Builder_State* builder); // State Pattern : Handle Implementation
};

// State pattern : Concrete State
class InNonNullElementState : public virtual State
{
public:
	virtual State* handle(XMLTokenizer::XMLToken::TokenTypes lastToken, XMLTokenizer::XMLToken::TokenTypes currentToken, XMLTokenizer::XMLToken* token, Builder_State* builder); // State Pattern : Handle Implementation
};

// State pattern : Concrete State
class EndState : public virtual State
{
public:
	virtual State* handle(XMLTokenizer::XMLToken::TokenTypes lastToken, XMLTokenizer::XMLToken::TokenTypes currentToken, XMLTokenizer::XMLToken* token, Builder_State* builder); // State Pattern : Handle Implementation
};

#endif // !STATE_H
