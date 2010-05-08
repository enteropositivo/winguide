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
#include "KeyConverter.h"

CMap<UINT, UINT, CString, CString&> KeyConverter::_keyName;

KeyConverter::KeyConverter( void )
{

}

KeyConverter::~KeyConverter( void )
{

}

CString KeyConverter::ToString( UINT virtualKeyCode )
{
	if(_keyName.GetCount() == NULL)
		initializeMap();

	CString name;

	if(!_keyName.Lookup(virtualKeyCode, name))
		name.AppendFormat(_T("%c"), virtualKeyCode);

	return name;
}

CString KeyConverter::ToString( UINT virtualKeyCode, bool ctrlPressed, bool shiftPressed, bool altPressed )
{
	if(_keyName.GetCount() == NULL)
		initializeMap();

	CString keyCombo;

	if(virtualKeyCode == VK_CONTROL || virtualKeyCode == VK_MENU || virtualKeyCode == VK_SHIFT)
	{
		keyCombo.AppendFormat(KeyConverter::ToString(virtualKeyCode));
		return keyCombo;
	}

	if (ctrlPressed)
		keyCombo.AppendFormat(_T("Ctrl+"));
	if (shiftPressed)
		keyCombo.AppendFormat(_T("Shift+"));
	if (altPressed)
		keyCombo.AppendFormat(_T("Alt+"));

	keyCombo.AppendFormat(KeyConverter::ToString(virtualKeyCode));
	return keyCombo;
}

BOOL KeyConverter::IsVirtualKey( WORD virtualKeyCode )
{
	if(_keyName.GetCount() == NULL)
		initializeMap();

	CString name;
	return _keyName.Lookup(virtualKeyCode, name);
}

