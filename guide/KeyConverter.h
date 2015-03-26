#pragma once

#include <afxwin.h>
#include <afxtempl.h>
#include <map>
#include <exception>

class KeyConverter
{
	static CMap<UINT, UINT, CString, CString&> _keyName;

public:
	static CString ToString(UINT virtualKeyCode);
	static CString ToString(UINT virtualKeyCode, bool ctrlPressed, bool shiftPressed, bool altPressed);
	static BOOL IsVirtualKey(WORD virtualKeyCode);

private:
	KeyConverter(void);
	~KeyConverter(void);
	static void initializeMap();
};
