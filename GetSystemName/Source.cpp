﻿#include<string>
#include <windows.h>
#pragma warning(disable:4996)
std::string getSystemName() 
{
	std::string vname;	//先判断是否为win8.1或win10
	typedef void(__stdcall*NTPROC)(DWORD*, DWORD*, DWORD*);
	HINSTANCE hinst = LoadLibraryA("ntdll.dll");
	DWORD dwMajor, dwMinor, dwBuildNumber;
	NTPROC proc = (NTPROC)GetProcAddress(hinst, "RtlGetNtVersionNumbers");
	proc(&dwMajor, &dwMinor, &dwBuildNumber);
	if (dwMajor == 6 && dwMinor == 3)	//win 8.1
	{
		vname = "Microsoft Windows 8.1";
		printf_s("此电脑的版本为:%s\n", vname.c_str());
		return vname;
	}
	if (dwMajor == 10 && dwMinor == 0)	//win 10
	{
		vname = "Microsoft Windows 10";	
		printf_s("此电脑的版本为:%s\n", vname.c_str());
		return vname;	
	}	
	// 下面判断不能Win Server，因为本人还未有这种系统的机子，暂时不给出
	// 判断win8.1以下的版本
	 SYSTEM_INFO info;
	// 用SYSTEM_INFO结构判断64位AMD处理器 
	 GetSystemInfo(&info);
	// 调用GetSystemInfo函数填充结构 
	 OSVERSIONINFOEX os;
	 os.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	 if (GetVersionEx((OSVERSIONINFO *)&os))
	 {
		 //下面根据版本信息判断操作系统名称
		 switch (os.dwMajorVersion)
		 {
			 //判断主版本号 
			 case 4:
				switch (os.dwMinorVersion)
				{
					//判断次版本号	
					case 0:
						if (os.dwPlatformId == VER_PLATFORM_WIN32_NT)
								vname = "Microsoft Windows NT 4.0";	//1996年7月发布
						else if (os.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
								vname = "Microsoft Windows 95";
						break;
					case 10:
						vname = "Microsoft Windows 98";
						break;
					case 90:
						vname = "Microsoft Windows Me";
						break;
				}
				break;
			case 5:
				switch (os.dwMinorVersion)
				{
					//再比较dwMinorVersion的值
					case 0:
						vname = "Microsoft Windows 2000";	//1999年12月发布 
						break;
					case 1:
						vname = "Microsoft Windows XP";	//2001年8月发布  
						break;
					case 2:
						if (os.wProductType == VER_NT_WORKSTATION &&
							info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
							vname = "Microsoft Windows XP Professional x64 Edition";
						else if (GetSystemMetrics(SM_SERVERR2) == 0)
							vname = "Microsoft Windows Server 2003";	//2003年3月发布
						else if (GetSystemMetrics(SM_SERVERR2) != 0)
							vname = "Microsoft Windows Server 2003 R2";
						break;
				}
				break;
			case 6:
				switch (os.dwMinorVersion)
				{
					case 0:
						if (os.wProductType == VER_NT_WORKSTATION)
							vname = "Microsoft Windows Vista";
						else
							vname = "Microsoft Windows Server 2008";	//服务器版本   
					break;
					case 1:
						if (os.wProductType == VER_NT_WORKSTATION)
							vname = "Microsoft Windows 7";
						else
							vname = "Microsoft Windows Server 2008 R2";
					break;
					case 2:
						if (os.wProductType == VER_NT_WORKSTATION)
							vname = "Microsoft Windows 8";
						else
							vname = "Microsoft Windows Server 2012";
						break;
					}
				break;
			default:
				vname = "未知操作系统";
			}
		 printf_s("此电脑的版本为:%s\n", vname.c_str());
		return vname;
	 }
	 else
		 printf_s("版本获取失败\n");
	return vname;
}

int main()
{
	getSystemName();
	return 0;
}









