#pragma once
#pragma comment(linker, "/subsystem:windows")
#pragma comment(linker, "/ENTRY:Main")

#include <Windows.h>
#include <string>
#include "common.h"
#include "ntapi.h"

#include <vector>
#pragma comment(lib, "User32.lib")

namespace scmultiloader {

	using namespace System;
	using namespace System::Threading;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Diagnostics;
	using namespace System::IO;

	/// <summary>
	/// MyForm에 대한 요약입니다.
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form {
	public:
		MyForm(void) {
			InitializeComponent();
			//
			//TODO: 생성자 코드를 여기에 추가합니다.
			//
		}

	protected:
		/// <summary>
		/// 사용 중인 모든 리소스를 정리합니다.
		/// </summary>
		~MyForm() {
			if (components) {
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ btnRun;
	private: System::Windows::Forms::TextBox^ txtGamePath;
	protected:


	private: System::Windows::Forms::Button^ btnStart;
	private: System::Windows::Forms::Button^ btnStop;


	private: System::Windows::Forms::ListBox^ listBox1;
	private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ RemoveAllToolStripMenuItem;

	private: System::ComponentModel::IContainer^ components;
	protected:

	private:
		/// <summary>
		/// 필수 디자이너 변수입니다.
		/// </summary>


	#pragma region Windows Form Designer generated code
		/// <summary>
		/// 디자이너 지원에 필요한 메서드입니다. 
		/// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
		/// </summary>
		void InitializeComponent(void) {
			this->components = (gcnew System::ComponentModel::Container());
			this->btnRun = (gcnew System::Windows::Forms::Button());
			this->txtGamePath = (gcnew System::Windows::Forms::TextBox());
			this->btnStart = (gcnew System::Windows::Forms::Button());
			this->btnStop = (gcnew System::Windows::Forms::Button());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->RemoveAllToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->contextMenuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// btnRun
			// 
			this->btnRun->Location = System::Drawing::Point(12, 41);
			this->btnRun->Name = L"btnRun";
			this->btnRun->Size = System::Drawing::Size(84, 38);
			this->btnRun->TabIndex = 0;
			this->btnRun->Text = L"실행";
			this->btnRun->UseVisualStyleBackColor = true;
			this->btnRun->Click += gcnew System::EventHandler(this, &MyForm::btnRun_Click);
			// 
			// txtGamePath
			// 
			this->txtGamePath->Location = System::Drawing::Point(12, 12);
			this->txtGamePath->Name = L"txtGamePath";
			this->txtGamePath->Size = System::Drawing::Size(398, 23);
			this->txtGamePath->TabIndex = 1;
			// 
			// btnStart
			// 
			this->btnStart->Location = System::Drawing::Point(102, 41);
			this->btnStart->Name = L"btnStart";
			this->btnStart->Size = System::Drawing::Size(84, 38);
			this->btnStart->TabIndex = 2;
			this->btnStart->Text = L"시작";
			this->btnStart->UseVisualStyleBackColor = true;
			this->btnStart->Click += gcnew System::EventHandler(this, &MyForm::btnStart_Click);
			// 
			// btnStop
			// 
			this->btnStop->Location = System::Drawing::Point(192, 41);
			this->btnStop->Name = L"btnStop";
			this->btnStop->Size = System::Drawing::Size(84, 38);
			this->btnStop->TabIndex = 3;
			this->btnStop->Text = L"중지";
			this->btnStop->UseVisualStyleBackColor = true;
			this->btnStop->Click += gcnew System::EventHandler(this, &MyForm::btnStop_Click);
			// 
			// listBox1
			// 
			this->listBox1->ContextMenuStrip = this->contextMenuStrip1;
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 15;
			this->listBox1->Location = System::Drawing::Point(12, 84);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(398, 169);
			this->listBox1->TabIndex = 4;
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->RemoveAllToolStripMenuItem });
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(111, 26);
			// 
			// RemoveAllToolStripMenuItem
			// 
			this->RemoveAllToolStripMenuItem->Name = L"RemoveAllToolStripMenuItem";
			this->RemoveAllToolStripMenuItem->Size = System::Drawing::Size(110, 22);
			this->RemoveAllToolStripMenuItem->Text = L"지우기";
			this->RemoveAllToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::RemoveAllToolStripMenuItem_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(420, 265);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->btnStop);
			this->Controls->Add(this->btnStart);
			this->Controls->Add(this->txtGamePath);
			this->Controls->Add(this->btnRun);
			this->Font = (gcnew System::Drawing::Font(L"맑은 고딕", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
													  static_cast<System::Byte>(129)));
			this->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"StarCraft Multi-Loader v0.3";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::MyForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Resize += gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
			this->contextMenuStrip1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
	#pragma endregion

		Thread^ thread = nullptr;
		bool isThreadStop = false;

		pZwQueryInformationProcess ZwQueryInformationProcess = nullptr;
		pNtQueryObject NtQueryObject = nullptr;
		fnRtlNtStatusToDosError RtlNtStatusToDosError = nullptr;

		int txtGamePathPadding = 0;
		int listBoxMarginRight = 0;

	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {

		btnStop->Enabled = false;

		if (IsUserAdministrator() == false) {
			System::Windows::Forms::DialogResult result = MessageBox::Show("관리자 권한이 필요합니다. 관리자 권한으로 다시 실행하시겠습니까?", "알림", MessageBoxButtons::YesNo, MessageBoxIcon::Error);
			if (result == System::Windows::Forms::DialogResult::Yes) {
				try {
					Process^ process = gcnew Process();
					process->StartInfo->FileName = Application::ExecutablePath;
					process->StartInfo->Arguments = "-admin";
					process->StartInfo->Verb = "runas";
					process->Start();
				}
				catch (...) {

				}
			}
			Application::Exit();
		}

		// Resize
		txtGamePathPadding = this->Width - txtGamePath->Width;
		listBoxMarginRight = this->Width - listBox1->Width;
		//MessageBox::Show(listBoxMarginRight.ToString());

		String^ gamePath = GetGamePath();
		if (gamePath != nullptr)
			txtGamePath->Text = gamePath;
		else
			txtGamePath->Text = "StarCraft.exe 경로를 찾을수 없습니다.";

		const char* szNTDLL = _T("ntdll.dll");
		DWORD Error = 0UL;

		HMODULE hNTDLL = LoadLibrary(szNTDLL);
		if (hNTDLL == 0) {
			hNTDLL = GetModuleHandle(szNTDLL);
			if (hNTDLL == 0) {
				MessageBox::Show("Ntdll.dll 을 로드할수 없습니다.", "알림", MessageBoxButtons::OK, MessageBoxIcon::Error);
				Application::Exit();
				return;
			}
		}

		ZwQueryInformationProcess = (pZwQueryInformationProcess)GetProcAddress(hNTDLL, "ZwQueryInformationProcess");
		NtQueryObject = (pNtQueryObject)GetProcAddress(hNTDLL, "NtQueryObject");
		RtlNtStatusToDosError = (fnRtlNtStatusToDosError)GetProcAddress(hNTDLL, "RtlNtStatusToDosError");
		if (!ZwQueryInformationProcess || !NtQueryObject || !RtlNtStatusToDosError) {
			MessageBox::Show("API 주소를 불러올수 없습니다.", "알림", MessageBoxButtons::OK, MessageBoxIcon::Error);
			Application::Exit();
			return;
		}
	}
	private: System::Void RemoveAllToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		listBox1->Items->Clear();
	}
	private: System::Void btnRun_Click(System::Object^ sender, System::EventArgs^ e) {
		// 실행
		if (File::Exists(txtGamePath->Text) == false) {
			MessageBox::Show(txtGamePath->Text + "\r\n해당경로에 파일이 없습니다.", "알림", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
		try {
			Process^ process = gcnew Process();
			process->Start(txtGamePath->Text, "-launch");
		}
		catch (Exception^ e) {
			MessageBox::Show(e->Message, "알림", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
	}
	private: System::Void btnStart_Click(System::Object^ sender, System::EventArgs^ e) {
		// 시작
		btnStart->Enabled = false;
		btnStop->Enabled = true;

		thread = gcnew Thread(gcnew ThreadStart(this, &MyForm::MoniterThread));
		thread->IsBackground = true;
		thread->Start();
	}

		   delegate int listViewAddItemDelegate(String^ text);
	private: int listBoxAddItem(String^ text) {
		if (listBox1->InvokeRequired) {
			return (int)this->Invoke(gcnew listViewAddItemDelegate(this, &MyForm::listBoxAddItem), text);
		}
		else {
			String^ fullText = "[" + DateTime::Now.ToString("HH:mm:ss") + "] " + text;
			return listBox1->Items->Add(fullText);
		}
	}

	private: System::Void MoniterThread() {
		isThreadStop = false;

		listBoxAddItem("Start...");
		while (isThreadStop == false) {
			Thread::Sleep(1);

			std::unique_ptr<void, deleter> hSnapshot(
				CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL),
				&CloseHandle);

			if (hSnapshot.get() == INVALID_HANDLE_VALUE)
				return;

			PROCESSENTRY32 entry = { 0, };
			entry.dwSize = sizeof(PROCESSENTRY32);
			if (Process32First(hSnapshot.get(), &entry)) {
				do {
					if (_tcsicmp(entry.szExeFile, _T("StarCraft.exe")) == 0) {

						// Open Process
						std::unique_ptr<void, deleter> process(OpenProcess(MAXIMUM_ALLOWED, false, entry.th32ProcessID), &CloseHandle);
						if (process.get() == nullptr)
							continue;

						std::vector<unsigned char> buffer;

						ULONG dwLength = 0;
						NTSTATUS status = ZwQueryInformationProcess(process.get(), ProcessHandleInformation, buffer.data(), buffer.size(), &dwLength);
						while (status == STATUS_INFO_LENGTH_MISMATCH) {
							buffer.resize(dwLength);
							status = ZwQueryInformationProcess(process.get(), ProcessHandleInformation, buffer.data(), buffer.size(), &dwLength);
						}
						if (status == STATUS_PROCESS_IS_TERMINATING)
							continue;

						if (status != ERROR_SUCCESS) {
							std::string str = getErrorString(RtlNtStatusToDosError(status));
							std::string message = format("PID:%d ZwQueryInformationProcess 오류코드: %08X 오류내용: %s", entry.th32ProcessID, status, str.c_str()).c_str();
							listBoxAddItem(gcnew String(message.c_str()));
							continue;
						}

						PPROCESS_HANDLE_SNAPSHOT_INFORMATION pInformation = (PPROCESS_HANDLE_SNAPSHOT_INFORMATION)buffer.data();
						for (ULONG i = 0; i < pInformation->NumberOfHandles; i++) {
							HANDLE handle = pInformation->Handles[i].HandleValue;
							DWORD dwObjectResult = 0;
							HANDLE copyHandle = nullptr;
							status = DuplicateHandle(process.get(), handle, GetCurrentProcess(), &copyHandle, MAXIMUM_ALLOWED, false, DUPLICATE_SAME_ACCESS);
							if (status == false)
								continue;

							// 핸들정보 조회
							std::vector<unsigned char> objectBuf;
							status = NtQueryObject(copyHandle, ObjectNameInformation, objectBuf.data(), objectBuf.size(), &dwObjectResult);
							while (status == STATUS_INFO_LENGTH_MISMATCH) {
								objectBuf.resize(dwObjectResult);
								status = NtQueryObject(copyHandle, ObjectNameInformation, objectBuf.data(), objectBuf.size(), &dwObjectResult);
							}
							if (status == STATUS_PIPE_DISCONNECTED)
								continue;

							if (status != ERROR_SUCCESS) {
								std::string str = getErrorString(RtlNtStatusToDosError(status));
								std::string message = format("PID:%d NtQueryObject 오류코드: %08X 오류내용: %s", entry.th32ProcessID, status, str.c_str()).c_str();
								listBoxAddItem(gcnew String(message.c_str()));
								continue;
							}
							CloseHandle(copyHandle);

							POBJECT_NAME_INFORMATION pObjectInfo = (POBJECT_NAME_INFORMATION)objectBuf.data();
							if (pObjectInfo->Name.Length) {
								if (wcsstr(pObjectInfo->Name.Buffer, L"Starcraft Check For Other Instances")) {
									status = DuplicateHandle(process.get(), handle, GetCurrentProcess(), &copyHandle, MAXIMUM_ALLOWED, false, DUPLICATE_CLOSE_SOURCE);
									CloseHandle(copyHandle);
									listBoxAddItem(String::Format("StarCraft.exe({0}) handle:{1} Remove... OK", gcnew array<System::Object^> { entry.th32ProcessID, (int)copyHandle }));
								}
							}
						}
					}
				} while (Process32Next(hSnapshot.get(), &entry));
			}
		}
	}
	private: System::Void btnStop_Click(System::Object^ sender, System::EventArgs^ e) {
		listBoxAddItem("Stoping...");
		btnStart->Enabled = true;
		btnStop->Enabled = false;
		isThreadStop = true;
		if (thread != nullptr)
			thread->Join();
		listBoxAddItem("Stoped !!");
	}
	private: System::Void MyForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
		isThreadStop = true;
		if (thread != nullptr)
			thread->Join();
	}
	private: System::Void MyForm_Resize(System::Object^ sender, System::EventArgs^ e) {
		txtGamePath->Width = this->Width - txtGamePathPadding;
		listBox1->Width = this->Width - listBoxMarginRight;
	}
	};
}
