#pragma once
#include <afxwin.h>
#include <afxtempl.h>
#include <windows.h>
#include <vector>
#include <map>
#include <set>
#include "KeyConverter.h"

class CGuideApp;

class CommandManager
{
public:
	typedef std::map<CString, ACCEL> AccelMap;//CommandName->ACCEL
	typedef std::vector<AccelMap> ContextMap;//ContextCookie->ACCELMAP
	typedef std::vector<bool> ChangeMap;//ContextCookie->changed?
	typedef std::vector<HACCEL> HAccelMap;//ContextCookie->changed?
	typedef std::map<CString,DWORD> ContextNameToCookieMap;//ContextName->Cookie

private:
	ContextMap				_accelMap;
	ChangeMap				_changeMap;
	ContextNameToCookieMap	_cookieMap; 
	HAccelMap		_hAccelMap;
	CGuideApp	*_app;

	CString			_currentScheme;
	CStringArray	_availableSchemes;
	AccelMap::iterator _cmdNameIter;
	AccelMap::iterator _cmdNameIterEnd;
public:

	CommandManager(void);
	~CommandManager(void);

	void SetCurrentScheme(const CString& scheme);

	void SetAccelerator(DWORD ctxCookie
							, TCHAR *cmdName
							, WORD cmdId
							, WORD key
							, bool ctrl
							, bool shift
							, bool alt);

	DWORD GetContextCookie(CString context);

	void GetContextNames(CStringArray & names);
	
	HACCEL GetDynamicAcceleratorTable(DWORD contextCookie);

	bool GetFirstCommandName(DWORD contextCookie, CString &cmdName);

	bool GetNextCommandName(CString &cmdName);

	CString GetCommandKeyCombo(DWORD contextCookie, CString cmdName);

	DWORD AddContext(CString ctx);

private:
	BYTE getFVirt(WORD key, bool ctrl, bool shift, bool alt);
	static CString GetCommandKeyCombo(ACCEL accel);
};
