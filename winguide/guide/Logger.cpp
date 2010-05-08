#include "StdAfx.h"
#include "Logger.h"
#include "Interspy/ISMsgManager.h"


void Logger::Log( const MSG& msg )
{
	if(_inclusiveFiltering)
	{
		if(_filter.find(msg.message) == _filter.end())
			return;
	}
	else
	{
		if(_filter.find(msg.message) != _filter.end())
			return;
	}
	

	CString sMsg;
	CStringArray aParams;
	TCHAR cClass[40];
	
	::GetClassName(msg.hwnd, cClass, 40);
	//Do not call the following unless you want to be inundated with WM_GETTEXT messages
	//::GetWindowText(msg.hwnd, cCaption, 128);

	sMsg.Format(_T("Class:\"%s\" "), cClass);

	if (CISMsgManager::HandleMsg(&msg, sMsg, &aParams))
	{
		int nParams = aParams.GetSize();

		if (nParams)
		{
			sMsg += _T('|');

			for (int nParam = 0; nParam < nParams; nParam++)
			{
				sMsg += aParams[nParam];

				if (nParam < nParams - 1)
					sMsg += _T('|'); // delimeter
			}
		}
	}

	sMsg += _T("\n");

	
	return print(sMsg);
}

void Logger::print(const TCHAR* str)
{
	printTabs();
	OutputDebugString(str);
}

int Logger::log(const TCHAR * format, va_list args)
{
	int len;
	TCHAR * buffer;
	// _vscprintf doesn't count terminating '\0'
	len = _vsctprintf( format, args ) + 1; 
	buffer = new TCHAR[len * sizeof(TCHAR)];
	len = _vstprintf( buffer, format, args );
	print( buffer );
	delete buffer;
	return len;
}

void Logger::printTabs()
{
	for(int i = 0; i<_indentLevel; i++)
	{
		OutputDebugString(_T("\t"));
	}
}
void Logger::Log(const TCHAR * format, ...)
{
	va_list args;
	va_start( args, format );
	log(format, args);
}

void Logger::Enter(const TCHAR* format, ...)
{
	va_list args;
	va_start( args, format );
	print(_T(">>"));
	log(format, args);
	_indentLevel++;
}
void Logger::Exit(const TCHAR* format, ...)
{
	va_list args;
	va_start( args, format );
	_indentLevel--;
	print(_T("<<"));
	log(format, args);
}

void Logger::SetFilterMode(bool inclusiveFiltering)
{
	_inclusiveFiltering = inclusiveFiltering;
}


void Logger::AddFilter(DWORD msg)
{
	_filter.insert(msg);
}


void Logger::RemoveFilter(DWORD msg)
{
	_filter.erase(msg);
}


void Logger::ResetFilter()
{
	_filter.clear();
}



std::set<DWORD> Logger::_filter;
//The default setting should log all messages
bool Logger::_inclusiveFiltering = false;
CRITICAL_SECTION Logger::csec;
bool Logger::_initialized = false;
int Logger::_indentLevel=0;