#include "Exceptions.h"
#include <sstream>

Exception::Exception(int line, const std::string& file) : m_line(line), m_file(file) 
{}

const std::string Exception::Info() {
	std::ostringstream ss;
	ss << "FILE: " << m_file << "\n"
		<< "LINE: " << m_line << "\n" 
		<< "Type: " << GetType() << "\n";
	return ss.str();
}
