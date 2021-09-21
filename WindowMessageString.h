#pragma once
#include "windows.h"
#include <unordered_map>

class WindowMessageString {
public:
	WindowMessageString();
	void PrintWindowMessage(UINT msg);
private:
	std::unordered_map<UINT, PCWSTR> map;
};