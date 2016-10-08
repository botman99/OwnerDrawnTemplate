
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

#include <Windows.h>
#include <CommCtrl.h>

#include "resource.h"

#include "PluginInterface.h"
#include "StaticDialog.h"
#include "menuCmdID.h"
#include "Scintilla.h"

#include "NppParameters.h"

#include "OwnerDrawnTemplate.h"


extern WNDPROC wndProcNotepad;
extern HANDLE g_hModule;
extern bool bIsNppReady;

// The data of Notepad++ that you can use in your plugin commands
NppData nppData;

COwnerDrawnTemplate OwnerDrawnTemplate_MAIN;
COwnerDrawnTemplate OwnerDrawnTemplate_SUB;

int gCurrentView = -1;


void AboutDlg()
{
    ::MessageBox(NULL, TEXT("Hello, Notepad++!"), TEXT("OwnerDrawnTemplate"), MB_OK);
}

void ToggleDlg()
{
	if( gCurrentView == MAIN_VIEW )
	{
		OwnerDrawnTemplate_MAIN.ToggleActiveDoc();
	}
	else if( gCurrentView == SUB_VIEW )
	{
		OwnerDrawnTemplate_SUB.ToggleActiveDoc();
	}

	UpdateDocs();
}

void UpdateDocs()
{
	if( bIsNppReady )
	{
		// get the current Scintilla view
		::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&gCurrentView);

//		TCHAR pszNewPath[MAX_PATH];
//		::SendMessage(nppData._nppHandle, NPPM_GETFULLCURRENTPATH, 0, (LPARAM)pszNewPath);

		// get the number of documents open in the primary (MAIN) view and allocate space to retrieve the filenames
		UINT num_primary_docs = (UINT)::SendMessage(nppData._nppHandle, NPPM_GETNBOPENFILES, 0, (LPARAM)PRIMARY_VIEW);
		LPCTSTR* PrimaryFilenames = (LPCTSTR*)new LPTSTR[num_primary_docs];
		for( UINT i = 0; i < num_primary_docs; i++ )
		{
			PrimaryFilenames[i] = (LPTSTR)new TCHAR[MAX_PATH];
		}

		// get the filenames for the primary view
		::SendMessage(nppData._nppHandle, NPPM_GETOPENFILENAMESPRIMARY, (WPARAM)PrimaryFilenames, (LPARAM)num_primary_docs);

		// get the current active document index for this primary view
		INT primary_doc_index = (INT)::SendMessage(nppData._nppHandle, NPPM_GETCURRENTDOCINDEX, 0, MAIN_VIEW);

		OwnerDrawnTemplate_MAIN.UpdateDocs(PrimaryFilenames, num_primary_docs, primary_doc_index);

		for( UINT i = 0; i < num_primary_docs; i++ )
		{
			delete [] PrimaryFilenames[i];
		}
		delete [] PrimaryFilenames;


		// get the number of documents open in the secondary (SUB) view and allocate space to retrieve the filenames
		UINT num_secondary_docs = (UINT)::SendMessage(nppData._nppHandle, NPPM_GETNBOPENFILES, 0, (LPARAM)SECOND_VIEW);
		LPCTSTR* SecondaryFilenames = (LPCTSTR*)new LPTSTR[num_secondary_docs];
		for( UINT i = 0; i < num_secondary_docs; i++ )
		{
			SecondaryFilenames[i] = (LPTSTR)new TCHAR[MAX_PATH];
		}

		// get the filenames for the secondary view
		::SendMessage(nppData._nppHandle, NPPM_GETOPENFILENAMESSECOND, (WPARAM)SecondaryFilenames, (LPARAM)num_secondary_docs);

		// get the current active document index for this secondary view
		int secondary_doc_index = (int)::SendMessage(nppData._nppHandle, NPPM_GETCURRENTDOCINDEX, 0, SUB_VIEW);

		OwnerDrawnTemplate_SUB.UpdateDocs(SecondaryFilenames, num_secondary_docs, secondary_doc_index);

		for( UINT i = 0; i < num_secondary_docs; i++ )
		{
			delete [] SecondaryFilenames[i];
		}
		delete [] SecondaryFilenames;

		//DebugLog("UpdateDocs: gCurrentView = %d, MAIN = %d, SUB = %d", gCurrentView, primary_doc_index, secondary_doc_index);

		SetupWindows();

		RedrawListView();

		UpdateFocus();
	}
}

