/*
    스타크래프트 동접로더
    릴리즈 : 2020-12-18 0618

    아이콘 : http://www.pngmart.com/image/68321
*/

#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <conio.h>

#include "api.h"
#include "function.h"

pZwQueryInformationProcess ZwQueryInformationProcess;
pNtQueryObject NtQueryObject;
TCHAR sName[] = _T("Starcraft Check For Other Instances");

bool closeHandle(DWORD dwProcessId) {
    PPROCESS_HANDLE_SNAPSHOT_INFORMATION pInformation;

    LPBYTE lpBuffer = new BYTE[0x8000];
    DWORD dwBufferSize = 0x8000;

    LPBYTE pObject = new BYTE[0x8000];
    DWORD dwObjectSize = 0x8000;

    BOOL bResult = false;

    // 프로세스를 열음
    HANDLE hProcess = OpenProcess(MAXIMUM_ALLOWED, false, dwProcessId);
    if (!hProcess) {
        return false;
    }
    // 프로세스에 대한 핸들의 정보를 가져옴
    ULONG dwLength = 0;
    NTSTATUS status = ZwQueryInformationProcess(hProcess, ProcessHandleInformation, lpBuffer, dwBufferSize, &dwLength);
    while (status == STATUS_INFO_LENGTH_MISMATCH) {
        delete[] lpBuffer;
        dwBufferSize = dwLength;
        lpBuffer = new BYTE[dwBufferSize];
        status = ZwQueryInformationProcess(hProcess, ProcessHandleInformation, lpBuffer, dwBufferSize, &dwLength);
    }

    // 핸들리스트 루프
    pInformation = (PPROCESS_HANDLE_SNAPSHOT_INFORMATION)lpBuffer;
    for (ULONG i = 0; i < pInformation->NumberOfHandles; i++) {
        HANDLE handle = pInformation->Handles[i].HandleValue;

        
        DWORD dwObjectResult = 0;
        HANDLE copyHandle = nullptr; // 복사될핸들
        status = DuplicateHandle(hProcess, handle, GetCurrentProcess(), &copyHandle, MAXIMUM_ALLOWED, false, DUPLICATE_SAME_ACCESS);

        // 핸들정보 조회
        status = NtQueryObject(copyHandle, ObjectNameInformation, pObject, dwObjectSize, &dwObjectResult);
        while (status == STATUS_INFO_LENGTH_MISMATCH) {
            delete[] pObject;
            dwObjectSize = dwObjectResult;
            pObject = new BYTE[dwObjectSize];
            status = NtQueryObject(copyHandle, ObjectNameInformation, pObject, dwObjectSize, &dwObjectResult);
        }
        CloseHandle(copyHandle);

        // 핸들의 이름을 가져옴
        POBJECT_NAME_INFORMATION pObjectInfo = (POBJECT_NAME_INFORMATION)pObject;
        if (pObjectInfo->Name.Length)
        {
            if (_tcsstr(pObjectInfo->Name.Buffer, sName))
            {
                status = DuplicateHandle(hProcess, handle, GetCurrentProcess(), &copyHandle, MAXIMUM_ALLOWED, false, DUPLICATE_CLOSE_SOURCE);
                CloseHandle(copyHandle);
                printf("\n[%s] PID: %d Handle: %08X\n",GetTime().c_str(), dwProcessId, handle, pObjectInfo->Name.Buffer);
                bResult = true;
            }
        }
    }

    if (lpBuffer) delete[] lpBuffer;
    if (pObject) delete[] pObject;

    CloseHandle(hProcess);
    return bResult;
}

int main()
{
    printf("스타크래프트 멀티로더 v0.1\n");

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
    if (!ZwQueryInformationProcess || !NtQueryObject) {
        Error = GetLastError();
        printf("API 의 주소를 구할수 없습니다.\n");
        ErrorMessage(Error);
        _getch();
        return Error;
    }


    
    unsigned int Num = 0;
    bool bFind = false;

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
                if (closeHandle(dwProcessId))
                {
                    printf("[%s] [Waiting for StarCraft.exe]", GetTime().c_str());
                    Num = 0;
                }
            }

            hWnd = GetWindow(hWnd, GW_HWNDNEXT);
            Sleep(0);
        }


        
        Sleep(1000);
    }

    
}
