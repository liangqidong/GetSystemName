#ifndef GET_SYSTEM_NAME_H
#define GET_SYSTEM_NAME_H
#include<string>
#include <vector>
#include <functional>

#include <windows.h>
#pragma warning(disable:4996)

class GetSystemName
{
public:
	GetSystemName();
	~GetSystemName();
	long GetWindowsName(char* windowsName,unsigned int& nameLen);

private:
	bool GetSystemVersion(OSVERSIONINFOEX& os);
	bool MicrosoftWindows8_1(DWORD dwMajor, DWORD dwMinor);
	bool MicrosoftWindows10(DWORD dwMajor, DWORD dwMinor);
	bool MicrosoftWindowsNT4_0(OSVERSIONINFOEX os);
	bool MicrosoftWindows95(OSVERSIONINFOEX os);
	bool MicrosoftWindows98(OSVERSIONINFOEX os);
	bool MicrosoftWindowsMe(OSVERSIONINFOEX os);
	bool MicrosoftWindows2000(OSVERSIONINFOEX os);
	bool MicrosoftWindowsXP(OSVERSIONINFOEX os);
	bool MicrosoftWindowsXPProfessionalX64Edition(OSVERSIONINFOEX os);
	bool MicrosoftWindowsServer2003(OSVERSIONINFOEX os);
	bool MicrosoftWindowsServer2003R2(OSVERSIONINFOEX os);
	bool MicrosoftWindowsVista(OSVERSIONINFOEX os);
	bool MicrosoftWindowsServer2008(OSVERSIONINFOEX os);
	bool MicrosoftWindowsServer2008R2(OSVERSIONINFOEX os);
	bool MicrosoftWindows7(OSVERSIONINFOEX os);
	bool MicrosoftWindows8(OSVERSIONINFOEX os);
	bool MicrosoftWindowsServer2012(OSVERSIONINFOEX os);

	std::string m_vname;
	DWORD m_dwMajor;
	DWORD m_dwMinor;
	DWORD m_dwBuildNumber;
	SYSTEM_INFO m_systemInfo;
	std::vector<std::function<bool(OSVERSIONINFOEX os)>>	m_funVector;
};

#endif//GET_SYSTEM_NAME_H

