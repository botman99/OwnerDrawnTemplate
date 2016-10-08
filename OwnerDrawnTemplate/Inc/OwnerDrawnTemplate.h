
// This file is part of Notepad++ project
// Copyright (C)2016 Jeffrey Broome
// Notepad++ Copyright (C)2003 Don HO <donho@altern.org>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// Note that the GPL places important restrictions on "derived works", yet
// it does not provide a detailed definition of that term.  To avoid
// misunderstandings, we consider an application to constitute a
// "derivative work" for the purpose of this license if it does any of the
// following:
// 1. Integrates source code from Notepad++.
// 2. Integrates/includes/aggregates Notepad++ into a proprietary executable
//	installer, such as those produced by InstallShield.
// 3. Links to a library or executes a program that does any of the above.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#pragma once

#include <Windows.h>
#include <vector>

#include "StaticDialog.h"


//Notification message
#define TCN_TABDROPPED (TCN_FIRST - 10)
#define TCN_TABDROPPEDOUTSIDE (TCN_FIRST - 11)
#define TCN_TABDELETE (TCN_FIRST - 12)


void DebugLog(const char* format, ... );

void AboutDlg();
void ToggleDlg();

void UpdateDocs();
void UpdateFocus();
void SetupWindows();
void RedrawListView();

LRESULT CALLBACK SubWndProcNotepad(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

struct DocData
{
	bool bIsEnabled;  // is the plugin enabled for this document?
	TCHAR Filename[MAX_PATH];

	DocData::DocData()
		: bIsEnabled(false)
	{
		Filename[0] = 0;
	}
};


class COwnerDrawnTemplate : public StaticDialog
{
public:
	std::vector<DocData> Documents;
	int active_doc_index;
	int previous_active_doc_index;
	HWND _hParentHandle;  // handle of parent handle (points to scintilla main/sub view)

	COwnerDrawnTemplate()
		: view(-1)
		, _hListCtrl(NULL)
		, _hParentHandle(NULL)
		, _hDefaultListProc(nullptr)
		, active_doc_index(-1)
		, previous_active_doc_index(-1)
	{
	}

    void init(int view);
	void SetupWindow();
	void ToggleActiveDoc();
	void UpdateDocs(LPCTSTR* Filenames, UINT filename_count, INT active_doc_index);
	void UpdateFocus();
	bool IsActiveDocValid();
	bool IsActiveDocEnabled();
	void RedrawListView();

protected :
	virtual INT_PTR CALLBACK run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam);

private:
	int view;  // (0 = MAIN_VIEW, 1 = SUB_VIEW)

	HWND _hListCtrl;

	/* subclassing handle */
	WNDPROC _hDefaultListProc;

	/* Subclassing list proc */
	LRESULT runProcList(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK wndListProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
		return (((COwnerDrawnTemplate*)(::GetWindowLongPtr(hwnd, GWLP_USERDATA)))->runProcList(hwnd, Message, wParam, lParam));
	};
};

extern COwnerDrawnTemplate OwnerDrawnTemplate_MAIN;
extern COwnerDrawnTemplate OwnerDrawnTemplate_SUB;

