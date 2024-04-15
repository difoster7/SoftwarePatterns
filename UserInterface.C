#include "UserInterface.H"
#include <iostream>;
#include <string>;
#include <sstream>;

using namespace std;

void UserInterface::run()
{
	int selection = -1;
	string inputStr;

	while (selection != 99)
	{
		displayOptions();
		getline(cin, inputStr);
		stringstream(inputStr) >> selection;
		printf("\n\n");

		switch (selection)
		{
		case 1:
			createTokenizerCommand();
			break;
		case 2:
			createSerializerCommand();
			break;
		case 3:
			createValidatorCommand();
			break;
		case 4:
			createDirectorCommand();
			break;
		case 5:
			createCoRCommand();
			break;
		case 6:
			createMementoCommand();
			break;
		case 99:
			continue;
		default:
			displayHelp();
			continue;
		}

		command->execute();
		printf("\n\n");

	}
}

void UserInterface::displayOptions()
{
	printf("Select one of the following options: \n");
	printf("1: Test Tokenizer\n");
	printf("2: Test Serializer\n");
	printf("3: Test Validator\n");
	printf("4: Test Director\n");
	printf("5: Test Chain of Responsibility\n");
	printf("6: Test Memento\n");
	printf("99: Quit\n");
	printf("\nInput: ");
}

void UserInterface::displayHelp()
{
	printf("\n");
	printf("Tokenizer: reads an xml file into memory, requires one file input\n");
	printf("Serialize: builds a DOM structure in memory and prints it to an output, can print to files or stdout\n");
	printf("Validator: validates a DOM structure in memory and prints it to a file, requires a file to output to\n");
	printf("Director: reads an xml file into memory and observers key events, requires one file input\n");
	printf("Chain of Responsibility: reads an xml file into memory and tests if it can handles events, requires one file input\n");
	printf("Memento: builds a DOM structure in memory, then destroys and recreates it with a memento\n\n");
}

void UserInterface::createTokenizerCommand()
{
	string inputStr;
	command = new TestTokenizerCommand();
	printf("Please enter an input file: ");
	getline(cin, inputStr);

	dynamic_cast<TestTokenizerCommand*>(command)->addFile(inputStr);
}

void UserInterface::createSerializerCommand()
{
	string inputStr;
	string prettyOutput;
	string minimalOutput;

	command = new TestSerializerCommand();

	printf("Would you like to enter a file for the pretty output? (y/n) : ");
	getline(cin, inputStr);
	if (inputStr.compare("y") || inputStr == ("Y"))
	{
		printf("Please enter an output file: ");
		getline(cin, inputStr);
		dynamic_cast<TestSerializerCommand*>(command)->addPrettyFileOutput(inputStr);

		printf("Would you like to enter a file for the minimal output? (y/n) : ");
		getline(cin, inputStr);
		if (inputStr.compare("y") || inputStr == ("Y"))
		{
			printf("Please enter an output file: ");
			getline(cin, inputStr);
			dynamic_cast<TestSerializerCommand*>(command)->addMinimalFileOutput(inputStr);
		}
	}
}

void UserInterface::createValidatorCommand()
{
	string inputStr;
	command = new TestValidatorCommand();
	printf("Please enter an output file: ");
	getline(cin, inputStr);

	dynamic_cast<TestValidatorCommand*>(command)->addOutputFile(inputStr);
}

void UserInterface::createDirectorCommand()
{
	string inputStr;
	command = new TestDirectorCommand();
	printf("Please enter an input file: ");
	getline(cin, inputStr);

	dynamic_cast<TestDirectorCommand*>(command)->addFile(inputStr);
}

void UserInterface::createCoRCommand()
{
	string inputStr;
	command = new TestCoRCommand();
	printf("Please enter an input file: ");
	getline(cin, inputStr);

	dynamic_cast<TestCoRCommand*>(command)->addFile(inputStr);
}

void UserInterface::createMementoCommand()
{
	command = new TestMementoCommand();
}
