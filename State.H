#ifndef STATE_H
#define STATE_H

#include "XMLTokenizer.H"
#include "Builder_State.H"

class State
{
public:
	virtual State* handle(XMLTokenizer::XMLToken::TokenTypes lastToken, XMLTokenizer::XMLToken::TokenTypes currentToken, XMLTokenizer::XMLToken* token, Builder_State* builder) = 0;
};

class BeforePrologState : public virtual State
{
public:
	virtual State* handle(XMLTokenizer::XMLToken::TokenTypes lastToken, XMLTokenizer::XMLToken::TokenTypes currentToken, XMLTokenizer::XMLToken* token, Builder_State* builder);
};

class AfterPrologState : public virtual State
{
public:
	virtual State* handle(XMLTokenizer::XMLToken::TokenTypes lastToken, XMLTokenizer::XMLToken::TokenTypes currentToken, XMLTokenizer::XMLToken* token, Builder_State* builder);
};

class ParsingElementState : public virtual State
{
public:
	virtual State* handle(XMLTokenizer::XMLToken::TokenTypes lastToken, XMLTokenizer::XMLToken::TokenTypes currentToken, XMLTokenizer::XMLToken* token, Builder_State* builder);
};

class InNonNullElementState : public virtual State
{
public:
	virtual State* handle(XMLTokenizer::XMLToken::TokenTypes lastToken, XMLTokenizer::XMLToken::TokenTypes currentToken, XMLTokenizer::XMLToken* token, Builder_State* builder);
};

class EndState : public virtual State
{
public:
	virtual State* handle(XMLTokenizer::XMLToken::TokenTypes lastToken, XMLTokenizer::XMLToken::TokenTypes currentToken, XMLTokenizer::XMLToken* token, Builder_State* builder);
};

#endif // !STATE_H