void UpdateFocus()
{
	if( bIsNppReady )
	{
		// get the current Scintilla view
		::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&gCurrentView);

		if( gCurrentView == MAIN_VIEW )
		{
			OwnerDrawnTemplate_MAIN.UpdateFocus();
		}
		else if( gCurrentView == SUB_VIEW )
		{
			OwnerDrawnTemplate_SUB.UpdateFocus();
		}
	}
}

void SetupWindows()
{
	OwnerDrawnTemplate_MAIN.SetupWindow();
	OwnerDrawnTemplate_SUB.SetupWindow();
}

void RedrawListView()
{
	if( OwnerDrawnTemplate_MAIN.IsActiveDocEnabled() )  // if the active document is enabled redraw the list view
	{
		OwnerDrawnTemplate_MAIN.RedrawListView();
	}

	if( OwnerDrawnTemplate_SUB.IsActiveDocEnabled() )  // if the active document is enabled redraw the list view
	{
		OwnerDrawnTemplate_SUB.RedrawListView();
	}
}


void COwnerDrawnTemplate::init(int in_view)
{
	view = in_view;

	if( view == MAIN_VIEW )
	{
		_hParentHandle = nppData._scintillaMainHandle;
	}
	else
	{
		_hParentHandle = nppData._scintillaSecondHandle;
	}

	Window::init((HINSTANCE)g_hModule, nppData._nppHandle);

    if( !isCreated() )
	{
		create(IDD_DIALOG, false);
	}
}

void COwnerDrawnTemplate::SetupWindow()
{
	if( bIsNppReady )
	{
		if( active_doc_index == -1 )  // no documents open in this view?
		{
			::ShowWindow(_hSelf, SW_HIDE);  // hide our window
			::ShowWindow(_hListCtrl, SW_HIDE);  // hide the list control in our window
			::ShowWindow(_hParentHandle, SW_HIDE);  // hide the parent handle window
		}
		else if( IsActiveDocEnabled() )
		{
			RECT rect;
			POINT point;

			::GetWindowRect(_hParentHandle, &rect);

			point.x = rect.left;
			point.y = rect.top;

			::ScreenToClient(nppData._nppHandle, &point);
			rect.left = point.x;
			rect.top = point.y;

			point.x = rect.right;
			point.y = rect.bottom;

			::ScreenToClient(nppData._nppHandle, &point);
			rect.right = point.x;
			rect.bottom = point.y;

			DebugLog("SetupWindow: %s, left=%d, top=%d, right=%d, bottom=%d", (view == 0) ? "MAIN_VIEW" : "SUB_VIEW", rect.left, rect.top, rect.right, rect.bottom);

			// set the proper window size and position
			::SetWindowPos(_hSelf, NULL, rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top, FALSE);

			if( !IsWindowVisible(_hSelf) )  // if the owner drawn window is not visible (hidden), show it and hide the parent window
			{
				::ShowWindow(_hSelf, SW_SHOW);  // show our window
				::ShowWindow(_hListCtrl, SW_SHOW);  // show the list control in our window
				::ShowWindow(_hParentHandle, SW_HIDE);  // hide the parent handle window (the normal text view)
			}
		}
		else
		{
			if( !IsWindowVisible(_hParentHandle) )  // if the parent handle window (the normal text view) is not visible (hidden), show that window
			{
				::ShowWindow(_hSelf, SW_HIDE);  // hide our window
				::ShowWindow(_hListCtrl, SW_HIDE);  // hide the list control in our window
				::ShowWindow(_hParentHandle, SW_SHOW);  // show the parent handle window
			}
		}
	}
}

void COwnerDrawnTemplate::ToggleActiveDoc()
{
	if( IsActiveDocValid() )
	{
		Documents[active_doc_index].bIsEnabled = !Documents[active_doc_index].bIsEnabled;
		//DebugLog("ToggleActiveDoc() - Documents[%d].bIsEnabled = %s", active_doc_index, Documents[active_doc_index].bIsEnabled ? "TRUE" : "FALSE");
	}
}

