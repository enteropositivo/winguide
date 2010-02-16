#pragma once
#include "afxwin.h"

class CKeyComboEdit :
	public CEdit
{

	bool _ctrlPressed;
	bool _shiftPressed;
	bool _altPressed;
	UINT _virtualKeyCode;
public:
	CKeyComboEdit(void);
	~CKeyComboEdit(void);
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	bool WasCtrlPressed() { return _ctrlPressed; }
	bool WasShiftPressed() { return _shiftPressed; }
	bool WasAltPressed() { return _altPressed; }
	UINT GetVirtualKeyCode() { return _virtualKeyCode; }

	BOOL PreTranslateMessage(MSG *pMsg);

	DECLARE_MESSAGE_MAP()
};




