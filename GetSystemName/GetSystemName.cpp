#include "GetSystemName.h"



GetSystemName::GetSystemName()
{
	typedef void(__stdcall*NTPROC)(DWORD*, DWORD*, DWORD*);
	HINSTANCE hinst = LoadLibraryA("ntdll.dll");
	NTPROC proc = (NTPROC)GetProcAddress(hinst, "RtlGetNtVersionNumbers");
	proc(&m_dwMajor, &m_dwMinor, &m_dwBuildNumber);
	GetSystemInfo(&m_systemInfo);

	m_funVector.push_back(std::bind(&GetSystemName::MicrosoftWindowsNT4_0, this, std::placeholders::_1));
	m_funVector.push_back(std::bind(&GetSystemName::MicrosoftWindows95, this, std::placeholders::_1));
	m_funVector.push_back(std::bind(&GetSystemName::MicrosoftWindows98, this, std::placeholders::_1));
	m_funVector.push_back(std::bind(&GetSystemName::MicrosoftWindowsMe, this, std::placeholders::_1));
	m_funVector.push_back(std::bind(&GetSystemName::MicrosoftWindows2000, this, std::placeholders::_1));
	m_funVector.push_back(std::bind(&GetSystemName::MicrosoftWindowsXP, this, std::placeholders::_1));
	m_funVector.push_back(std::bind(&GetSystemName::MicrosoftWindowsXPProfessionalX64Edition, this, std::placeholders::_1));
	m_funVector.push_back(std::bind(&GetSystemName::MicrosoftWindowsServer2003, this, std::placeholders::_1));
	m_funVector.push_back(std::bind(&GetSystemName::MicrosoftWindowsServer2003R2, this, std::placeholders::_1));
	m_funVector.push_back(std::bind(&GetSystemName::MicrosoftWindowsVista, this, std::placeholders::_1));
	m_funVector.push_back(std::bind(&GetSystemName::MicrosoftWindowsServer2008, this, std::placeholders::_1));
	m_funVector.push_back(std::bind(&GetSystemName::MicrosoftWindowsServer2008R2, this, std::placeholders::_1));
	m_funVector.push_back(std::bind(&GetSystemName::MicrosoftWindows7, this, std::placeholders::_1));
	m_funVector.push_back(std::bind(&GetSystemName::MicrosoftWindows8, this, std::placeholders::_1));
	m_funVector.push_back(std::bind(&GetSystemName::MicrosoftWindowsServer2012, this, std::placeholders::_1));
	
}


GetSystemName::~GetSystemName()
{
}

long GetSystemName::GetWindowsName(char* windowsName, unsigned int& nameLen)
{
	long errorCode = -1;
	if (MicrosoftWindows8_1(m_dwMajor, m_dwMinor))
	{
		errorCode = 0;
		goto END;
	}

	if (MicrosoftWindows10(m_dwMajor, m_dwMinor))
	{
		errorCode = 0;
		goto END;
	}
	OSVERSIONINFOEX os;
	if (!GetSystemVersion(os))
	{
		errorCode = -1;
		m_vname = "版本获取失败";
		goto END;
	}
	for (auto it = m_funVector.begin(); it != m_funVector.end(); it++)
	{
		if ((*it)(os))
		{
			errorCode = 0;
			goto END;
		}
		
	}
	m_vname = "未知操作系统";
END:
	if (nameLen < m_vname.length())
	{
		return -1;
	}
	nameLen = m_vname.length();
	memcpy(windowsName, m_vname.c_str(), nameLen);
	return errorCode;
}

bool GetSystemName::GetSystemVersion(OSVERSIONINFOEX& os)
{
	return GetVersionEx((OSVERSIONINFO *)&os);
}

bool GetSystemName::MicrosoftWindows8_1(DWORD dwMajor, DWORD dwMinor)
{
	bool isWindows8_1 = false;
	if (dwMajor == 6 && dwMinor == 3)	//win 8.1
	{
		m_vname = "Microsoft Windows 8.1";
		printf_s("此电脑的版本为:%s\n", m_vname.c_str());
		isWindows8_1 = true;
	}
	return isWindows8_1;
}

