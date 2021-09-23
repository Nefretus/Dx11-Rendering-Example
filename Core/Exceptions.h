#pragma once
#include <exception>
#include <string>
#include <Windows.h>

#define WIDE2(x) L##x
#define WIDE1(x) WIDE2(x)
#define WFILE WIDE1(__FILE__)

class Exception : public std::exception {
public:
	Exception(int line, const std::wstring& file) : m_line(line), m_file(file)
	{}

	virtual const std::wstring Info() = 0;

	virtual LPCTSTR GetType() const = 0; // shoudl be wchar?
	int GetLine() const { return m_line; }
	const std::wstring& GetFile() const { return m_file; }
protected:
	int m_line;
	std::wstring m_file;
};

class WindowException : public Exception {
public:
	WindowException(const std::wstring file, int line, HRESULT errorCode);

	LPCTSTR GetType() const override { return L"Window exception"; }
	HRESULT GetErrorCode() const { return m_errorCode; }

	const std::wstring Info() override;
	const std::wstring TranslateErrorCode();
private:
	HRESULT m_errorCode;
};