void KeyConverter::initializeMap()
{
	_keyName[VK_LBUTTON] = _T("Lbutton"); //0x01
	_keyName[VK_RBUTTON] = _T("Rbutton"); //0x02
	_keyName[VK_CANCEL] = _T("Cancel"); //0x03
	_keyName[VK_MBUTTON] = _T("Mbutton"); //0x04
	_keyName[VK_XBUTTON1] = _T("Xbutton1"); //0x05
	_keyName[VK_XBUTTON2] = _T("Xbutton2"); //0x06
	_keyName[VK_BACK] = _T("BackSpace"); //0x08
	_keyName[VK_TAB] = _T("Tab"); //0x09
	_keyName[VK_CLEAR] = _T("Clear"); //0x0C
	_keyName[VK_RETURN] = _T("Enter"); //0x0D
	_keyName[VK_SHIFT] = _T("Shift"); //0x10
	_keyName[VK_CONTROL] = _T("Ctrl"); //0x11
	_keyName[VK_MENU] = _T("Alt"); //0x12
	_keyName[VK_PAUSE] = _T("Pause"); //0x13
	_keyName[VK_CAPITAL] = _T("CapsLock"); //0x14
	_keyName[VK_KANA] = _T("Kana"); //0x15
	//_keyName[VK_HANGEUL] = _T("Hangeul"); //0x15
	//_keyName[VK_HANGUL] = _T("Hangul"); //0x15
	_keyName[VK_JUNJA] = _T("Junja"); //0x17
	_keyName[VK_FINAL] = _T("Final"); //0x18
	_keyName[VK_HANJA] = _T("Hanja"); //0x19
	//_keyName[VK_KANJI] = _T("Kanji"); //0x19
	_keyName[VK_ESCAPE] = _T("Esc"); //0x1B
	_keyName[VK_CONVERT] = _T("Convert"); //0x1C
	_keyName[VK_NONCONVERT] = _T("Nonconvert"); //0x1D
	_keyName[VK_ACCEPT] = _T("Accept"); //0x1E
	_keyName[VK_MODECHANGE] = _T("Modechange"); //0x1F
	_keyName[VK_SPACE] = _T("Space"); //0x20
	_keyName[VK_PRIOR] = _T("Prior"); //0x21
	_keyName[VK_NEXT] = _T("Next"); //0x22
	_keyName[VK_END] = _T("End"); //0x23
	_keyName[VK_HOME] = _T("Home"); //0x24
	_keyName[VK_LEFT] = _T("Left"); //0x25
	_keyName[VK_UP] = _T("Up"); //0x26
	_keyName[VK_RIGHT] = _T("Right"); //0x27
	_keyName[VK_DOWN] = _T("Down"); //0x28
	_keyName[VK_SELECT] = _T("Select"); //0x29
	_keyName[VK_PRINT] = _T("Print"); //0x2A
	_keyName[VK_EXECUTE] = _T("Execute"); //0x2B
	_keyName[VK_SNAPSHOT] = _T("Snapshot"); //0x2C
	_keyName[VK_INSERT] = _T("Insert"); //0x2D
	_keyName[VK_DELETE] = _T("Delete"); //0x2E
	_keyName[VK_HELP] = _T("Help"); //0x2F
	_keyName[VK_LWIN] = _T("Lwin"); //0x5B
	_keyName[VK_RWIN] = _T("Rwin"); //0x5C
	_keyName[VK_APPS] = _T("Apps"); //0x5D
	_keyName[VK_SLEEP] = _T("Sleep"); //0x5F
	_keyName[VK_NUMPAD0] = _T("Numpad0"); //0x60
	_keyName[VK_NUMPAD1] = _T("Numpad1"); //0x61
	_keyName[VK_NUMPAD2] = _T("Numpad2"); //0x62
	_keyName[VK_NUMPAD3] = _T("Numpad3"); //0x63
	_keyName[VK_NUMPAD4] = _T("Numpad4"); //0x64
	_keyName[VK_NUMPAD5] = _T("Numpad5"); //0x65
	_keyName[VK_NUMPAD6] = _T("Numpad6"); //0x66
	_keyName[VK_NUMPAD7] = _T("Numpad7"); //0x67
	_keyName[VK_NUMPAD8] = _T("Numpad8"); //0x68
	_keyName[VK_NUMPAD9] = _T("Numpad9"); //0x69
	_keyName[VK_MULTIPLY] = _T("Multiply"); //0x6A
	_keyName[VK_ADD] = _T("Numpad +"); //0x6B
	_keyName[VK_SEPARATOR] = _T("Separator"); //0x6C
	_keyName[VK_SUBTRACT] = _T("Numpad -"); //0x6D
	_keyName[VK_DECIMAL] = _T("Decimal"); //0x6E
	_keyName[VK_DIVIDE] = _T("Numpad /"); //0x6F
	_keyName[VK_F1] = _T("F1"); //0x70
	_keyName[VK_F2] = _T("F2"); //0x71
	_keyName[VK_F3] = _T("F3"); //0x72
	_keyName[VK_F4] = _T("F4"); //0x73
	_keyName[VK_F5] = _T("F5"); //0x74
	_keyName[VK_F6] = _T("F6"); //0x75
	_keyName[VK_F7] = _T("F7"); //0x76
	_keyName[VK_F8] = _T("F8"); //0x77
	_keyName[VK_F9] = _T("F9"); //0x78
	_keyName[VK_F10] = _T("F10"); //0x79
	_keyName[VK_F11] = _T("F11"); //0x7A
	_keyName[VK_F12] = _T("F12"); //0x7B
	_keyName[VK_F13] = _T("F13"); //0x7C
	_keyName[VK_F14] = _T("F14"); //0x7D
	_keyName[VK_F15] = _T("F15"); //0x7E
	_keyName[VK_F16] = _T("F16"); //0x7F
	_keyName[VK_F17] = _T("F17"); //0x80
	_keyName[VK_F18] = _T("F18"); //0x81
	_keyName[VK_F19] = _T("F19"); //0x82
	_keyName[VK_F20] = _T("F20"); //0x83
	_keyName[VK_F21] = _T("F21"); //0x84
	_keyName[VK_F22] = _T("F22"); //0x85
	_keyName[VK_F23] = _T("F23"); //0x86
	_keyName[VK_F24] = _T("F24"); //0x87
	_keyName[VK_NUMLOCK] = _T("NumLock"); //0x90
	_keyName[VK_SCROLL] = _T("ScrollLock"); //0x91
	_keyName[VK_OEM_NEC_EQUAL] = _T("OemNecEqual"); //0x92
	//_keyName[VK_OEM_FJ_JISHO] = _T("OemFjJisho"); //0x92
	_keyName[VK_OEM_FJ_MASSHOU] = _T("OemFjMasshou"); //0x93
	_keyName[VK_OEM_FJ_TOUROKU] = _T("OemFjTouroku"); //0x94
	_keyName[VK_OEM_FJ_LOYA] = _T("OemFjLoya"); //0x95
	_keyName[VK_OEM_FJ_ROYA] = _T("OemFjRoya"); //0x96
	_keyName[VK_LSHIFT] = _T("LShift"); //0xA0
	_keyName[VK_RSHIFT] = _T("RShift"); //0xA1
	_keyName[VK_LCONTROL] = _T("LCtrl"); //0xA2
	_keyName[VK_RCONTROL] = _T("RCtrl"); //0xA3
	_keyName[VK_LMENU] = _T("Lalt"); //0xA4
	_keyName[VK_RMENU] = _T("Ralt"); //0xA5
	_keyName[VK_BROWSER_BACK] = _T("BrowserBack"); //0xA6
	_keyName[VK_BROWSER_FORWARD] = _T("BrowserForward"); //0xA7
	_keyName[VK_BROWSER_REFRESH] = _T("BrowserRefresh"); //0xA8
	_keyName[VK_BROWSER_STOP] = _T("BrowserStop"); //0xA9
	_keyName[VK_BROWSER_SEARCH] = _T("BrowserSearch"); //0xAA
	_keyName[VK_BROWSER_FAVORITES] = _T("BrowserFavorites"); //0xAB
	_keyName[VK_BROWSER_HOME] = _T("BrowserHome"); //0xAC
	_keyName[VK_VOLUME_MUTE] = _T("VolumeMute"); //0xAD
	_keyName[VK_VOLUME_DOWN] = _T("VolumeDown"); //0xAE
	_keyName[VK_VOLUME_UP] = _T("VolumeUp"); //0xAF
	_keyName[VK_MEDIA_NEXT_TRACK] = _T("MediaNextTrack"); //0xB0
	_keyName[VK_MEDIA_PREV_TRACK] = _T("MediaPrevTrack"); //0xB1
	_keyName[VK_MEDIA_STOP] = _T("MediaStop"); //0xB2
	_keyName[VK_MEDIA_PLAY_PAUSE] = _T("MediaPlayPause"); //0xB3
	_keyName[VK_LAUNCH_MAIL] = _T("LaunchMail"); //0xB4
	_keyName[VK_LAUNCH_MEDIA_SELECT] = _T("LaunchMediaSelect"); //0xB5
	_keyName[VK_LAUNCH_APP1] = _T("LaunchApp1"); //0xB6
	_keyName[VK_LAUNCH_APP2] = _T("LaunchApp2"); //0xB7
	_keyName[VK_OEM_1] = _T("Oem1"); //0xBA
	_keyName[VK_OEM_PLUS] = _T("Plus"); //0xBB
	_keyName[VK_OEM_COMMA] = _T(","); //0xBC
	_keyName[VK_OEM_MINUS] = _T("-"); //0xBD
	_keyName[VK_OEM_PERIOD] = _T("."); //0xBE
	_keyName[VK_OEM_2] = _T("Oem2"); //0xBF
	_keyName[VK_OEM_3] = _T("`"); //0xC0
	_keyName[VK_OEM_4] = _T("Oem4"); //0xDB
	_keyName[VK_OEM_5] = _T("Oem5"); //0xDC
	_keyName[VK_OEM_6] = _T("Oem6"); //0xDD
	_keyName[VK_OEM_7] = _T("Oem7"); //0xDE
	_keyName[VK_OEM_8] = _T("Oem8"); //0xDF
	_keyName[VK_OEM_AX] = _T("OemAx"); //0xE1
	_keyName[VK_OEM_102] = _T("Oem102"); //0xE2
	_keyName[VK_ICO_HELP] = _T("IcoHelp"); //0xE3
	_keyName[VK_ICO_00] = _T("Ico00"); //0xE4
	_keyName[VK_PROCESSKEY] = _T("Processkey"); //0xE5
	_keyName[VK_ICO_CLEAR] = _T("IcoClear"); //0xE6
	_keyName[VK_PACKET] = _T("Packet"); //0xE7
	_keyName[VK_OEM_RESET] = _T("OemReset"); //0xE9
	_keyName[VK_OEM_JUMP] = _T("OemJump"); //0xEA
	_keyName[VK_OEM_PA1] = _T("OemPa1"); //0xEB
	_keyName[VK_OEM_PA2] = _T("OemPa2"); //0xEC
	_keyName[VK_OEM_PA3] = _T("OemPa3"); //0xED
	_keyName[VK_OEM_WSCTRL] = _T("OemWsctrl"); //0xEE
	_keyName[VK_OEM_CUSEL] = _T("OemCusel"); //0xEF
	_keyName[VK_OEM_ATTN] = _T("OemAttn"); //0xF0
	_keyName[VK_OEM_FINISH] = _T("OemFinish"); //0xF1
	_keyName[VK_OEM_COPY] = _T("OemCopy"); //0xF2
	_keyName[VK_OEM_AUTO] = _T("OemAuto"); //0xF3
	_keyName[VK_OEM_ENLW] = _T("OemEnlw"); //0xF4
	_keyName[VK_OEM_BACKTAB] = _T("OemBacktab"); //0xF5
	_keyName[VK_ATTN] = _T("Attn"); //0xF6
	_keyName[VK_CRSEL] = _T("Crsel"); //0xF7
	_keyName[VK_EXSEL] = _T("Exsel"); //0xF8
	_keyName[VK_EREOF] = _T("Ereof"); //0xF9
	_keyName[VK_PLAY] = _T("Play"); //0xFA
	_keyName[VK_ZOOM] = _T("Zoom"); //0xFB
	_keyName[VK_NONAME] = _T("Noname"); //0xFC
	_keyName[VK_PA1] = _T("Pa1"); //0xFD
	_keyName[VK_OEM_CLEAR] = _T("OemClear"); //0xFE
}