bool GetSystemName::MicrosoftWindows10(DWORD dwMajor, DWORD dwMinor)
{
	bool isWindows10 = false;
	if (dwMajor == 10 && dwMinor == 0)
	{
		m_vname = "Microsoft Windows 10";
		printf_s("此电脑的版本为:%s\n", m_vname.c_str());
		isWindows10 = true;
	}
	return isWindows10;
}

bool GetSystemName::MicrosoftWindowsNT4_0(OSVERSIONINFOEX os)
{
	bool isWindowsNT4_0 = false;
	if (4 == os.dwMajorVersion &&
		0 == os.dwMinorVersion &&
		VER_PLATFORM_WIN32_NT == os.dwPlatformId)
	{
		m_vname = "Microsoft Windows NT 4.0";
		printf_s("此电脑的版本为:%s\n", m_vname.c_str());
		isWindowsNT4_0 = true;
	}
	return isWindowsNT4_0;
}

bool GetSystemName::MicrosoftWindows95(OSVERSIONINFOEX os)
{
	bool isWindows95 = false;
	if (4 == os.dwMajorVersion &&
		0 == os.dwMinorVersion &&
		VER_PLATFORM_WIN32_WINDOWS == os.dwPlatformId)
	{
		m_vname = "Microsoft Windows NT 4.0";
		printf_s("此电脑的版本为:%s\n", m_vname.c_str());
		isWindows95 = true;
	}
	return isWindows95;
}

bool GetSystemName::MicrosoftWindows98(OSVERSIONINFOEX os)
{
	bool isWindows98 = false;
	if (4 == os.dwMajorVersion &&
		10 == os.dwMinorVersion )
	{
		m_vname = "Microsoft Windows 98";
		printf_s("此电脑的版本为:%s\n", m_vname.c_str());
		isWindows98 = true;
	}
	return isWindows98;
}

bool GetSystemName::MicrosoftWindowsMe(OSVERSIONINFOEX os)
{
	bool isWindowsMe = false;
	if (4 == os.dwMajorVersion &&
		90 == os.dwMinorVersion)
	{
		m_vname = "Microsoft Windows Me";
		printf_s("此电脑的版本为:%s\n", m_vname.c_str());
		isWindowsMe = true;
	}
	return isWindowsMe;
}

bool GetSystemName::MicrosoftWindows2000(OSVERSIONINFOEX os)
{
	bool isWindows2000 = false;
	if (5 == os.dwMajorVersion &&
		0 == os.dwMinorVersion)
	{
		m_vname = "Microsoft Windows 2000";
		printf_s("此电脑的版本为:%s\n", m_vname.c_str());
		isWindows2000 = true;
	}
	return isWindows2000;
}

bool GetSystemName::MicrosoftWindowsXP(OSVERSIONINFOEX os)
{
	bool isWindowsXP = false;
	if (5 == os.dwMajorVersion &&
		1 == os.dwMinorVersion)
	{
		m_vname = "Microsoft Windows XP";
		printf_s("此电脑的版本为:%s\n", m_vname.c_str());
		isWindowsXP = true;
	}
	return isWindowsXP;
}

bool GetSystemName::MicrosoftWindowsXPProfessionalX64Edition(OSVERSIONINFOEX os)
{
	bool isWindowsXPProfessionalX64Edition = false;
	if (5 == os.dwMajorVersion &&
		2 == os.dwMinorVersion &&
		VER_NT_WORKSTATION ==  os.wProductType &&
		PROCESSOR_ARCHITECTURE_AMD64  == m_systemInfo.wProcessorArchitecture)	//win 10
	{
		m_vname = "Microsoft Windows XP Professional x64 Edition";
		printf_s("此电脑的版本为:%s\n", m_vname.c_str());
		isWindowsXPProfessionalX64Edition = true;
	}
	return isWindowsXPProfessionalX64Edition;
}

