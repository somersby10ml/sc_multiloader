#include "MyForm.h"



using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void Main(array<String^>^ args) {

	if (args->Length > 0 && String::Compare(args[0], "-admin") == 0) {
		if (IsUserAdministrator() == false) {
			MessageBox::Show("������ �������� ������ �����Ͽ����ϴ�. ���α׷��� ����˴ϴ�.", "�˸�", MessageBoxButtons::YesNo, MessageBoxIcon::Error);
			return;
		}
	}

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	scmultiloader::MyForm form;
	Application::Run(% form);
}

//
//void SampleTemplate::MyForm::MarshalString(String^ s, std::string& os) {
//	using namespace Runtime::InteropServices;
//	const char* chars =
//		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
//	os = chars;
//	Marshal::FreeHGlobal(IntPtr((void*)chars));
//}
//
//void SampleTemplate::MyForm::MarshalString(String^ s, std::wstring& os) {
//	using namespace Runtime::InteropServices;
//	const wchar_t* chars =
//		(const wchar_t*)(Marshal::StringToHGlobalUni(s)).ToPointer();
//	os = chars;
//	Marshal::FreeHGlobal(IntPtr((void*)chars));
//}