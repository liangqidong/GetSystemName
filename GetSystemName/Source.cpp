#include "GetSystemName.h"

int main()
{
	//getSystemName();
	GetSystemName gs;
	char windowsName[MAX_PATH] = { 0 };
	unsigned int len = MAX_PATH;
	gs.GetWindowsName(windowsName, len);

	return 0;
}