bool GetSystemName::MicrosoftWindowsServer2003(OSVERSIONINFOEX os)
{
	bool isWindowsServer2003 = false;
	if (5 == os.dwMajorVersion &&
		2 == os.dwMinorVersion &&
		GetSystemMetrics(SM_SERVERR2) == 0)	
	{
		m_vname = "Microsoft Windows Server 2003";
		printf_s("此电脑的版本为:%s\n", m_vname.c_str());
		isWindowsServer2003 = true;
	}
	return isWindowsServer2003;
}

bool GetSystemName::MicrosoftWindowsServer2003R2(OSVERSIONINFOEX os)
{
	bool isWindowsServer2003R2 = false;
	if (5 == os.dwMajorVersion &&
		2 == os.dwMinorVersion &&
		GetSystemMetrics(SM_SERVERR2) != 0)
	{
		m_vname = "Microsoft Windows Server 2003 R2";
		printf_s("此电脑的版本为:%s\n", m_vname.c_str());
		isWindowsServer2003R2 = true;
	}
	return isWindowsServer2003R2;
}

bool GetSystemName::MicrosoftWindowsVista(OSVERSIONINFOEX os)
{
	bool isWindowsVista = false;
	if (6 == os.dwMajorVersion &&
		0 == os.dwMinorVersion &&
		VER_NT_WORKSTATION  == os.wProductType)
	{
		m_vname = "Microsoft Windows Vista";
		printf_s("此电脑的版本为:%s\n", m_vname.c_str());
		isWindowsVista = true;
	}
	return isWindowsVista;
}

bool GetSystemName::MicrosoftWindowsServer2008(OSVERSIONINFOEX os)
{
	bool isWindowsServer2008 = false;
	if (6 == os.dwMajorVersion &&
		0 == os.dwMinorVersion &&
		VER_NT_WORKSTATION != os.wProductType)
	{
		m_vname = "Microsoft Windows Server 2008";
		printf_s("此电脑的版本为:%s\n", m_vname.c_str());
		isWindowsServer2008 = true;
	}
	return isWindowsServer2008;
}

bool GetSystemName::MicrosoftWindowsServer2008R2(OSVERSIONINFOEX os)
{
	bool isWindowsServer2008R2 = false;
	if (6 == os.dwMajorVersion &&
		1 == os.dwMinorVersion &&
		VER_NT_WORKSTATION != os.wProductType)
	{
		m_vname = "Microsoft Windows Server 2008 R2";
		printf_s("此电脑的版本为:%s\n", m_vname.c_str());
		isWindowsServer2008R2 = true;
	}
	return isWindowsServer2008R2;
}

bool GetSystemName::MicrosoftWindows7(OSVERSIONINFOEX os)
{
	bool isWindows7 = false;
	if (6 == os.dwMajorVersion &&
		1 == os.dwMinorVersion &&
		VER_NT_WORKSTATION == os.wProductType)
	{
		m_vname = "Microsoft Windows 7";
		printf_s("此电脑的版本为:%s\n", m_vname.c_str());
		isWindows7 = true;
	}
	return isWindows7;
}

bool GetSystemName::MicrosoftWindows8(OSVERSIONINFOEX os)
{
	bool isWindows8 = false;
	if (6 == os.dwMajorVersion &&
		2 == os.dwMinorVersion &&
		VER_NT_WORKSTATION == os.wProductType)
	{
		m_vname = "Microsoft Windows 8";
		printf_s("此电脑的版本为:%s\n", m_vname.c_str());
		isWindows8 = true;
	}
	return isWindows8;
}

bool GetSystemName::MicrosoftWindowsServer2012(OSVERSIONINFOEX os)
{
	bool isWindowsServer2012 = false;
	if (6 == os.dwMajorVersion &&
		2 == os.dwMinorVersion &&
		VER_NT_WORKSTATION != os.wProductType)
	{
		m_vname = "Microsoft Windows Server 2012";
		printf_s("此电脑的版本为:%s\n", m_vname.c_str());
		isWindowsServer2012 = true;
	}
	return isWindowsServer2012;
}
