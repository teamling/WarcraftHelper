#include "helper.h"
#include <atlstr.h>

#pragma comment(lib, "Version.lib")

Version GetWar3Version() {
	char Data[2048];
	memset(Data, 0, 2048);
	if (!GetFileVersionInfo("Game.dll", 0, sizeof(Data), Data))
	{
		return Version::unknown;
	}
	VS_FIXEDFILEINFO *FileInfo;
	UINT nBytes = 0;
	VerQueryValue(Data, "\\", (void**)&FileInfo, &nBytes);
	DWORD buildVersion = FileInfo->dwFileVersionLS & 0xffff;
	return static_cast<Version>(buildVersion);
}

Helper::Helper() {
	this->m_IsWar3 = IsWar3();
	if (!this->m_IsWar3) {
		return;
	}
	DWORD gamedll = (DWORD)GetModuleHandle("Game.dll");
	Version gamedversion = GetWar3Version();
	// 获取GameDll
	this->m_GamedllBase = gamedll;
	// 获取游戏版本
	this->m_War3Version = gamedversion;

	this->m_UnlockFPS = UnlockFPS(gamedll, gamedversion);
}

Helper::~Helper() {
}

void Helper::Start() {
	if (!this->m_IsWar3) {
		return;
	}
	
	/*DWORD esiBak = 0;
	DWORD ediBak = 0;
	DWORD ebxBak = 0;
	_asm {
		mov esiBak, esi
		mov ediBak, edi
		mov ebxBak, ebx
	}*/
	this->m_UnlockFPS.Start();
	/*_asm {
		mov esi, esiBak
		mov edi, ediBak
		mov ebx, ebxBak
	}*/

	this->LoadPlugins();
}

void Helper::Stop() {
	if (!this->m_IsWar3) {
		return;
	}

	this->m_UnlockFPS.Stop();
	Sleep(60);
}

bool IsWar3() {
	TCHAR lpFilePATH[MAX_PATH];
	memset(lpFilePATH, 0, MAX_PATH * sizeof(TCHAR));
	::GetModuleFileName(NULL, lpFilePATH, MAX_PATH);
	CString tmp;
	tmp.Format("%s", lpFilePATH);
	DWORD loc = tmp.ReverseFind('\\');
	for (int i = loc + 1; i< MAX_PATH; i++) {
		if (lpFilePATH[i] >= 'A' && lpFilePATH[i] <= 'Z'){
			lpFilePATH[i] += 'a'-'A';
		}
	}
	if (strncmp(lpFilePATH + loc + 1, "war3.exe",8)) {
		return false;
	}
	return true;
}


void Helper::LoadPlugins() {
	if (!this->m_GamedllBase) {
		return;
	}


}