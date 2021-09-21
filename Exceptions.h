#pragma once
#include <exception>
#include <string>

class Exception : public std::exception {
public:
	Exception(int line, const std::string& file);

	const std::string Info();

	virtual const char* GetType() const { return "Basic exception"; }
	int GetLine() const { return m_line; }
	const std::string& GetFile() const { return m_file; }
protected:
	int m_line;
	std::string m_file;
};