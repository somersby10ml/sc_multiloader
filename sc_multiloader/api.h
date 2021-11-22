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

typedef enum _SYSTEM_INFORMATION_CLASS {
	SystemBasicInformation,                // 0
	SystemProcessorInformation,            // 1
	SystemPerformanceInformation,          // 2
	SystemTimeOfDayInformation,            // 3
	SystemNotImplemented1,                 // 4
	SystemProcessesAndThreadsInformation,  // 5
	SystemCallCounts,                      // 6
	SystemConfigurationInformation,        // 7
	SystemProcessorTimes,                  // 8
	SystemGlobalFlag,                      // 9
	SystemNotImplemented2,                 // 10
	SystemModuleInformation,               // 11
	SystemLockInformation,                 // 12
	SystemNotImplemented3,                 // 13
	SystemNotImplemented4,                 // 14
	SystemNotImplemented5,                 // 15
	SystemHandleInformation,               // 16
	SystemObjectInformation,               // 17
	SystemPagefileInformation,             // 18
	SystemInstructionEmulationCounts,      // 19
	SystemInvalidInfoClass1,               // 20
	SystemCacheInformation,                // 21
	SystemPoolTagInformation,              // 22
	SystemProcessorStatistics,             // 23
	SystemDpcInformation,                  // 24
	SystemNotImplemented6,                 // 25
	SystemLoadImage,                       // 26
	SystemUnloadImage,                     // 27
	SystemTimeAdjustment,                  // 28
	SystemNotImplemented7,                 // 29
	SystemNotImplemented8,                 // 30
	SystemNotImplemented9,                 // 31
	SystemCrashDumpInformation,            // 32
	SystemExceptionInformation,            // 33
	SystemCrashDumpStateInformation,       // 34
	SystemKernelDebuggerInformation,       // 35
	SystemContextSwitchInformation,        // 36
	SystemRegistryQuotaInformation,        // 37
	SystemLoadAndCallImage,                // 38
	SystemPrioritySeparation,              // 39
	SystemNotImplemented10,                // 40
	SystemNotImplemented11,                // 41
	SystemInvalidInfoClass2,               // 42
	SystemInvalidInfoClass3,               // 43
	SystemTimeZoneInformation,             // 44
	SystemLookasideInformation,            // 45
	SystemSetTimeSlipEvent,                // 46
	SystemCreateSession,                   // 47
	SystemDeleteSession,                   // 48
	SystemInvalidInfoClass4,               // 49
	SystemRangeStartInformation,           // 50
	SystemVerifierInformation,             // 51
	SystemAddVerifier,                     // 52
	SystemSessionProcessesInformation      // 53
} SYSTEM_INFORMATION_CLASS;

typedef NTSTATUS(NTAPI* pZwQuerySystemInformation) (
	_In_      SYSTEM_INFORMATION_CLASS SystemInformationClass,
	_Inout_   PVOID                    SystemInformation,
	_In_      ULONG                    SystemInformationLength,
	_Out_opt_ PULONG                   ReturnLength
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

typedef struct __PUBLIC_OBJECT_TYPE_INFORMATION {
	UNICODE_STRING TypeName;
	ULONG          Reserved[22];
} PUBLIC_OBJECT_TYPE_INFORMATION, * PPUBLIC_OBJECT_TYPE_INFORMATION;

typedef NTSTATUS(NTAPI* pNtQueryObject)(
	HANDLE          Handle,
	OBJECT_INFORMATION_CLASS    ObjectInformationClass,
	PVOID           ObjectInformation,
	ULONG           ObjectInformationLength,
	PULONG          ReturnLength
	);

typedef struct _OBJECT_NAME_INFORMATION {
	UNICODE_STRING          Name;
	WCHAR                   NameBuffer[1];
} OBJECT_NAME_INFORMATION, * POBJECT_NAME_INFORMATION;

typedef struct _SYSTEM_HANDLE_TABLE_ENTRY_INFO {
	ULONG ProcessId;
	UCHAR ObjectTypeNumber;
	UCHAR Flags;
	USHORT Handle;
	PVOID Object;
	ACCESS_MASK GrantedAccess;
} SYSTEM_HANDLE_TABLE_ENTRY_INFO;
typedef struct _SYSTEM_HANDLE_INFORMATION
{
	ULONG NumberOfHandles;
	SYSTEM_HANDLE_TABLE_ENTRY_INFO Handles[1];
} SYSTEM_HANDLE_INFORMATION;
