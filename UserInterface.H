#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "Command.H"

// Command Pattern : Invoker
class UserInterface
{
private:
	Command* command;

public:
	UserInterface() {};

	void run();
	void displayOptions();
	void displayHelp();
	void createTokenizerCommand();
	void createSerializerCommand();
	void createValidatorCommand();
	void createDirectorCommand();
	void createCoRCommand();
	void createMementoCommand();

};

#endif // !USERINTERFACE_H
