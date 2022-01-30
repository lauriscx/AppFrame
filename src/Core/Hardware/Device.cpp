#include "Device.h"
#include <thread>

#if defined (WINDOWS) | defined (__WIN32__) | defined (__WIN32) | defined (_MSC_VER)
#include <windows.h>//This include must be first
#include <shellapi.h>
#include <intrin.h>
#include <winnt.h>
#include <fileapi.h>
#include <array>
#include <sysinfoapi.h>
#include <winreg.h>

const char * AppFrame::Device::GetDeviceModel() {
	std::string deviceModel;
	/*HKEY hKey;
	char buf[255] = { 0 };
	DWORD dwType = 0;
	DWORD dwBufSize = sizeof(buf);
	try {
		if (RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("HARDWARE\\DESCRIPTION\\System\\BIOS"), &hKey) == ERROR_SUCCESS) {
			dwType = REG_SZ;
			if (RegQueryValueEx(hKey, TEXT("SystemProductName"), NULL, NULL, (LPBYTE)buf, &dwBufSize) == ERROR_SUCCESS) {
				deviceModel = buf;
			}
			RegCloseKey(hKey);
		}
	}
	catch (...) {}*/
	return deviceModel.c_str();
}
const char * AppFrame::Device::GetDeviceOS() {
	std::string OSVersion;

	/*OSVERSIONINFOEX  versionInfo;
	versionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	OSVERSIONINFO*  pVersionInfo = (POSVERSIONINFO)&versionInfo;
	if (::GetVersionEx(pVersionInfo))
	{
		OSVersion += versionInfo.dwMajorVersion;
		OSVersion += ".";
		OSVersion += versionInfo.dwMinorVersion;
		OSVersion += " (";
		OSVersion += versionInfo.dwBuildNumber;
		OSVersion += ")/n";
	}*/

	return OSVersion.c_str();
}
const char * AppFrame::Device::GetCPUModel() {
	std::string cpu;

	/*std::array<int, 4> cpuId = {};
	__cpuid(cpuId.data(), 0);
	int nIds = cpuId[0];

	std::vector<std::array<int, 4>> data;
	for (int i = 0; i <= nIds; i++)
	{
		__cpuidex(cpuId.data(), i, 0);
		data.push_back(cpuId);
	}
	char vendor[0x20];
	memset(vendor, 0, sizeof(vendor));
	*reinterpret_cast<int*>(vendor) = data[0][1];
	*reinterpret_cast<int*>(vendor + 4) = data[0][3];
	*reinterpret_cast<int*>(vendor + 8) = data[0][2];

	cpu += "Vendor: ";
	cpu += vendor;
	cpu += "\n";

	__cpuid(cpuId.data(), 0x80000000);
	const unsigned int nExIds = cpuId[0];

	std::vector<std::array<int, 4>> extdata;
	for (unsigned int i = 0x80000000; i <= nExIds; i++)
	{
		__cpuidex(cpuId.data(), i, 0);
		extdata.push_back(cpuId);
	}

	char brand[0x40];
	memset(brand, 0, sizeof(brand));
	if (nExIds >= 0x80000004)
	{
		memcpy(brand, extdata[2].data(), sizeof(cpuId));
		memcpy(brand + 16, extdata[3].data(), sizeof(cpuId));
		memcpy(brand + 32, extdata[4].data(), sizeof(cpuId));

		cpu += "Brand: ";
		cpu += brand;
		cpu += "\n";
	}

	__cpuid(cpuId.data(), 0x80000006);
	cpu += "CacheLineSize: ";
	cpu += cpuId[2] & 0xFF;;
	cpu += "\n";*/

	return cpu.c_str();
}
const char * AppFrame::Device::GetGPUModel() {
	std::string GPUInfo;

	/*HKEY keyServ;
	HKEY keyEnum;
	HKEY key;
	HKEY key2;
	LONG lResult;//LONG-Type Variable-Save Function Return Value  

	//Query all subkeys under "SYSTEM\\CurrentControlSet\Services" and save them to keyServ  
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Services"), 0, KEY_READ, &keyServ);
	if (ERROR_SUCCESS != lResult)
		return "";


	//Query all subkeys under "SYSTEM\\CurrentControlSet\\Enum" and save them to keyEnum  
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Enum"), 0, KEY_READ, &keyEnum);
	if (ERROR_SUCCESS != lResult)
		return "";

	int i = 0, count = 0;
	DWORD size = 0, type = 0;
	for (;; ++i)
	{
		Sleep(5);
		size = 512;
		TCHAR name[512] = { 0 };//Save the field names of subitems under keyServ  

		//Enumerate each subitem field under keyServ one by one and save it in name  
		lResult = RegEnumKeyEx(keyServ, i, name, &size, NULL, NULL, NULL, NULL);

		//Subitems to be read do not exist, that is, keyServ's subitems jump out of the loop when they are all traversed  
		if (lResult == ERROR_NO_MORE_ITEMS)
			break;

		//Open the keyServ subentry field and save the value of the field identified by name to key  
		lResult = RegOpenKeyEx(keyServ, name, 0, KEY_READ, &key);
		if (lResult != ERROR_SUCCESS)
		{
			RegCloseKey(keyServ);
			return "";
		}


		size = 512;
		//The field under query key is the subkey field name of Group saved to name  
		lResult = RegQueryValueEx(key, TEXT("Group"), 0, &type, (LPBYTE)name, &size);
		if (lResult == ERROR_FILE_NOT_FOUND)
		{
			//The? Key does not exist  
			RegCloseKey(key);
			continue;
		};



		//If the name queried is not Video, the key is not a graphics card driver.  
		if (strcmp(TEXT("Video"), name) != 0)
		{
			RegCloseKey(key);
			continue;     //Return to the for loop  
		};

		//If the program continues to execute, the information about the graphics card has been found, so after the following code is executed, break the first for loop, and the function returns.  
		lResult = RegOpenKeyEx(key, TEXT("Enum"), 0, KEY_READ, &key2);
		RegCloseKey(key);
		key = key2;
		size = sizeof(count);
		lResult = RegQueryValueEx(key, TEXT("Count"), 0, &type, (LPBYTE)&count, &size);//Query Count field (number of graphics cards)  

		GPUInfo += "GPU count: ";
		GPUInfo += count;//Number of saved graphics cards  
		GPUInfo += "\n";

		for (int j = 0; j < count; ++j)
		{
			TCHAR sz[512] = { 0 };
			TCHAR name[64] = { 0 };
			wsprintf(name, TEXT("%d"), j);
			size = sizeof(sz);
			lResult = RegQueryValueEx(key, name, 0, &type, (LPBYTE)sz, &size);


			lResult = RegOpenKeyEx(keyEnum, sz, 0, KEY_READ, &key2);
			if (ERROR_SUCCESS)
			{
				RegCloseKey(keyEnum);
				return "";
			}


			size = sizeof(sz);
			lResult = RegQueryValueEx(key2, TEXT("FriendlyName"), 0, &type, (LPBYTE)sz, &size);
			if (lResult == ERROR_FILE_NOT_FOUND)
			{
				size = sizeof(sz);
				lResult = RegQueryValueEx(key2, TEXT("DeviceDesc"), 0, &type, (LPBYTE)sz, &size);

				GPUInfo += "GPU[";
				GPUInfo += j;
				GPUInfo += "]: ";
				GPUInfo += sz;//Save the name of the video card   
				GPUInfo += "\n";
			};
			RegCloseKey(key2);
			key2 = NULL;
		};
		RegCloseKey(key);
		key = NULL;
		break;
	}*/
	return GPUInfo.c_str();
}
const char * AppFrame::Device::GetRegion() {
	//Get a GEOID by calling
	//LCID LangId = GetUserDefaultLCID();
	//GEOID id = GetUserGeoID(GEOCLASS_NATION);

	std::string ISOcodeW;

	//GetGeoInfo(id, GEO_FRIENDLYNAME, &ISOcodeW[0], 3, LangId);
	//Pass the GEOID to GetGeoInfo() along with GEO_FRIENDLYNAME to fetch the string in the language specified in LangId(GetUserDefaultLCID() for the current)
	return ISOcodeW.c_str();
}
unsigned int AppFrame::Device::GetHardwareConcurrency() {
	return std::thread::hardware_concurrency();
}
const char * AppFrame::Device::GetCurrency() {
	/*LCID LangId = GetUserDefaultLCID();
	GEOID id = GetUserGeoID(GEOCLASS_NATION);

	CURRENCYFMTA lpFormat;
	std::string currency;
	int currencyID = 0;

	int SomeSortOfID = GetCurrencyFormatA(LangId,	0, 0, &lpFormat, &currency[0], currencyID);*/

	std::string sout;
	//::GetCurrencyFormat(LOCALE_USER_DEFAULT, LOCALE_NOUSEROVERRIDE, "", NULL, &sout[0], SomeSortOfID);
	return sout.c_str();
}
const char * AppFrame::Device::GetDeviceLanguage() {
	return std::locale().name().c_str();
}
int AppFrame::Device::GetRAMMemory() {
	unsigned __int64 memory;
	GetPhysicallyInstalledSystemMemory(&memory);
	return memory;
	return 0;
}
int AppFrame::Device::GetHardMemory() {
	/*unsigned __int64 totalSpace;
	unsigned __int64 freeSpace;
	return ::GetDiskFreeSpaceEx("c:\\", nullptr, reinterpret_cast<ULARGE_INTEGER*>(&totalSpace), reinterpret_cast<ULARGE_INTEGER*>(&freeSpace));
	return totalSpace;*/
	return 0;
}
int AppFrame::Device::GetScreenWidth() {
	/*RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	return desktop.right;*/
	return 0;
}
int AppFrame::Device::GetScreenHeight() {
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);

	return desktop.bottom;
}
int AppFrame::Device::GetInputType() {
	return 0;
}

