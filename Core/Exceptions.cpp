#include "Exceptions.h"
#include <sstream>


// WINDOW EXCEPTION
Win32Exception::Win32Exception(const std::wstring file, int line, HRESULT errorCode) :
	Exception(line, file), m_errorCode(errorCode) 
{}

const std::wstring Win32Exception::TranslateErrorCode() {
	LPWSTR errorText = NULL;
	FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM
		| FORMAT_MESSAGE_ALLOCATE_BUFFER
		| FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		m_errorCode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPWSTR>(&errorText),  // output 
		0, // minimum size for output buffer
		NULL);   // arguments - see note 
	
	std::wstring errorMsg{ errorText };
	LocalFree(errorText);
	return errorMsg;
}

const std::wstring Win32Exception::Info() {
	std::wostringstream ss;
	ss << "FILE: " << m_file << "\n"
		<< "LINE: " << m_line << "\n"
		<< "Type: " << GetType() << "\n"
		<< "Error: " << TranslateErrorCode() << "\n";
	return ss.str();
}