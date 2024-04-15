#include "Command.H"
#include "Tests.H"

void TestTokenizerCommand::addFile(std::string file)
{
	inputFile = file;
}

void TestTokenizerCommand::execute()
{
	char* argv3 = inputFile.data();
	char* argv[] = { argv0, argv1, argv3, 0 };
	testTokenizer(3, argv);
}

void TestSerializerCommand::addPrettyFileOutput(std::string file)
{
	outputFilePretty = file;
}

void TestSerializerCommand::addMinimalFileOutput(std::string file)
{
	outputFileMinimal = file;
}

void TestSerializerCommand::execute()
{
	int argc;
	if (!outputFilePretty.empty() && !outputFileMinimal.empty())
	{
		char* argv3 = outputFilePretty.data();
		char* argv4 = outputFileMinimal.data();
		char* argv[] = { argv0, argv1, argv3, argv4, 0 };
		argc = 4;
		testSerializer(argc, argv);
	}
	else if (!outputFilePretty.empty())
	{
		char* argv3 = outputFilePretty.data();
		char* argv[] = { argv0, argv1, argv3, 0 };
		argc = 3;
		testSerializer(argc, argv);
	}
	else
	{
		char* argv[] = { argv0, argv1, 0 };
		argc = 2;
		testSerializer(argc, argv);
	}
}

void TestValidatorCommand::addOutputFile(std::string file)
{
	outputFile = file;
}

void TestValidatorCommand::execute()
{
	char* argv3 = outputFile.data();
	char* argv[] = { argv0, argv1, argv3, 0 };
	testValidator(3, argv);
}

void TestDirectorCommand::addFile(std::string file)
{
	inputFile = file;
}

void TestDirectorCommand::execute()
{
	char* argv3 = inputFile.data();
	char* argv[] = { argv0, argv1, argv3, 0 };
	testDirector(3, argv);
}

void TestCoRCommand::addFile(std::string file)
{
	inputFile = file;
}

void TestCoRCommand::execute()
{
	char* argv3 = inputFile.data();
	char* argv[] = { argv0, argv1, argv3, 0 };
	testCoR(3, argv);
}

void TestMementoCommand::execute()
{
	char* argv[] = { argv0, argv1, 0 };
	testMemento(2, argv);
}
