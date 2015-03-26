#include "StdAfx.h"
#include "CommandManager.h"
#include ".\guide.h"

//Static member variable
CommandManager *CommandManager::_instance = NULL;

CommandManager::CommandManager(void)
{
	_app = (CGuideApp*)AfxGetApp();
	_app->GetSchemeNames(_availableSchemes);
}

CommandManager::~CommandManager(void) 
{
}

void CommandManager::SetCurrentScheme(const CString& scheme)
{
	_currentScheme = scheme;
}

DWORD CommandManager::AddContext(CString ctx)
{
	//if the context does not exist then create appropriate entries for it
	if(_cookieMap.find(ctx) == _cookieMap.end())
	{
		_accelMap.push_back(AccelMap());
		_changeMap.push_back(TRUE);
		_hAccelMap.push_back(NULL);
		_cookieMap[ctx] = (DWORD)_accelMap.size()-1;//Save the index of the entry just inserted as the cookie
	}

	return _cookieMap[ctx];
}

void CommandManager::GetContextNames(CStringArray & names)
{
	for(ContextNameToCookieMap::iterator i = _cookieMap.begin();
		i != _cookieMap.end();
		++i)
	{
		names.Add(i->first);
	}
}

void CommandManager::SetAccelerator(DWORD ctxCookie
						, TCHAR *cmdName
						, WORD cmdId
						, WORD key
						, bool ctrl
						, bool shift
						, bool alt)
{
	TRACE(_T("Enter CommandManager::SetAccelerator()\n"));
	_changeMap[ctxCookie] = true;
	ACCEL accel;
	accel.fVirt = getFVirt(key, ctrl, shift, alt);
	accel.key = key;
	accel.cmd = cmdId;
	_accelMap[ctxCookie][cmdName] = accel;
	TRACE(_T("ACCEL(fVirt=0x%x, key=0x%x, cmd=0x%x)\n"), accel.fVirt, accel.key, accel.cmd);
	TRACE(_T("Exit CommandManager::SetAccelerator()\n"));
}

void CommandManager::ResetAccelerator(DWORD ctxCookie
						, CString cmdName
						, WORD key
						, bool ctrl
						, bool shift
						, bool alt)
{
	TRACE(_T("Enter CommandManager::ResetAccelerator()\n"));
	AccelMap::iterator cmdIter = _accelMap[ctxCookie].find(cmdName);
	if(cmdIter == _accelMap[ctxCookie].end())
		throw std::exception("Trying to reset unregistered command. Use SetAccelerator() first.\n");

	_changeMap[ctxCookie] = true;
	ACCEL accel;
	accel.fVirt = getFVirt(key, ctrl, shift, alt);
	accel.key = key;
	accel.cmd = cmdIter->second.cmd;
	_accelMap[ctxCookie][cmdName] = accel;
	TRACE(_T("ACCEL(fVirt=0x%x, key=0x%x, cmd=0x%x)\n"), accel.fVirt, accel.key, accel.cmd);
	TRACE(_T("Exit CommandManager::ResetAccelerator()\n"));
}

DWORD CommandManager::GetContextCookie(CString context)
{
	return _cookieMap[context];
}

HACCEL CommandManager::GetDynamicAcceleratorTable(DWORD contextCookie)
{

	if(contextCookie >= _hAccelMap.size())
	{
		TRACE(_T("CommandManager::GetDynamicAcceleratorTable(): Invalid context cookie\n"));
		return NULL;
	}

	if(_changeMap[contextCookie])
	{
		TRACE(_T("CommandManager::GetDynamicAcceleratorTable(): Creating new context map\n"));
		std::vector<ACCEL> accelArray;
		
		AccelMap & accelMap = _accelMap[contextCookie];

		for(AccelMap::iterator i = accelMap.begin();
			i != accelMap.end();
			++i)
		{
			accelArray.push_back(i->second);
		}
		TRACE(_T("CommandManager::GetDynamicAcceleratorTable(): Found %d accelerators \n"), accelArray.size());
		
		if(accelArray.size() > 0)
		{
			DestroyAcceleratorTable(_hAccelMap[contextCookie]);
			_hAccelMap[contextCookie] = CreateAcceleratorTable(&accelArray[0], (int)accelArray.size());
		}
		
		_changeMap[contextCookie] = false;
	}

	return _hAccelMap[contextCookie];
}

bool CommandManager::GetFirstCommandName(DWORD contextCookie, CString &cmdName)
{
	_cmdNameIter = _accelMap[contextCookie].begin();
	_cmdNameIterEnd = _accelMap[contextCookie].end();
	if(_cmdNameIter == _cmdNameIterEnd)
		return false;
	
	cmdName = _cmdNameIter->first;

	return true;
}

bool CommandManager::GetNextCommandName(CString &cmdName)
{
	if(_cmdNameIter++ == _cmdNameIterEnd)
		return false;

	if(_cmdNameIter == _cmdNameIterEnd)
		return false;
	
	cmdName = _cmdNameIter->first;

	return true;
}

CString CommandManager::GetCommandKeyCombo(ACCEL accel)
{
	return KeyConverter::ToString(accel.key
									, (accel.fVirt & FCONTROL) == FCONTROL
									, (accel.fVirt & FSHIFT) == FSHIFT
									, (accel.fVirt & FALT) == FALT
								);
}

CString CommandManager::GetCommandKeyCombo(DWORD contextCookie, CString cmdName)
{
	return GetCommandKeyCombo(_accelMap[contextCookie][cmdName]);
}

BYTE CommandManager::getFVirt(WORD key, bool ctrl, bool shift, bool alt)
{
	BYTE fVirt=0;
	fVirt |= KeyConverter::IsVirtualKey(key)?FVIRTKEY:0;
	fVirt |= ctrl?FCONTROL:0;
	fVirt |= shift?FSHIFT:0;
	fVirt |= alt?FALT:0;

	return fVirt;
}

CommandManager * CommandManager::GetInstance()
{
	if(_instance == NULL)
		_instance = new CommandManager();

	return _instance;
}