void COwnerDrawnTemplate::UpdateDocs(LPCTSTR* Filenames, UINT filename_count, INT in_active_doc_index)
{
	// create a new list of documents with the filenames in the proper order
	std::vector<DocData> NewDocuments;

	for( UINT i = 0; i < filename_count; i++ )
	{
		DocData doc;
		doc.bIsEnabled = false;  // this will be fixed up before we overwrite the old document list
		wcscpy_s(doc.Filename, MAX_PATH, Filenames[i]);
		NewDocuments.emplace_back(doc);
	}

	// preserve any settings from the old document list into the new document list
	for( DocData& old_doc : Documents )
	{
		for( DocData& new_doc : NewDocuments )
		{
			if( wcscmp(old_doc.Filename, new_doc.Filename) == 0 )
			{
				new_doc.bIsEnabled = old_doc.bIsEnabled;
				break;
			}
		}
	}

	// copy the new document list
	Documents = NewDocuments;

	// set the current active document index
	active_doc_index = in_active_doc_index;
}

void COwnerDrawnTemplate::UpdateFocus()
{
	if( bIsNppReady && IsActiveDocValid() )  // if a document is active see if it needs FOCUS
	{
		if( Documents[active_doc_index].bIsEnabled && (GetFocus() == nppData._nppHandle) )  // if the document is enabled, but not focused, set focus
		{
			//DebugLog("UpdateFocus: %s, SetFocus(_hListCtrl)", (view == 0) ? "MAIN_VIEW" : "SUB_VIEW");
			::SetFocus(_hListCtrl);
		}
		else if( !Documents[active_doc_index].bIsEnabled && (GetFocus() == _hListCtrl) )  // if the document is not enabled and has focus, set focus back to parent handle window (the normal text view)
		{
			//DebugLog("UpdateFocus: %s, SetFocus(_hParentHandle)", (view == 0) ? "MAIN_VIEW" : "SUB_VIEW");
			::SetFocus(_hParentHandle);
		}
	}
}

bool COwnerDrawnTemplate::IsActiveDocValid()
{
	return (active_doc_index >= 0) && (active_doc_index < (INT)Documents.size());
}

bool COwnerDrawnTemplate::IsActiveDocEnabled()
{
	return IsActiveDocValid() && Documents[active_doc_index].bIsEnabled;
}

void COwnerDrawnTemplate::RedrawListView()
{
	::RedrawWindow(_hListCtrl, NULL, NULL, RDW_INVALIDATE);  // redraw the owner drawn window
}

