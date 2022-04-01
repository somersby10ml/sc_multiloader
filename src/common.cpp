#include "common.h"
#include "ntapi.h"


using namespace System::Security::Principal;
using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace Microsoft::Win32;

System::String^ GetGamePath() {
	System::String^ subkey = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\StarCraft";
	RegistryKey^ key = Registry::LocalMachine->OpenSubKey(subkey, true);
	if (key == nullptr)
		return nullptr;

	System::String^ gamePath = (System::String^)key->GetValue("InstallLocation");
	if (gamePath == nullptr)
		return nullptr;

	gamePath = Path::Combine(gamePath, "x86\\StarCraft.exe");
	if (!File::Exists(gamePath))
		return nullptr;

	return gamePath;
}

bool IsUserAdministrator() {
	WindowsIdentity^ user = WindowsIdentity::GetCurrent();
	WindowsPrincipal^ principal = gcnew WindowsPrincipal(user);
	return principal->IsInRole(WindowsBuiltInRole::Administrator);
}



std::string getErrorString(_In_ DWORD errorCode) {
	char* messageBuffer = nullptr;
	DWORD size = FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		nullptr,
		errorCode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)&messageBuffer,
		0,
		nullptr);

	if (size == 0 || messageBuffer == nullptr)
		return std::string();

	while (size && isspace(messageBuffer[size - 1]))
		messageBuffer[--size] = 0;

	std::string message(messageBuffer);
	if (messageBuffer)
		LocalFree(messageBuffer);
	return message;
}

std::string format(const char* format, ...) {
	va_list argptr;
	va_start(argptr, format);
	size_t len = static_cast<size_t>(std::vsnprintf(NULL, 0, format, argptr)) + 1;
	std::string formated(len, 0);
	std::vsnprintf((char*)formated.data(), len, format, argptr);
	return formated;
}