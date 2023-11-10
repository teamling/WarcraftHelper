#pragma once

#include "unlockfps.h"


class Helper {
public:
	Helper();
	~Helper();

	void Start();
	void Stop();
private:
	void LoadPlugins();
	DWORD m_GamedllBase;
	Version m_War3Version;
	bool m_IsWar3;

	UnlockFPS m_UnlockFPS;
};

bool IsWar3();