INT_PTR CALLBACK COwnerDrawnTemplate::run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
		case WM_INITDIALOG:
		{
			//DebugLog("run_dlgProc: WM_INITDIALOG (%s)", (view == 0) ? "MAIN_VIEW" : "SUB_VIEW");

			_hListCtrl	= ::GetDlgItem(_hSelf, IDC_LIST);

			/* intial subclassing for key mapping */
			::SetWindowLongPtr(_hListCtrl, GWLP_USERDATA, (LONG_PTR)(void *)this);
			_hDefaultListProc = (WNDPROC)(void *)(::SetWindowLongPtr(_hListCtrl, GWLP_WNDPROC, (LONG_PTR)(void *)wndListProc));

			ListView_SetExtendedListViewStyleEx(_hListCtrl, LVS_EX_ONECLICKACTIVATE, LVS_EX_ONECLICKACTIVATE);

			// set up the list view column format
			LVCOLUMN Column = {LVCF_WIDTH | LVCF_TEXT | LVCF_FMT | LVCF_SUBITEM, LVCFMT_LEFT, 200, TEXT("TEST"), 4, 0};

			for( int i = 0; i < 4; i++ )
			{
				Column.iSubItem = i;
				ListView_InsertColumn(_hListCtrl, i, &Column);
			}

			// create some dummy list view rows where we can display some text
			ListView_SetItemCountEx(_hListCtrl, 10, LVSICF_NOSCROLL);

			break;
		}

		case WM_SIZE:
		case WM_SIZING:
		case WM_MOVING:
		case WM_ENTERSIZEMOVE:
		case WM_EXITSIZEMOVE:
		{
			//DebugLog("run_dlgProc: WM_SIZE / WM_SIZING / WM_MOVING / WM_ENTERSIZEMOVE / WM_EXITSIZEMOVE");
			RECT rc;
			getClientRect(rc);
			::SetWindowPos(_hListCtrl, NULL, rc.left, rc.top, rc.right, rc.bottom, SWP_NOZORDER | SWP_SHOWWINDOW);

			break;
		}

		case WM_ACTIVATE:
		{
			//DebugLog("run_dlgProc: WM_ACTIVATE (%s), wParam = %d", (view == 0) ? "MAIN_VIEW" : "SUB_VIEW", wParam);

			if( wParam )  // activated?
			{
				// set up custom cursor here
			}
			else
			{
				// restore default cursor here
			}

			RedrawListView();

			break;
		}

		case WM_NOTIFY:
		{
			if (((LPNMHDR)lParam)->hwndFrom == _hListCtrl)
			{
				switch (((LPNMHDR)lParam)->code)
				{
					case LVN_GETDISPINFO:
					{
						LV_DISPINFO *lpdi = (LV_DISPINFO *)lParam;

						unsigned int row = lpdi->item.iItem;
						unsigned int column = lpdi->item.iSubItem;

						TCHAR Buffer[256];  // ListView controls can only display 259 characters per column (http://support.microsoft.com/kb/321104)
						size_t buffer_len = _countof(Buffer);

						// display some dummy text in the row/column
						if( (lpdi->item.mask & LVIF_TEXT) )
						{
							if( (row % 2) == 0 )
							{
								if( (column % 2) == 0 )
								{
									swprintf(Buffer, buffer_len, TEXT("OwnerDrawn"));
									wcsncpy_s(lpdi->item.pszText, lpdi->item.cchTextMax, Buffer, buffer_len);
								}
								else
								{
									swprintf(Buffer, buffer_len, TEXT("Document #%ld"), active_doc_index);
									wcsncpy_s(lpdi->item.pszText, lpdi->item.cchTextMax, Buffer, buffer_len);
								}
							}
							else
							{
								if( (column % 2) == 0 )
								{
									swprintf(Buffer, buffer_len, TEXT("Hello"));
									wcsncpy_s(lpdi->item.pszText, lpdi->item.cchTextMax, Buffer, buffer_len);
								}
								else
								{
									swprintf(Buffer, buffer_len, TEXT("World"));
									wcsncpy_s(lpdi->item.pszText, lpdi->item.cchTextMax, Buffer, buffer_len);
								}
							}
						}
					}
				}
			}

			break;
		}

		default:
			break;
	}

	return FALSE;
}

