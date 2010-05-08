#pragma once

#include <set>
#include <windows.h>
#include <stdlib.h>
#include <stdarg.h>

class Logger
{
	static std::set<DWORD> _filter;
	static bool _inclusiveFiltering;
	static CRITICAL_SECTION csec;
	static bool _initialized;
	static int _indentLevel;

	//Methods
	static int log(const TCHAR * format, va_list args);
	static void printTabs();
	static void print(const TCHAR* str);
public:
	
	static void SetFilterMode(bool inclusiveFiltering);
	static void AddFilter(DWORD msg);
	static void RemoveFilter(DWORD msg);
	static void ResetFilter();
	static void Log( const MSG& msg );
	static void Log(const TCHAR* fmt, ...);
	static void Enter(const TCHAR* fmt, ...);
	static void Exit(const TCHAR* fmt, ...);
};
