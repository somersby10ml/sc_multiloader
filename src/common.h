#pragma once
#include <Windows.h>
#include <functional>
#include <TlHelp32.h>
#include <algorithm>
#include <memory>
#include <tchar.h>
#include <string>

typedef std::function<void(void*)> deleter;

System::String^ GetGamePath();
bool IsUserAdministrator();

public delegate void ProcessDelegate(System::String^ ProcessName, int Processid, int handle);


std::string getErrorString(_In_ DWORD errorCode);
std::string format(const char* format, ...);