#pragma once

#include <afxwin.h>
#include <afxtempl.h>
#include <map>
#include <exception>

class KeyConverter
{
	static CMap<UINT, UINT, CString, CString&> _keyName;

public:
	static CString ToString(UINT virtualKeyCode)
	{
		if(_keyName.GetCount() == NULL)
			initializeMap();

		CString name;

		if(!_keyName.Lookup(virtualKeyCode, name))
			name.AppendFormat(_T("%c"), virtualKeyCode);

		return name;
	}

	static CString ToString(UINT virtualKeyCode, bool ctrlPressed, bool shiftPressed, bool altPressed)
	{
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

	static BOOL IsVirtualKey(WORD virtualKeyCode)
	{
		CString name;
		return _keyName.Lookup(virtualKeyCode, name);
	}

private:
	KeyConverter(void) {}
	~KeyConverter(void) {}

	static void initializeMap()
	{
		_keyName[0x01] = _T("LButton");
		_keyName[0x02] = _T("RButton");
		_keyName[0x03] = _T("Cancel");
		_keyName[0x04] = _T("MButton");
		_keyName[0x05] = _T("XButton1");
		_keyName[0x06] = _T("XButton2");
		_keyName[0x08] = _T("BackSpace");
		_keyName[0x09] = _T("Tab");
		_keyName[0x0c] = _T("Clear");
		_keyName[0x0d] = _T("Enter");
		_keyName[0x10] = _T("Shift");
		_keyName[0x11] = _T("Ctrl");
		_keyName[0x12] = _T("Alt");
		_keyName[0x13] = _T("Pause");
		_keyName[0x14] = _T("CapsLock");
		_keyName[0x15] = _T("Kana");
		_keyName[0x15] = _T("Hangeul");
		_keyName[0x15] = _T("Hangul");
		_keyName[0x17] = _T("Junja");
		_keyName[0x18] = _T("Final");
		_keyName[0x19] = _T("Hanja");
		_keyName[0x19] = _T("Kanji");
		_keyName[0x1b] = _T("Escape");
		_keyName[0x1c] = _T("Convert");
		_keyName[0x1d] = _T("Nonconvert");
		_keyName[0x1e] = _T("Accept");
		_keyName[0x1f] = _T("Modechange");
		_keyName[0x20] = _T("Space");
		_keyName[0x21] = _T("Prior");
		_keyName[0x22] = _T("Next");
		_keyName[0x23] = _T("End");
		_keyName[0x24] = _T("Home");
		_keyName[0x25] = _T("Left");
		_keyName[0x26] = _T("Up");
		_keyName[0x27] = _T("Right");
		_keyName[0x28] = _T("Down");
		_keyName[0x29] = _T("Select");
		_keyName[0x2a] = _T("Print");
		_keyName[0x2b] = _T("Execute");
		_keyName[0x2c] = _T("Snapshot");
		_keyName[0x2d] = _T("Insert");
		_keyName[0x2e] = _T("Delete");
		_keyName[0x2f] = _T("Help");
		_keyName[0x5b] = _T("LWin");
		_keyName[0x5c] = _T("RWin");
		_keyName[0x5d] = _T("Apps");
		_keyName[0x5f] = _T("Sleep");
		_keyName[0x60] = _T("Numpad0");
		_keyName[0x61] = _T("Numpad1");
		_keyName[0x62] = _T("Numpad2");
		_keyName[0x63] = _T("Numpad3");
		_keyName[0x64] = _T("Numpad4");
		_keyName[0x65] = _T("Numpad5");
		_keyName[0x66] = _T("Numpad6");
		_keyName[0x67] = _T("Numpad7");
		_keyName[0x68] = _T("Numpad8");
		_keyName[0x69] = _T("Numpad9");
		_keyName[0x6a] = _T("Numpad *");
		_keyName[0x6b] = _T("Numpad +");
		_keyName[0x6c] = _T("Separator");
		_keyName[0x6d] = _T("Numpad -");
		_keyName[0x6e] = _T("Decimal");
		_keyName[0x6f] = _T("Numpad /");
		_keyName[0x70] = _T("F1");
		_keyName[0x71] = _T("F2");
		_keyName[0x72] = _T("F3");
		_keyName[0x73] = _T("F4");
		_keyName[0x74] = _T("F5");
		_keyName[0x75] = _T("F6");
		_keyName[0x76] = _T("F7");
		_keyName[0x77] = _T("F8");
		_keyName[0x78] = _T("F9");
		_keyName[0x79] = _T("F10");
		_keyName[0x7a] = _T("F11");
		_keyName[0x7b] = _T("F12");
		_keyName[0x7c] = _T("F13");
		_keyName[0x7d] = _T("F14");
		_keyName[0x7e] = _T("F15");
		_keyName[0x7f] = _T("F16");
		_keyName[0x80] = _T("F17");
		_keyName[0x81] = _T("F18");
		_keyName[0x82] = _T("F19");
		_keyName[0x83] = _T("F20");
		_keyName[0x84] = _T("F21");
		_keyName[0x85] = _T("F22");
		_keyName[0x86] = _T("F23");
		_keyName[0x87] = _T("F24");
		_keyName[0x90] = _T("Numlock");
		_keyName[0x91] = _T("ScrollLock");
		_keyName[0x92] = _T("OemNecEqual");
		_keyName[0x92] = _T("OemFjJisho");
		_keyName[0x93] = _T("OemFjMasshou");
		_keyName[0x94] = _T("OemFjTouroku");
		_keyName[0x95] = _T("OemFjLoya");
		_keyName[0x96] = _T("OemFjRoya");
		_keyName[0xa0] = _T("LShift");
		_keyName[0xa1] = _T("RShift");
		_keyName[0xa2] = _T("LControl");
		_keyName[0xa3] = _T("RControl");
		_keyName[0xa4] = _T("LMenu");
		_keyName[0xa5] = _T("RMenu");
		_keyName[0xa6] = _T("BrowserBack");
		_keyName[0xa7] = _T("BrowserForward");
		_keyName[0xa8] = _T("BrowserRefresh");
		_keyName[0xa9] = _T("BrowserStop");
		_keyName[0xaa] = _T("BrowserSearch");
		_keyName[0xab] = _T("BrowserFavorites");
		_keyName[0xac] = _T("BrowserHome");
		_keyName[0xad] = _T("VolumeMute");
		_keyName[0xae] = _T("VolumeDown");
		_keyName[0xaf] = _T("VolumeUp");
		_keyName[0xb0] = _T("MediaNextTrack");
		_keyName[0xb1] = _T("MediaPrevTrack");
		_keyName[0xb2] = _T("MediaStop");
		_keyName[0xb3] = _T("MediaPlayPause");
		_keyName[0xb4] = _T("LaunchMail");
		_keyName[0xb5] = _T("LaunchMediaSelect");
		_keyName[0xb6] = _T("LaunchApp1");
		_keyName[0xb7] = _T("LaunchApp2");
		_keyName[0xba] = _T("Oem1");
		_keyName[0xbb] = _T("Plus");
		_keyName[0xbc] = _T(",");
		_keyName[0xbd] = _T("-");
		_keyName[0xbe] = _T(".");
		_keyName[0xbf] = _T("Oem2");
		_keyName[0xc0] = _T("`");
		_keyName[0xdb] = _T("Oem4");
		_keyName[0xdc] = _T("Oem5");
		_keyName[0xdd] = _T("Oem6");
		_keyName[0xde] = _T("Oem7");
		_keyName[0xdf] = _T("Oem8");
		_keyName[0xe1] = _T("OemAx");
		_keyName[0xe2] = _T("Oem102");
		_keyName[0xe3] = _T("IcoHelp");
		_keyName[0xe4] = _T("Ico00");
		_keyName[0xe5] = _T("Processkey");
		_keyName[0xe6] = _T("IcoClear");
		_keyName[0xe7] = _T("Packet");
		_keyName[0xe9] = _T("OemReset");
		_keyName[0xea] = _T("OemJump");
		_keyName[0xeb] = _T("OemPa1");
		_keyName[0xec] = _T("OemPa2");
		_keyName[0xed] = _T("OemPa3");
		_keyName[0xee] = _T("OemWsctrl");
		_keyName[0xef] = _T("OemCusel");
		_keyName[0xf0] = _T("OemAttn");
		_keyName[0xf1] = _T("OemFinish");
		_keyName[0xf2] = _T("OemCopy");
		_keyName[0xf3] = _T("OemAuto");
		_keyName[0xf4] = _T("OemEnlw");
		_keyName[0xf5] = _T("OemBacktab");
		_keyName[0xf6] = _T("Attn");
		_keyName[0xf7] = _T("Crsel");
		_keyName[0xf8] = _T("Exsel");
		_keyName[0xf9] = _T("Ereof");
		_keyName[0xfa] = _T("Play");
		_keyName[0xfb] = _T("Zoom");
		_keyName[0xfc] = _T("Noname");
		_keyName[0xfd] = _T("Pa1");
		_keyName[0xfe] = _T("OemClear");

	}
};
