#ifndef OUTPUTSTREAM_H
#define OUTPUTSTREAM_H

#include <string>
#include <fstream>

namespace dom
{
	class OutputStream 
	{
	public:
		virtual void write(const std::string& input) = 0;
	};
}

class FileOutputStream : public dom::OutputStream
{
private:
	std::fstream file;

public:
	FileOutputStream(const std::string& filename) : file(filename.c_str(), std::ios_base::out) {}
	~FileOutputStream() {}

	virtual void write(const std::string& input);
};

class StdOutputStream : public dom::OutputStream 
{
public:
	StdOutputStream() {}
	~StdOutputStream() {}

	virtual void write(const std::string& input);
};

#endif OUTPUTSTREAM_H