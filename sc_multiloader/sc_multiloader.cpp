/*
	스타크래프트 동접로더
	릴리즈 : 2020-12-18 0618

	아이콘 : http://www.pngmart.com/image/68321
*/

#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <conio.h>
#include <vector>

#include "api.h"
#include "function.h"

pZwQueryInformationProcess ZwQueryInformationProcess;
pZwQuerySystemInformation ZwQuerySystemInformation;
pNtQueryObject NtQueryObject;
WCHAR sName[] = L"Starcraft Check For Other Instances";

DWORD EnableNTPrivilege(LPCTSTR szPrivilege, DWORD dwState) {
	DWORD                   dwRtn = 0;
	HANDLE                  hToken;
	LUID                    luid;
	TOKEN_PRIVILEGES 		TP;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
		if (LookupPrivilegeValue(NULL, szPrivilege, &luid)) {
			TP.Privileges[0].Attributes = dwState;
			TP.PrivilegeCount = 1;
			TP.Privileges[0].Luid = luid;
			if (AdjustTokenPrivileges(hToken, FALSE, &TP, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
				dwRtn = TP.Privileges[0].Attributes;
		}
		CloseHandle(hToken);
	}
	return dwRtn;
}

bool closeHandle(DWORD dwProcessId) {
	SYSTEM_HANDLE_INFORMATION* pInformation;

	//LPBYTE system_handle_buffer = new BYTE[0x8000];
	std::vector<BYTE> system_handle_buffer;
	std::vector<BYTE> name_buffer;
	std::vector<BYTE> type_buffer;

	//LPBYTE name_buffer = new BYTE[0x8000];

	BOOL bResult = false;
	// MAXIMUM_ALLOWED

	// 프로세스를 열음
	// MAXIMUM_ALLOWED
	HANDLE hProcess = OpenProcess(MAXIMUM_ALLOWED, false, dwProcessId);
	if (!hProcess) {
		return false;
	}
	// 프로세스에 대한 핸들의 정보를 가져옴
	ULONG dwLength = 0;
	NTSTATUS status = ZwQuerySystemInformation(SYSTEM_INFORMATION_CLASS::SystemHandleInformation, system_handle_buffer.data(), system_handle_buffer.size(), &dwLength);
	while (status == STATUS_INFO_LENGTH_MISMATCH) {
		system_handle_buffer.resize(dwLength);
		status = ZwQuerySystemInformation(SYSTEM_INFORMATION_CLASS::SystemHandleInformation, system_handle_buffer.data(), system_handle_buffer.size(), &dwLength);
	}
	if (status != STATUS_SUCCESS) {
		printf("\nZwQuerySystemInformation return:%08X GetLastError:%08X\n", status, GetLastError());
		return false;
	}

	// 핸들리스트 루프
	pInformation = (SYSTEM_HANDLE_INFORMATION*)system_handle_buffer.data();
	for (ULONG i = 0; i < pInformation->NumberOfHandles; i++) {
		if (pInformation->Handles[i].ProcessId != dwProcessId) continue;

		HANDLE handle = (HANDLE)pInformation->Handles[i].Handle;

		// 핸들 복사
		HANDLE copyHandle = nullptr;
		if (!DuplicateHandle(hProcess, handle, GetCurrentProcess(), &copyHandle, MAXIMUM_ALLOWED, false, DUPLICATE_SAME_ACCESS)) {
			continue;
		}

		// 핸들 타입 조회
		status = NtQueryObject(copyHandle, ObjectTypeInformation, type_buffer.data(), type_buffer.size(), &dwLength);
		while (status == STATUS_INFO_LENGTH_MISMATCH) {
			type_buffer.resize(dwLength);
			status = NtQueryObject(copyHandle, ObjectTypeInformation, type_buffer.data(), type_buffer.size(), &dwLength);
		}
		if (status != STATUS_SUCCESS)
			continue;

		PPUBLIC_OBJECT_TYPE_INFORMATION typeName = (PPUBLIC_OBJECT_TYPE_INFORMATION)type_buffer.data();
		if (wcscmp(typeName->TypeName.Buffer, L"Event") != 0)
			continue;

		// 핸들 값 조회
		status = NtQueryObject(copyHandle, ObjectNameInformation, name_buffer.data(), name_buffer.size(), &dwLength);
		while (status == STATUS_INFO_LENGTH_MISMATCH) {
			name_buffer.resize(dwLength);
			status = NtQueryObject(copyHandle, ObjectNameInformation, name_buffer.data(), name_buffer.size(), &dwLength);
		}
		if (status != STATUS_SUCCESS)
			continue;

		CloseHandle(copyHandle);

		// 핸들의 이름을 가져옴
		POBJECT_NAME_INFORMATION pObjectInfo = (POBJECT_NAME_INFORMATION)name_buffer.data();
		if (pObjectInfo->Name.Length) {
			if (wcsstr(pObjectInfo->Name.Buffer, sName)) {
				status = DuplicateHandle(hProcess, handle, GetCurrentProcess(), &copyHandle, MAXIMUM_ALLOWED, false, DUPLICATE_CLOSE_SOURCE);
				CloseHandle(copyHandle);
				printf("\n[%s] PID: %d Handle: %p %ws\n", GetTime().c_str(), dwProcessId, handle, pObjectInfo->Name.Buffer);
				bResult = true;
			}
		}
	}

	CloseHandle(hProcess);
	return bResult;
}

int main()
{
	EnableNTPrivilege(SE_DEBUG_NAME, SE_PRIVILEGE_ENABLED);

	printf("스타크래프트 멀티로더 v0.2\n");

	if (!IsElevated()) {
		printf("관리자 권한으로 실행해주세요.\n");
		_getch();
		return 5;
	}

	const TCHAR* NTDLL = _T("ntdll.dll");
	DWORD Error = 0UL;

	HMODULE hNTDLL = LoadLibrary(NTDLL);
	Error = GetLastError();
	if (hNTDLL == 0UL) {
		hNTDLL = GetModuleHandle(NTDLL);
		if (hNTDLL == 0UL) {
			printf("ntdll.dll 의 모듈 주소를 구할수 없습니다.\n");
			ErrorMessage(Error);
			_getch();
			return Error;
		}
	}

	ZwQueryInformationProcess = (pZwQueryInformationProcess)GetProcAddress(hNTDLL, "ZwQueryInformationProcess");
	NtQueryObject = (pNtQueryObject)GetProcAddress(hNTDLL, "NtQueryObject");
	ZwQuerySystemInformation = (pZwQuerySystemInformation)GetProcAddress(hNTDLL, "ZwQuerySystemInformation");
	if (!ZwQueryInformationProcess || !NtQueryObject) {
		Error = GetLastError();
		printf("API 의 주소를 구할수 없습니다.\n");
		ErrorMessage(Error);
		_getch();
		return Error;
	}

	unsigned int Num = 0;
	bool bFind = false;
	std::vector<int> overlapPrevent;

	printf("[%s] [Waiting for StarCraft.exe]", GetTime().c_str());
	while (true) {
		if (Num % 4 == 0) printf(".");
		if (Num % 4 == 1) printf(".");
		if (Num % 4 == 2) printf(".");
		if (Num % 4 == 3) printf("\b\b\b   \b\b\b");
		Num++;

		HWND hWnd = FindWindow(NULL, NULL);
		while (hWnd) {
			TCHAR Buffer[20];
			DWORD dwProcessId;
			GetWindowText(hWnd, Buffer, 20);
			if (_tcscmp(Buffer, _T("Brood War")) == 0) {
				GetWindowThreadProcessId(hWnd, &dwProcessId);
				if (find(overlapPrevent.begin(), overlapPrevent.end(), dwProcessId) == overlapPrevent.end()
					&& closeHandle(dwProcessId))
				{
					printf("[%s] [Waiting for StarCraft.exe]", GetTime().c_str());
					Num = 0;
					overlapPrevent.push_back(dwProcessId);
				}
			}

			hWnd = GetWindow(hWnd, GW_HWNDNEXT);
			Sleep(0);
		}

		Sleep(1000);
	}
}