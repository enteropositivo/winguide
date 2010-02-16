#include "StdAfx.h"
#include "CommandManager.h"
#include ".\guide.h"

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
	_changeMap[ctxCookie] = true;
	ACCEL accel;
	accel.fVirt = getFVirt(key, ctrl, shift, alt);
	accel.key = key;
	accel.cmd = cmdId;
	_accelMap[ctxCookie][cmdName] = accel;
}

DWORD CommandManager::GetContextCookie(CString context)
{
	return _cookieMap[context];
}

HACCEL CommandManager::GetDynamicAcceleratorTable(DWORD contextCookie)
{
	if(_changeMap[contextCookie])
	{
		std::vector<ACCEL> accelArray;
		
		AccelMap & accelMap = _accelMap[contextCookie];

		for(AccelMap::iterator i = accelMap.begin();
			i != accelMap.end();
			++i)
		{
			accelArray.push_back(i->second);
		}
		
		if(accelArray.size() > 0)
			_hAccel = CreateAcceleratorTable(&accelArray[0]
												, (int)accelArray.size());
		
		_changeMap[contextCookie] = false;
	}

	return _hAccel;
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

//void CommandManager::Serialize( CArchive& archive )
//{
//	// call base class function first
//	// base class is CObject in this case
//	CObject::Serialize( archive );

//	// now do the stuff for our specific class
//	if(archive.IsStoring())
//	{
//		//Save the number of elements
//		archive << (int)_accelMap.size();

//		for(AccelMap::iterator i = _accelMap.begin();
//			i != _accelMap.end();
//			++i)
//		{
//			archive << i->first;
//			archive << i->second.cmd;
//			archive << i->second.fVirt;
//			archive << i->second.key;
//		}
//	}
//	else
//	{
//		int size;
//		archive >> size;
//		CString name;
//		ACCEL accel;
//		for(int i=0; i<size; i++)
//		{
//			archive >> name;
//			archive >> accel.cmd;
//			archive >> accel.fVirt;
//			archive >> accel.key;
//		}

//		_accelMap[name] = accel;
//	}
//}


BYTE CommandManager::getFVirt(WORD key, bool ctrl, bool shift, bool alt)
{
	BYTE fVirt=0;
	fVirt |= KeyConverter::IsVirtualKey(key)?FVIRTKEY:0;
	fVirt |= ctrl?FCONTROL:0;
	fVirt |= shift?FSHIFT:0;
	fVirt |= alt?FALT:0;

	return fVirt;
}

