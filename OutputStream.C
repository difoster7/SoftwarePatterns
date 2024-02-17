#include "OutputStream.H"

void FileOutputStream::write(const std::string& input)
{
	printf("hi from output stream\n");
	printf(input.c_str());
	file << input;
}

void StdOutputStream::write(const std::string& input)
{
	printf(input.c_str());
}
