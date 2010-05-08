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

#include "stdafx.h"
#include "Guide.h"
#include "KeyConfig.h"


// KeyConfigDialog dialog

IMPLEMENT_DYNAMIC(KeyConfigDialog, CDialog)

KeyConfigDialog::KeyConfigDialog(CWnd* pParent /*=NULL*/)
	: CDialog(KeyConfigDialog::IDD, pParent)
	, _ctxCookie(-1)
{

}

KeyConfigDialog::~KeyConfigDialog()
{
}

void KeyConfigDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_availableCommands);
	DDX_Control(pDX, IDC_EDIT_CURRENT_KEY, m_txtCurrentKeyAssignment);
	DDX_Control(pDX, IDC_EDIT_DESIRED_KEY, m_txtDesiredKeyCombo);
	DDX_Control(pDX, IDC_BTN_ASSIGN, m_btnAssign);
	DDX_Control(pDX, IDC_COMBO_CONTEXT, m_cmbContext);
}

BOOL KeyConfigDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	_cmdManager = CommandManager::GetInstance();

	CStringArray contextNames;

	_cmdManager->GetContextNames(contextNames);

	for(int i=0; i < contextNames.GetCount(); i++)
	{
		m_cmbContext.AddString(contextNames.ElementAt(i));
	}

	m_cmbContext.SetCurSel(0);
	//Trigger the event manually for the first time
	OnCbnSelchangeComboContext();

	return TRUE;
}


BEGIN_MESSAGE_MAP(KeyConfigDialog, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &KeyConfigDialog::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDOK, &KeyConfigDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_ASSIGN, &KeyConfigDialog::OnBnClickedBtnAssign)
	ON_CBN_SELCHANGE(IDC_COMBO_CONTEXT, &KeyConfigDialog::OnCbnSelchangeComboContext)
END_MESSAGE_MAP()


// KeyConfigDialog message handlers

void KeyConfigDialog::OnLbnSelchangeList1()
{
	int index = m_availableCommands.GetCurSel();
	if(index >=0 )
	{
		CString text;
		m_availableCommands.GetText(index, text);
		m_txtCurrentKeyAssignment.SetWindowText(_cmdManager->GetCommandKeyCombo(_ctxCookie, text));
	}
}


void KeyConfigDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void KeyConfigDialog::OnBnClickedBtnAssign()
{
	int index = m_availableCommands.GetCurSel();
	CString text;
	m_availableCommands.GetText(index, text);
	if(m_txtDesiredKeyCombo.IsValidKeyCombo())
		_cmdManager->ResetAccelerator(_ctxCookie
										, text
										, m_txtDesiredKeyCombo.GetVirtualKeyCode()
										, m_txtDesiredKeyCombo.WasCtrlPressed()
										, m_txtDesiredKeyCombo.WasShiftPressed()
										, m_txtDesiredKeyCombo.WasAltPressed()
									);

	OnLbnSelchangeList1();
}

void KeyConfigDialog::OnCbnSelchangeComboContext()
{
	int index = m_cmbContext.GetCurSel();
	CString contextName;
	m_cmbContext.GetLBText(index, contextName);

	_ctxCookie = _cmdManager->GetContextCookie(contextName);

	m_availableCommands.ResetContent();

	CString cmdName;
	bool retVal = _cmdManager->GetFirstCommandName(_ctxCookie, cmdName);

	while(retVal)
	{
		m_availableCommands.AddString(cmdName);
		retVal = _cmdManager->GetNextCommandName(cmdName);
	}
}
