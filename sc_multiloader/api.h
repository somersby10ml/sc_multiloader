#pragma once


const LONG STATUS_SUCCESS = 0x000000;
const LONG STATUS_INFO_LENGTH_MISMATCH = 0xC0000004;

typedef LONG       NTSTATUS;
typedef LONG       KPRIORITY;

typedef struct _UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
    PWSTR Buffer;
} UNICODE_STRING, * PUNICODE_STRING;

typedef enum _PROCESSINFOCLASS
{
    ProcessHandleCount = 0x14,
    ProcessHandleInformation = 0x33,
    ProcessHandleTable = 0x3A,
} PROCESSINFOCLASS, * PPROCESSINFOCLASS;

typedef NTSTATUS(NTAPI* pZwQueryInformationProcess)(
    _In_      HANDLE           ProcessHandle,
    _In_      PROCESSINFOCLASS ProcessInformationClass,
    _Out_     PVOID            ProcessInformation,
    _In_      ULONG            ProcessInformationLength,
    _Out_opt_ PULONG           ReturnLength
    );

typedef struct _PROCESS_HANDLE_TABLE_ENTRY_INFO {
    HANDLE 	HandleValue;
    ULONG_PTR  	HandleCount;
    ULONG_PTR  	PointerCount;
    ULONG 	GrantedAccess;
    ULONG 	ObjectTypeIndex;
    ULONG 	HandleAttributes;
    ULONG 	Reserved;
} PROCESS_HANDLE_TABLE_ENTRY_INFO, * PPROCESS_HANDLE_TABLE_ENTRY_INFO;

typedef struct _PROCESS_HANDLE_SNAPSHOT_INFORMATION
{
    ULONG_PTR NumberOfHandles;
    ULONG_PTR Reserved;
    PROCESS_HANDLE_TABLE_ENTRY_INFO Handles[1];
} PROCESS_HANDLE_SNAPSHOT_INFORMATION, * PPROCESS_HANDLE_SNAPSHOT_INFORMATION;

typedef enum _OBJECT_INFORMATION_CLASS {
    ObjectBasicInformation,
    ObjectNameInformation,
    ObjectTypeInformation,
    ObjectAllInformation,
    ObjectDataInformation

} OBJECT_INFORMATION_CLASS;

typedef NTSTATUS(NTAPI* pNtQueryObject)(
    HANDLE          Handle,
    OBJECT_INFORMATION_CLASS    ObjectInformationClass,
    PVOID           ObjectInformation,
    ULONG           ObjectInformationLength,
    PULONG          ReturnLength
    );

#define STATUS_INFO_LENGTH_MISMATCH ((NTSTATUS)0xC0000004L)
typedef struct _OBJECT_NAME_INFORMATION {
    UNICODE_STRING          Name;
    WCHAR                   NameBuffer[0];
} OBJECT_NAME_INFORMATION, * POBJECT_NAME_INFORMATION;
