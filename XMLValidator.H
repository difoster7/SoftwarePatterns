#ifndef XMLVALIDATOR_H
#define XMLVALIDATOR_H

#include <string>
#include <fstream>
#include <ios>
#include <vector>

#include "Element.H"

class ValidChildren
{
private:
	std::string			thisElement;
	std::vector<std::string>	validChildren;
	std::vector<bool>		childIsAttribute;
	bool				_canHaveText;
public:
	ValidChildren(std::string _thisElement) : thisElement(_thisElement), _canHaveText(false)	{}

	virtual std::string	getThisElement(void)			{ return thisElement; }
	virtual bool		canHaveText(void)			{ return _canHaveText; }
	virtual void		setCanHaveText(bool __canHaveText)	{ _canHaveText = __canHaveText; }

	virtual void		addValidChild(const std::string & child, bool isAttribute);
	virtual bool		childIsValid(const std::string & child, bool isAttribute);
};

class XMLValidator_Memento
{
private:
	std::vector<ValidChildren*> state;

	XMLValidator_Memento(std::vector<ValidChildren*> state) : state(state) {};
	std::vector<ValidChildren*> getState() { return state; };

public:
	~XMLValidator_Memento() {};

	friend class XMLValidator;
};

class XMLValidator
{
private:
	std::vector<ValidChildren *>	schema;
public:
	XMLValidator(void)	{}
	~XMLValidator() { for (int i = 0; i < schema.size(); i++) delete schema[i]; }

	virtual ValidChildren *				addSchemaElement(std::string element);
	virtual std::vector<ValidChildren *>::iterator	findSchemaElement(std::string element);
	virtual bool					canRootElement(std::string newElement);
	virtual bool					canAddElement(dom::Element * element, std::string newElement);
	virtual bool					canAddText(dom::Element * element);
	virtual bool					canAddAttribute(dom::Element * element, std::string newAttribute);

	virtual void	setMemento(XMLValidator_Memento* memento) { schema = memento->getState(); };
	virtual XMLValidator_Memento*	createMemento(){ return new XMLValidator_Memento(schema); };
};

class XMLValidator_Caretaker
{
private:
	XMLValidator_Memento* memento;

public:
	XMLValidator_Caretaker() {};

	void saveState(XMLValidator* validator) { memento = validator->createMemento(); }
	void restoreState(XMLValidator* validator) { validator->setMemento(memento); }
};

#endif // !XMLVALIDATOR_H