void AppFrame::Device::Vibrate(int sec) {
}

void AppFrame::Device::ShowPopup(const char * title, const char * desc, const char * button1, const char * button2) {
	//MessageBox(NULL, desc, title, MB_OK | MB_ICONQUESTION);
}

void AppFrame::Device::AddNotification(const char * title, const char * desc, const char * image, const char * parameters) {
	/*std::string notificationMessage = "Notification: ";
	notificationMessage += desc;

	MessageBox(NULL, notificationMessage.c_str(), title, MB_OK | MB_ICONQUESTION);*/
}

void AppFrame::Device::OnEventCallback(const char * functionAddress) {
}

#else
const char * Engine::Device::GetDeviceModel() {
	return nullptr;
}
const char * Engine::Device::GetDeviceOS() {
	return nullptr;
}
const char * Engine::Device::GetCPUModel() {
	return nullptr;
}
const char * Engine::Device::GetGPUModel() {
	return nullptr;
}
const char * Engine::Device::GetRegion() {
	return nullptr;
}
unsigned int Engine::Device::GetHardwareConcurrency() {
	return std::thread::hardware_concurrency();
}
const char * Engine::Device::GetCurrency() {
	return nullptr;
}
const char * Engine::Device::GetDeviceLanguage() {
	return nullptr;
}
int Engine::Device::GetRAMMemory() {
	return 0;
}
int Engine::Device::GetHardMemory() {
	return 0;
}
int Engine::Device::GetScreenWidth() {
	return 0;
}
int Engine::Device::GetScreenHeight() {
	return 0;
}
int Engine::Device::GetInputType() {
	return 0;
}

void Engine::Device::ShowPopup(const char * title, const char * desc, const char * button1, const char * button2) {
}

void Engine::Device::AddNotification(const char * title, const char * desc, const char * image, const char * parameters) {
}

void Engine::Device::OnEventCallback(const char * functionAddress) {
}
#endif