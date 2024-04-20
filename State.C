#include "State.H"


State* BeforePrologState::handle(XMLTokenizer::XMLToken::TokenTypes lastToken, XMLTokenizer::XMLToken::TokenTypes currentToken, XMLTokenizer::XMLToken* token, Builder_State* builder)
{
	switch (lastToken)
	{
	case XMLTokenizer::XMLToken::NULL_TOKEN:
		switch(currentToken)
		{
		case XMLTokenizer::XMLToken::PROLOG_START:
			builder->createProlog();
			return new AfterPrologState;
			break;
		default:
			break;
		}
	default:
		// Shouldn't be able to get here.
		break;
	}

	return this;
}


State* AfterPrologState::handle(XMLTokenizer::XMLToken::TokenTypes lastToken, XMLTokenizer::XMLToken::TokenTypes currentToken, XMLTokenizer::XMLToken* token, Builder_State* builder)
{
	switch (lastToken)
	{
	case XMLTokenizer::XMLToken::PROLOG_START:
		switch(currentToken)
		{
		case XMLTokenizer::XMLToken::PROLOG_IDENTIFIER:
			builder->identifyProlog(token->getToken());
			break;
		default:
			break;
		}
		break;
	case XMLTokenizer::XMLToken::PROLOG_IDENTIFIER:
		switch(currentToken)
		{
		case XMLTokenizer::XMLToken::ATTRIBUTE:
			builder->createAttribute(token->getToken());
			break;
		case XMLTokenizer::XMLToken::PROLOG_END:
			builder->endProlog();
			return new ParsingElementState;
			break;
		default:
			break;
		}
		break;
	case XMLTokenizer::XMLToken::ATTRIBUTE:
		switch(currentToken)
		{
		case XMLTokenizer::XMLToken::ATTRIBUTE_VALUE:
			builder->valueAttribute(token->getToken());
			break;
		default:
			break;
		}
		break;
	case XMLTokenizer::XMLToken::ATTRIBUTE_VALUE:
		switch(currentToken)
		{
		case XMLTokenizer::XMLToken::ATTRIBUTE:
			builder->createAttribute(token->getToken());
			break;
		case XMLTokenizer::XMLToken::TAG_END:
		case XMLTokenizer::XMLToken::PROLOG_END:
			builder->endProlog();
			return new ParsingElementState;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return this;
}

State* ParsingElementState::handle(XMLTokenizer::XMLToken::TokenTypes lastToken, XMLTokenizer::XMLToken::TokenTypes currentToken, XMLTokenizer::XMLToken* token, Builder_State* builder)
{
	switch (lastToken)
	{
	case XMLTokenizer::XMLToken::TAG_START:
		switch(currentToken)
		{
		case XMLTokenizer::XMLToken::ELEMENT:
			builder->createElement(token->getToken());
			break;
		default:
			break;
		}
		break;
	case XMLTokenizer::XMLToken::ELEMENT:
		switch(currentToken)
		{
		case XMLTokenizer::XMLToken::ATTRIBUTE:
			builder->createAttribute(token->getToken());
			break;
		case XMLTokenizer::XMLToken::TAG_END:
			builder->pushElement();
			return new InNonNullElementState;
			break;
		case XMLTokenizer::XMLToken::NULL_TAG_END:
			break;
		default:
			break;
		}
		break;
	case XMLTokenizer::XMLToken::ATTRIBUTE:
		switch(currentToken)
		{
		case XMLTokenizer::XMLToken::ATTRIBUTE_VALUE:
			builder->valueAttribute(token->getToken());
			break;
		default:
			break;
		}
		break;
	case XMLTokenizer::XMLToken::ATTRIBUTE_VALUE:
		switch(currentToken)
		{
		case XMLTokenizer::XMLToken::ATTRIBUTE:
			builder->createAttribute(token->getToken());
			break;
		case XMLTokenizer::XMLToken::TAG_END:
			builder->pushElement();
			return new InNonNullElementState;
			break;
		case XMLTokenizer::XMLToken::NULL_TAG_END:
			break;
		default:
			break;
		}
		break;
	case XMLTokenizer::XMLToken::PROLOG_END:
		switch(currentToken)
		{
		case XMLTokenizer::XMLToken::TAG_START:
			// Actually create element when we read tag name.
			break;
		default:
			break;
		}
		break;
	case XMLTokenizer::XMLToken::NULL_TAG_END:
		switch(currentToken)
		{
		case XMLTokenizer::XMLToken::TAG_START:
			// Actually create element when we read tag name.
			break;
		case XMLTokenizer::XMLToken::TAG_CLOSE_START:
			return new InNonNullElementState;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return this;
}

State* InNonNullElementState::handle(XMLTokenizer::XMLToken::TokenTypes lastToken, XMLTokenizer::XMLToken::TokenTypes currentToken, XMLTokenizer::XMLToken* token, Builder_State* builder)
{
	switch (lastToken)
	{
	case XMLTokenizer::XMLToken::ELEMENT:
		switch (currentToken)
		{
		case XMLTokenizer::XMLToken::TAG_END:
			if (!builder->popElement())
				return new EndState;
			break;
		default:
			break;
		}
		break;
	case XMLTokenizer::XMLToken::TAG_END:
		switch (currentToken)
		{
		case XMLTokenizer::XMLToken::TAG_START:
			return new ParsingElementState;
			// Actually create element when we read tag name.
			break;
		case XMLTokenizer::XMLToken::VALUE:
			builder->addValue(token->getToken());
			break;
		case XMLTokenizer::XMLToken::TAG_CLOSE_START:
			break;
		default:
			break;
		}
		break;
	case XMLTokenizer::XMLToken::VALUE:
		switch (currentToken)
		{
		case XMLTokenizer::XMLToken::TAG_CLOSE_START:
			break;
		default:
			break;
		}
	case XMLTokenizer::XMLToken::TAG_CLOSE_START:
		switch (currentToken)
		{
		case XMLTokenizer::XMLToken::ELEMENT:
			builder->confirmElement(token->getToken());
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return this;
}

State* EndState::handle(XMLTokenizer::XMLToken::TokenTypes lastToken, XMLTokenizer::XMLToken::TokenTypes currentToken, XMLTokenizer::XMLToken* token, Builder_State* builder)
{
	switch (currentToken)
	{
	case XMLTokenizer::XMLToken::NULL_TOKEN:
		break;
	default:
		break;
	}

	return this;
}