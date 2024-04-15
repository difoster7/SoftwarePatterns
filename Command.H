#ifndef COMMAND_H
#define COMMAND_H

#include <string>

// Command Pattern : Abstract Command
class Command
{
protected:
	char* argv0;
	char* argv1;

	Command() : argv0{ (char*)"command" }, argv1{ (char*)"Test" } {}

public:
	virtual ~Command() {}
	virtual void execute() = 0;
};

// Command Pattern : Concrete Command
class TestTokenizerCommand : public virtual Command
{
private:
	std::string inputFile;
public:
	TestTokenizerCommand() {};

	virtual void addFile(std::string file);
	virtual void execute();
};

// Command Pattern : Concrete Command
class TestSerializerCommand : public virtual Command
{
private:
	std::string outputFilePretty;
	std::string outputFileMinimal;

public:
	TestSerializerCommand() {};

	virtual void addPrettyFileOutput(std::string file);
	virtual void addMinimalFileOutput(std::string file);
	virtual void execute();
};

// Command Pattern : Concrete Command
class TestValidatorCommand : public virtual Command
{
private:
	std::string outputFile;

public:
	TestValidatorCommand() {};

	virtual void addOutputFile(std::string file);
	virtual void execute();
};

// Command Pattern : Concrete Command
class TestDirectorCommand : public virtual Command
{
private:
	std::string inputFile;
public:
	TestDirectorCommand() {};

	virtual void addFile(std::string file);
	virtual void execute();
};

// Command Pattern : Concrete Command
class TestCoRCommand : public virtual Command
{
private:
	std::string inputFile;
public:
	TestCoRCommand() {};

	virtual void addFile(std::string file);
	virtual void execute();
};

// Command Pattern : Concrete Command
class TestMementoCommand : public virtual Command
{
public:
	TestMementoCommand() {};

	virtual void execute();
};

#endif // !COMMAND_H