LRESULT COwnerDrawnTemplate::runProcList(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	if( bIsNppReady && IsActiveDocEnabled() )
	{
		switch (Message)
		{
			case WM_SETFOCUS:
			{
				//DebugLog("runProcList: WM_SETFOCUS (%s)", (view == 0) ? "MAIN_VIEW" : "SUB_VIEW");
				break;
			}

			case WM_DROPFILES:  // called when we drag/drop files on the list view (we need to tell NP++ to add these documents)
			{
				//DebugLog("runProcList: WM_DROPFILES (%s)", (view == 0) ? "MAIN_VIEW" : "SUB_VIEW");

				HDROP hDrop	= (HDROP)wParam;

				::SetFocus(_hParentHandle);

				INT filesDropped = ::DragQueryFile(hDrop, 0xffffffff, NULL, 0);
				for (INT i = 0 ; i < filesDropped ; ++i)
				{
					TCHAR pszFilePath[MAX_PATH];
					::DragQueryFile(hDrop, i, pszFilePath, MAX_PATH);
					::SendMessage(_hParent, NPPM_DOOPEN, 0, (LPARAM)pszFilePath);
				}
				::DragFinish(hDrop);

				if (::IsIconic(_hParent))
				{
					::ShowWindow(_hParent, SW_RESTORE);
				}
				::SetForegroundWindow(_hParent);

				return TRUE;
			}

			case WM_KEYDOWN:
			{
				//DebugLog("runProcList: WM_KEYDOWN (%s)", (view == 0) ? "MAIN_VIEW" : "SUB_VIEW");

				bool bCtrlKeyDown = (::GetKeyState(VK_CONTROL) & 0x80) == 0x80;
				bool bAltKeyDown = (::GetKeyState(VK_MENU) & 0x80) == 0x80;
				bool bShiftKeyDown = (::GetKeyState(VK_SHIFT) & 0x80) == 0x80;

				if( (wParam != 0) && (wParam != VK_CONTROL) && (wParam != VK_MENU) && (wParam != VK_SHIFT) )
				{
					bool bKeyFound = false;

					for( int i = 0; i < _countof(winKeyDefs); i++ )
					{
						if( (winKeyDefs[i].vKey == wParam) && (winKeyDefs[i].isCtrl == bCtrlKeyDown) &&
							 (winKeyDefs[i].isAlt == bAltKeyDown) &&  (winKeyDefs[i].isShift == bShiftKeyDown) )
						{
							bKeyFound = true;

							::SendMessage(nppData._nppHandle, WM_COMMAND, winKeyDefs[i].functionId, 0);

							break;
						}
					}

					if( !bKeyFound )
					{
						for( int i = 0; i < _countof(scintKeyDefs); i++ )
						{
							if( (scintKeyDefs[i].vKey == wParam) && (scintKeyDefs[i].isCtrl == bCtrlKeyDown) &&
								 (scintKeyDefs[i].isAlt == bAltKeyDown) &&  (scintKeyDefs[i].isShift == bShiftKeyDown) )
							{
								bKeyFound = true;

								SciFnDirect _pScintillaFunc = nullptr;
								sptr_t _pScintillaPtr = 0L;

								// determine which Scintilla window to send the message to
								if( gCurrentView == MAIN_VIEW )
								{
									_pScintillaFunc = (SciFnDirect)::SendMessage(nppData._scintillaMainHandle, SCI_GETDIRECTFUNCTION, 0, 0);
									_pScintillaPtr = (sptr_t)::SendMessage(nppData._scintillaMainHandle, SCI_GETDIRECTPOINTER, 0, 0);
								}
								else if( gCurrentView == SUB_VIEW )
								{
									_pScintillaFunc = (SciFnDirect)::SendMessage(nppData._scintillaSecondHandle, SCI_GETDIRECTFUNCTION, 0, 0);
									_pScintillaPtr = (sptr_t)::SendMessage(nppData._scintillaSecondHandle, SCI_GETDIRECTPOINTER, 0, 0);
								}

								if( _pScintillaFunc )
								{
									_pScintillaFunc(_pScintillaPtr, scintKeyDefs[i].functionId, 0, 0);
								}

								break;
							}
						}
					}

					if( !bKeyFound )
					{
						if( wParam == VK_F8 )  // the F8 key ("Focus on another view") needs special handling
						{
							//DebugLog("runProcList: WM_KEYDOWN (%s), F8", (view == 0) ? "MAIN_VIEW" : "SUB_VIEW");

							// we are about to switch views, but the IDM_VIEW_SWITCHTO_OTHER_VIEW code in NppCommands.cpp won't work unless Npp thinks it has focus, so give it focus
							if( gCurrentView == MAIN_VIEW )
							{
								::SetFocus(OwnerDrawnTemplate_MAIN._hParentHandle);
							}
							else if( gCurrentView == SUB_VIEW )
							{
								::SetFocus(OwnerDrawnTemplate_SUB._hParentHandle);
							}

							::SendMessage(nppData._nppHandle, WM_COMMAND, IDM_VIEW_SWITCHTO_OTHER_VIEW, 0);
						}
					}
				}

				return TRUE;
			}

			default:
				break;
		}
	}

	return ::CallWindowProc(_hDefaultListProc, hwnd, Message, wParam, lParam);
}


