#include "OutputStream.H"

void FileOutputStream::write(const std::string& input)
{
	file << input;
}

void StdOutputStream::write(const std::string& input)
{
	printf(input.c_str());
}
