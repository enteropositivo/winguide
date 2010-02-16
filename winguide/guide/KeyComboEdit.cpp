/* Copyright 2010 Sandeep Datta
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include "StdAfx.h"
#include "KeyComboEdit.h"
#include "KeyConverter.h"

BEGIN_MESSAGE_MAP(CKeyComboEdit, CEdit)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

CKeyComboEdit::CKeyComboEdit(void)
		: _ctrlPressed(false)
		, _shiftPressed(false)
		, _altPressed(false)
		, _virtualKeyCode(0xFF)
	{
	}

CKeyComboEdit::~CKeyComboEdit(void)
{
}

void CKeyComboEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

BOOL CKeyComboEdit::PreTranslateMessage(MSG *pMsg)
{

	//TCHAR str[2048];
	//_stprintf(str, _T("Msg: 0x%x wparam: 0x%x\n"), pMsg->message, pMsg->wParam);
	//OutputDebugString(str);


	if(pMsg->message == WM_KEYDOWN || pMsg->message == WM_SYSKEYDOWN)
	{
		SHORT state = GetKeyState(VK_SHIFT);
		_shiftPressed = (state & 1<<16) == 1<<16;
			
		state = GetKeyState(VK_CONTROL);
		_ctrlPressed = (state & 1<<16) == 1<<16;
		
		state = GetKeyState(VK_MENU);
		_altPressed = (state & 1<<16) == 1<<16;

		if(pMsg->wParam != VK_CONTROL 
			&& pMsg->wParam != VK_MENU 
			&& pMsg->wParam != VK_SHIFT)
		{

			_virtualKeyCode = (UINT)pMsg->wParam;
			SetWindowText(KeyConverter::ToString(_virtualKeyCode, _ctrlPressed, _shiftPressed, _altPressed));
		}
		else
		{
			_virtualKeyCode = 0xFF;//Reserved value used as sentinel
		}

		//Do not let these key strokes pass through
		if (pMsg->wParam == VK_F10 
			|| pMsg->wParam == VK_RETURN 
			|| pMsg->wParam == VK_TAB 
			|| pMsg->wParam == VK_ESCAPE)
			return TRUE;	
	}

	return CEdit::PreTranslateMessage(pMsg);;
}