LRESULT CALLBACK SubWndProcNotepad(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT ret = 0;

	switch (message)
	{
		case WM_ACTIVATE:
		{
			//DebugLog("SubWndProcNotepad: WM_ACTIVATE");
			ret = ::CallWindowProc(wndProcNotepad, hWnd, message, wParam, lParam);
			break;
		}

		case WM_COMMAND:
		{
			if (HIWORD(wParam) == SCEN_SETFOCUS)  // FOCUS change between MAIN and SUB views (i.e. mouse clicking on the other view)
			{
				//DebugLog("SubWndProcNotepad: SCEN_SETFOCUS");
				ret = ::CallWindowProc(wndProcNotepad, hWnd, message, wParam, lParam);
				UpdateDocs();

				break;
			}

			// handle some common Notepad++ WM_COMMAND messages here that we might want to do some special processing for (others can be added as needed)

			switch (LOWORD(wParam))
			{
				case IDM_FILE_RELOAD:
				{
					//DebugLog("SubWndProcNotepad: IDM_FILE_RELOAD");
					ret = ::CallWindowProc(wndProcNotepad, hWnd, message, wParam, lParam);
					break;
				}

				case IDM_SEARCH_FIND:
				case IDM_SEARCH_REPLACE:
				{
					//DebugLog("SubWndProcNotepad: IDM_SEARCH_FIND / IDM_SEARCH_REPLACE");
					ret = ::CallWindowProc(wndProcNotepad, hWnd, message, wParam, lParam);
					break;
				}

				case IDM_FILE_SAVE:
				{
					//DebugLog("SubWndProcNotepad: IDM_FILE_SAVE");
					ret = ::CallWindowProc(wndProcNotepad, hWnd, message, wParam, lParam);
					break;
				}

				case IDM_FILE_SAVEAS:
				case IDM_FILE_RENAME:
				{
					//DebugLog("SubWndProcNotepad: IDM_FILE_SAVEAS / IDM_FILE_RENAME");
					ret = ::CallWindowProc(wndProcNotepad, hWnd, message, wParam, lParam);
					UpdateDocs();  // saveas/rename will update the filename, so if we are storing filenames locally we will need to update our documents
					break;
				}

				case IDM_VIEW_TAB_NEXT:
				case IDM_VIEW_TAB_PREV:
				case IDM_VIEW_TAB_MOVEFORWARD:
				case IDM_VIEW_TAB_MOVEBACKWARD:
				case IDM_FILE_CLOSE:
				case IDM_FILE_CLOSEALL:
				case IDM_FILE_CLOSEALL_BUT_CURRENT:
				case IDM_FILE_NEW:
				{
					//DebugLog("SubWndProcNotepad: IDM_VIEW_TAB_NEXT/VIEW_TAB_PREV/FILE_CLOSE/FILE_CLOSEALL/FILE_CLOSEALL_BUT_CURRENT/FILE_NEW");
					ret = ::CallWindowProc(wndProcNotepad, hWnd, message, wParam, lParam);
					UpdateDocs();  // switching tabs and closing documents (or creating new documents) changes which document is the active document
					break;
				}

				case IDM_VIEW_GOTO_ANOTHER_VIEW:
				case IDM_VIEW_CLONE_TO_ANOTHER_VIEW:
				{
					//DebugLog("SubWndProcNotepad: IDM_VIEW_GOTO_ANOTHER_VIEW / IDM_VIEW_CLONE_TO_ANOTHER_VIEW");

					// we are about to switch views, if the document being switched is active, save that state so we can set it again after being moved
					bool bWasActive = false;

					if( (gCurrentView == MAIN_VIEW) && OwnerDrawnTemplate_MAIN.IsActiveDocEnabled() )
					{
						bWasActive = true;
					}
					else if( (gCurrentView == SUB_VIEW) && OwnerDrawnTemplate_SUB.IsActiveDocEnabled() )
					{
						bWasActive = true;
					}

					ret = ::CallWindowProc(wndProcNotepad, hWnd, message, wParam, lParam);
					UpdateDocs();  // switching views changes which Scintilla view is the current view

					if( (gCurrentView == MAIN_VIEW) && OwnerDrawnTemplate_MAIN.IsActiveDocValid() )
					{
						OwnerDrawnTemplate_MAIN.Documents[OwnerDrawnTemplate_MAIN.active_doc_index].bIsEnabled = bWasActive;
						UpdateDocs();
					}
					else if( (gCurrentView == SUB_VIEW) && OwnerDrawnTemplate_SUB.IsActiveDocValid() )
					{
						OwnerDrawnTemplate_SUB.Documents[OwnerDrawnTemplate_SUB.active_doc_index].bIsEnabled = bWasActive;
						UpdateDocs();
					}

					break;
				}

				case IDM_VIEW_SWITCHTO_OTHER_VIEW:
				{
					//DebugLog("SubWndProcNotepad: IDM_VIEW_SWITCHTO_OTHER_VIEW");

					// we are about to switch views, but the IDM_VIEW_SWITCHTO_OTHER_VIEW code in NppCommands.cpp won't work unless Npp thinks it has focus, so give it focus
					if( gCurrentView == MAIN_VIEW )
					{
						if( OwnerDrawnTemplate_MAIN.IsActiveDocEnabled() )
						{
							::SetFocus(OwnerDrawnTemplate_MAIN._hParentHandle);
						}
					}
					else if( gCurrentView == SUB_VIEW )
					{
						if( OwnerDrawnTemplate_SUB.IsActiveDocEnabled() )
						{
							::SetFocus(OwnerDrawnTemplate_SUB._hParentHandle);
						}
					}

					ret = ::CallWindowProc(wndProcNotepad, hWnd, message, wParam, lParam);
					break;
				}

				default:
					// by default, just pass this WM_COMMAND message along to Notepad++
					ret = ::CallWindowProc(wndProcNotepad, hWnd, message, wParam, lParam);
					break;
			}

			break;
		}

		case WM_NOTIFY:
		{
			SCNotification *notifyCode = (SCNotification *)lParam;

			switch (notifyCode->nmhdr.code)
			{
//				case TCN_TABDROPPED:
				case TCN_TABDROPPEDOUTSIDE:
				{
					//DebugLog("SubWndProcNotepad: TCN_TABDROPPEDOUTSIDE");

					int currentView = gCurrentView;

					// we are about to switch views, if the document being switched is active, save that state so we can set it again after being moved
					bool bWasActive = false;

					if( (gCurrentView == MAIN_VIEW) && OwnerDrawnTemplate_MAIN.IsActiveDocEnabled() )
					{
						bWasActive = true;
					}
					else if( (gCurrentView == SUB_VIEW) && OwnerDrawnTemplate_SUB.IsActiveDocEnabled() )
					{
						bWasActive = true;
					}

					ret = ::CallWindowProc(wndProcNotepad, hWnd, message, wParam, lParam);

					if( currentView != gCurrentView )
					{
						if( (gCurrentView == MAIN_VIEW) && OwnerDrawnTemplate_MAIN.IsActiveDocValid() )
						{
							OwnerDrawnTemplate_MAIN.Documents[OwnerDrawnTemplate_MAIN.active_doc_index].bIsEnabled = bWasActive;
							UpdateDocs();
						}
						else if( (gCurrentView == SUB_VIEW) && OwnerDrawnTemplate_SUB.IsActiveDocValid() )
						{
							OwnerDrawnTemplate_SUB.Documents[OwnerDrawnTemplate_SUB.active_doc_index].bIsEnabled = bWasActive;
							UpdateDocs();
						}
					}

					break;
				}

				case TCN_FOCUSCHANGE:
				case TCN_SELCHANGE:  // change between tabs in the same view (MAIN or SUB) or from one view to the other (drag/drop tab across views)
				{
					//DebugLog("SubWndProcNotepad: TCN_SELCHANGE");
					ret = ::CallWindowProc(wndProcNotepad, hWnd, message, wParam, lParam);
					UpdateDocs();  // changing tabs changes which document is active
					break;
				}

				case TCN_TABDELETE:
				{
					//DebugLog("SubWndProcNotepad: TCN_TABDELETE");
					ret = ::CallWindowProc(wndProcNotepad, hWnd, message, wParam, lParam);
					UpdateDocs();  // changing tabs changes which document is active
					break;
				}

				default:
					// by default, just pass this WM_NOTIFY message along to Notepad++
					ret = ::CallWindowProc(wndProcNotepad, hWnd, message, wParam, lParam);
					break;
			}
			break;
		}

		default:
			ret = ::CallWindowProc(wndProcNotepad, hWnd, message, wParam, lParam);
			break;
	}

	return ret;
}
