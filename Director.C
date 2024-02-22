#include "Director.H"
#include "XMLTokenizer.H"

void Director::build()
{
	XMLTokenizer tokenizer(file);
	XMLTokenizer::XMLToken* token = 0;

	int docLevel = 0;
	bool ignoreNextElement = false;
	std::string attrName;



	do
	{
		delete	token;
		token = tokenizer.getNextToken();

		//printf("\tLine %d:  %s = '%s'\n", tokenizer.getLineNumber(),
		//	token->toString(), token->getToken().size() == 0 ? "" : token->getToken().c_str());

		switch (token->getTokenType())
		{
		case XMLTokenizer::XMLToken::ELEMENT:
			if (!ignoreNextElement)
			{
				builder->addElement(token->getToken().c_str());
				docLevel++;
			}
			else
			{
				ignoreNextElement = false;
			}
			break;

		case XMLTokenizer::XMLToken::ATTRIBUTE:
			if (docLevel) attrName = token->getToken();
			break;

		case XMLTokenizer::XMLToken::ATTRIBUTE_VALUE:
			if (docLevel) builder->addAttr(attrName, token->getToken());
			break;
		case XMLTokenizer::XMLToken::VALUE:
			if (docLevel) builder->addText(token->getToken());
			break;
		case XMLTokenizer::XMLToken::TAG_CLOSE_START:
			ignoreNextElement = true;
		case XMLTokenizer::XMLToken::NULL_TAG_END:
			if (docLevel) builder->setParentAsCurrent();
			docLevel--;
		}

	} while (token->getTokenType() != XMLTokenizer::XMLToken::NULL_TOKEN);

}
