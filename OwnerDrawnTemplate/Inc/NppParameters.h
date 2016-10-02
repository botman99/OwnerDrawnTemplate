
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

#include <windows.h>
#include <tchar.h>

#include "keys.h"
#include "menuCmdID.h"


// OwnerDrawnTemplate: This file was extracted from Notepad++ Parameters.cpp file
// We comment out any Notepad++ keys or Scintilla keys that need special processing (they are noted here with "OwnerDrawnTemplate:" in the comment


struct WinMenuKeyDefinition //more or less matches accelerator table definition, easy copy/paste
{
	//const TCHAR * name;	//name retrieved from menu?
	int vKey;
	int functionId;
	bool isCtrl;
	bool isAlt;
	bool isShift;
	TCHAR * specialName;		//Used when no real menu name exists (in case of toggle for example)
};


struct ScintillaKeyDefinition
{
	const TCHAR * name;
	int functionId;
	bool isCtrl;
	bool isAlt;
	bool isShift;
	int vKey;
	int redirFunctionId;	//this gets set  when a function is being redirected through Notepad++ if Scintilla doesnt do it properly :)
};


/*!
** \brief array of accelerator keys for all std menu items
**
** values can be 0 for vKey, which means its unused
*/
static const WinMenuKeyDefinition winKeyDefs[] =
{
	// V_KEY,    COMMAND_ID,                                   Ctrl,  Alt,   Shift, cmdName
	// -------------------------------------------------------------------------------------
	//
	{VK_N,       IDM_FILE_NEW,                                 true,  false, false, nullptr},
	{VK_O,       IDM_FILE_OPEN,                                true,  false, false, nullptr},
	{ VK_NULL,    IDM_FILE_OPEN_FOLDER,                         false, false, false, nullptr },
	{ VK_NULL,    IDM_FILE_OPEN_CMD,                            false, false, false, nullptr },
	{VK_NULL,    IDM_FILE_OPENFOLDERASWORSPACE,                false, false, false, nullptr},
	{VK_NULL,    IDM_FILE_RELOAD,                              false, false, false, nullptr},
	{VK_S,       IDM_FILE_SAVE,                                true,  false, false, nullptr},
	{VK_S,       IDM_FILE_SAVEAS,                              true,  true,  false, nullptr},
	{VK_NULL,    IDM_FILE_SAVECOPYAS,                          false, false, false, nullptr},
	{VK_S,       IDM_FILE_SAVEALL,                             true,  false, true,  nullptr},
	{ VK_NULL,    IDM_FILE_RENAME,                              false, false, false, nullptr },
	{VK_W,       IDM_FILE_CLOSE,                               true,  false, false, nullptr},
	{VK_NULL,    IDM_FILE_CLOSEALL,                            false, false, false, nullptr},
	{VK_NULL,    IDM_FILE_CLOSEALL_BUT_CURRENT,                false, false, false, nullptr},
	{VK_NULL,    IDM_FILE_CLOSEALL_TOLEFT,                     false, false, false, nullptr},
	{VK_NULL,    IDM_FILE_CLOSEALL_TORIGHT,                    false, false, false, nullptr},
	{VK_NULL,    IDM_FILE_DELETE,                              false, false, false, nullptr},
	{VK_NULL,    IDM_FILE_LOADSESSION,                         false, false, false, nullptr},
	{VK_NULL,    IDM_FILE_SAVESESSION,                         false, false, false, nullptr},
	{VK_P,       IDM_FILE_PRINT,                               true,  false, false, nullptr},
	{VK_NULL,    IDM_FILE_PRINTNOW,                            false, false, false, nullptr},
	{VK_F4,      IDM_FILE_EXIT,                                false, true,  false, nullptr},
	{ VK_T,      IDM_FILE_RESTORELASTCLOSEDFILE,               true,  false,  true, TEXT("Restore Recent Closed File")},

//	{VK_NULL,    IDM_EDIT_UNDO,                                false, false, false, nullptr},
//	{VK_NULL,    IDM_EDIT_REDO,                                false, false, false, nullptr},
//	{VK_NULL,    IDM_EDIT_CUT,                                 false, false, false, nullptr},
//	{VK_NULL,    IDM_EDIT_COPY,                                false, false, false, nullptr},
//	{VK_NULL,    IDM_EDIT_PASTE,                               false, false, false, nullptr},
//	{VK_NULL,    IDM_EDIT_DELETE,                              false, false, false, nullptr},
//	{VK_NULL,    IDM_EDIT_SELECTALL,                           false, false, false, nullptr},
	{ VK_NULL,    IDM_EDIT_BEGINENDSELECT,                      false, false, false, nullptr },

	{VK_NULL,    IDM_EDIT_FULLPATHTOCLIP,                      false, false, false, nullptr},
	{VK_NULL,    IDM_EDIT_FILENAMETOCLIP,                      false, false, false, nullptr},
	{VK_NULL,    IDM_EDIT_CURRENTDIRTOCLIP,                    false, false, false, nullptr},
//	{VK_NULL,    IDM_EDIT_INS_TAB,                             false, false, false, nullptr},
//	{VK_NULL,    IDM_EDIT_RMV_TAB,                             false, false, false, nullptr},
	{VK_U,       IDM_EDIT_UPPERCASE,                           true,  false, true,  nullptr},
	{VK_U,       IDM_EDIT_LOWERCASE,                           true,  false, false, nullptr},
	{ VK_U,       IDM_EDIT_PROPERCASE_FORCE,                    false, true,  false, nullptr },
	{ VK_U,       IDM_EDIT_PROPERCASE_BLEND,                    false, true,  true,  nullptr },
	{VK_U,       IDM_EDIT_SENTENCECASE_FORCE,                  true,  true,  false, nullptr},
	{VK_U,       IDM_EDIT_SENTENCECASE_BLEND,                  true,  true,  true,  nullptr},
	{VK_NULL,    IDM_EDIT_INVERTCASE,                          false, false, false, nullptr},
	{VK_NULL,    IDM_EDIT_RANDOMCASE,                          false, false, false, nullptr},
//	{ VK_NULL,    IDM_EDIT_DUP_LINE,                            false, false, false, nullptr },
	{ VK_I,       IDM_EDIT_SPLIT_LINES,                         true,  false, false, nullptr },
	{ VK_J,       IDM_EDIT_JOIN_LINES,                          true,  false, false, nullptr },
	{ VK_UP,      IDM_EDIT_LINE_UP,                             true,  false, true,  nullptr },
	{ VK_DOWN,    IDM_EDIT_LINE_DOWN,                           true,  false, true,  nullptr },
	{ VK_NULL,    IDM_EDIT_REMOVEEMPTYLINES,                    false, false, false, nullptr },
	{ VK_NULL,    IDM_EDIT_REMOVEEMPTYLINESWITHBLANK,           false, false, false, nullptr },
	{ VK_RETURN,  IDM_EDIT_BLANKLINEABOVECURRENT,               true,  true,  false, nullptr },
	{ VK_RETURN,  IDM_EDIT_BLANKLINEBELOWCURRENT,               true,  true,  true,  nullptr },
	{ VK_NULL,    IDM_EDIT_SORTLINES_LEXICOGRAPHIC_ASCENDING,   false, false, false, nullptr },
	{ VK_NULL,    IDM_EDIT_SORTLINES_LEXICOGRAPHIC_DESCENDING,  false, false, false, nullptr },
	{ VK_NULL,    IDM_EDIT_SORTLINES_INTEGER_ASCENDING,         false, false, false, nullptr },
	{ VK_NULL,    IDM_EDIT_SORTLINES_INTEGER_DESCENDING,        false, false, false, nullptr },
	{ VK_NULL,    IDM_EDIT_SORTLINES_DECIMALCOMMA_ASCENDING,    false, false, false, nullptr },
	{ VK_NULL,    IDM_EDIT_SORTLINES_DECIMALCOMMA_DESCENDING,   false, false, false, nullptr },
	{ VK_NULL,    IDM_EDIT_SORTLINES_DECIMALDOT_ASCENDING,      false, false, false, nullptr },
	{ VK_NULL,    IDM_EDIT_SORTLINES_DECIMALDOT_DESCENDING,     false, false, false, nullptr },
	{VK_Q,       IDM_EDIT_BLOCK_COMMENT,                       true,  false, false, nullptr},
	{VK_K,       IDM_EDIT_BLOCK_COMMENT_SET,                   true,  false, false, nullptr},
	{VK_K,       IDM_EDIT_BLOCK_UNCOMMENT,                     true,  false, true,  nullptr},
	{VK_Q,       IDM_EDIT_STREAM_COMMENT,                      true,  false, true,  nullptr},
	{VK_NULL,    IDM_EDIT_STREAM_UNCOMMENT,                    false, false, false, nullptr},
	{VK_SPACE,   IDM_EDIT_AUTOCOMPLETE,                        true,  false, false, nullptr},
	{VK_SPACE,   IDM_EDIT_AUTOCOMPLETE_PATH,                   true,  true, false,  nullptr},
	{VK_RETURN,  IDM_EDIT_AUTOCOMPLETE_CURRENTFILE,            true,  false, false, nullptr},
	{VK_SPACE,   IDM_EDIT_FUNCCALLTIP,                         true,  false, true,  nullptr},
	{ VK_NULL,    IDM_FORMAT_TODOS,                             false, false, false, nullptr },
	{ VK_NULL,    IDM_FORMAT_TOUNIX,                            false, false, false, nullptr },
	{ VK_NULL,    IDM_FORMAT_TOMAC,                             false, false, false, nullptr },
	{ VK_NULL,    IDM_EDIT_TRIMTRAILING,                        false, false, false, nullptr },
	{ VK_NULL,    IDM_EDIT_TRIMLINEHEAD,                        false, false, false, nullptr },
	{ VK_NULL,    IDM_EDIT_TRIM_BOTH,                           false, false, false, nullptr },
	{ VK_NULL,    IDM_EDIT_EOL2WS,                              false, false, false, nullptr },
	{ VK_NULL,    IDM_EDIT_TRIMALL,                             false, false, false, nullptr },
	{ VK_NULL,    IDM_EDIT_TAB2SW,                              false, false, false, nullptr },
	{ VK_NULL,    IDM_EDIT_SW2TAB_ALL,                          false, false, false, nullptr },
	{ VK_NULL,    IDM_EDIT_SW2TAB_LEADING,                      false, false, false, nullptr },
	{ VK_NULL,    IDM_EDIT_PASTE_AS_HTML,                       false, false, false, nullptr },
	{ VK_NULL,    IDM_EDIT_PASTE_AS_RTF,                        false, false, false, nullptr },
	{ VK_NULL,    IDM_EDIT_COPY_BINARY,                         false, false, false, nullptr },
	{ VK_NULL,    IDM_EDIT_CUT_BINARY,                          false, false, false, nullptr },
	{ VK_NULL,    IDM_EDIT_PASTE_BINARY,                        false, false, false, nullptr },
	{ VK_NULL,    IDM_EDIT_OPENASFILE,                          false, false, false, nullptr },
	{ VK_NULL,    IDM_EDIT_OPENINFOLDER,                        false, false, false, nullptr },
	{ VK_NULL,    IDM_EDIT_SEARCHONINTERNET,                    false, false, false, nullptr },
	{ VK_NULL,    IDM_EDIT_CHANGESEARCHENGINE,                  false, false, false, nullptr },
//  { VK_NULL,    IDM_EDIT_COLUMNMODETIP,                       false, false, false, nullptr },
	{ VK_C,       IDM_EDIT_COLUMNMODE,                          false, true,  false, nullptr },
	{ VK_NULL,    IDM_EDIT_CHAR_PANEL,                          false, false, false, nullptr },
	{ VK_NULL,    IDM_EDIT_CLIPBOARDHISTORY_PANEL,              false, false, false, nullptr },
	{ VK_NULL,    IDM_EDIT_SETREADONLY,                         false, false, false, nullptr },
	{ VK_NULL,    IDM_EDIT_CLEARREADONLY,                       false, false, false, nullptr },
	{VK_F,       IDM_SEARCH_FIND,                              true,  false, false, nullptr},
	{VK_F,       IDM_SEARCH_FINDINFILES,                       true,  false, true,  nullptr},
	{VK_F3,      IDM_SEARCH_FINDNEXT,                          false, false, false, nullptr},
	{VK_F3,      IDM_SEARCH_FINDPREV,                          false, false, true,  nullptr},
	{ VK_F3,      IDM_SEARCH_SETANDFINDNEXT,                    true,  false, false, nullptr },
	{ VK_F3,      IDM_SEARCH_SETANDFINDPREV,                    true,  false, true,  nullptr },
	{VK_F3,      IDM_SEARCH_VOLATILE_FINDNEXT,                 true,  true, false,  nullptr},
	{VK_F3,      IDM_SEARCH_VOLATILE_FINDPREV,                 true,  true, true,   nullptr},
	{VK_H,       IDM_SEARCH_REPLACE,                           true,  false, false, nullptr},
	{VK_I,       IDM_SEARCH_FINDINCREMENT,                     true,  true,  false, nullptr},
	{ VK_F7,      IDM_FOCUS_ON_FOUND_RESULTS,                   false, false, false, nullptr },
	{ VK_F4,      IDM_SEARCH_GOTOPREVFOUND,                     false, false, true,  nullptr },
	{ VK_F4,      IDM_SEARCH_GOTONEXTFOUND,                     false, false, false, nullptr },
	{VK_G,       IDM_SEARCH_GOTOLINE,                          true,  false, false, nullptr},
	{VK_B,       IDM_SEARCH_GOTOMATCHINGBRACE,                 true,  false, false, nullptr},
	{VK_B,       IDM_SEARCH_SELECTMATCHINGBRACES,              true,  true,  false, nullptr},
	{VK_NULL,    IDM_SEARCH_MARK,                              false, false, false, nullptr},
	{VK_NULL,    IDM_SEARCH_MARKALLEXT1,                       false, false, false, nullptr},
	{VK_NULL,    IDM_SEARCH_MARKALLEXT2,                       false, false, false, nullptr},
	{VK_NULL,    IDM_SEARCH_MARKALLEXT3,                       false, false, false, nullptr},
	{VK_NULL,    IDM_SEARCH_MARKALLEXT4,                       false, false, false, nullptr},
	{VK_NULL,    IDM_SEARCH_MARKALLEXT5,                       false, false, false, nullptr},
	{VK_NULL,    IDM_SEARCH_UNMARKALLEXT1,                     false, false, false, nullptr},
	{VK_NULL,    IDM_SEARCH_UNMARKALLEXT2,                     false, false, false, nullptr},
	{VK_NULL,    IDM_SEARCH_UNMARKALLEXT3,                     false, false, false, nullptr},
	{VK_NULL,    IDM_SEARCH_UNMARKALLEXT4,                     false, false, false, nullptr},
	{VK_NULL,    IDM_SEARCH_UNMARKALLEXT5,                     false, false, false, nullptr},
	{VK_NULL,    IDM_SEARCH_CLEARALLMARKS,                     false, false, false, nullptr},
	{VK_1,       IDM_SEARCH_GOPREVMARKER1,                     true,  false, true,  nullptr},
	{VK_2,       IDM_SEARCH_GOPREVMARKER2,                     true,  false, true,  nullptr},
	{VK_3,       IDM_SEARCH_GOPREVMARKER3,                     true,  false, true,  nullptr},
	{VK_4,       IDM_SEARCH_GOPREVMARKER4,                     true,  false, true,  nullptr},
	{VK_5,       IDM_SEARCH_GOPREVMARKER5,                     true,  false, true,  nullptr},
	{VK_0,       IDM_SEARCH_GOPREVMARKER_DEF,                  true,  false, true,  nullptr},
	{ VK_1,       IDM_SEARCH_GONEXTMARKER1,                     true,  false, false, nullptr },
	{ VK_2,       IDM_SEARCH_GONEXTMARKER2,                     true,  false, false, nullptr },
	{ VK_3,       IDM_SEARCH_GONEXTMARKER3,                     true,  false, false, nullptr },
	{ VK_4,       IDM_SEARCH_GONEXTMARKER4,                     true,  false, false, nullptr },
	{ VK_5,       IDM_SEARCH_GONEXTMARKER5,                     true,  false, false, nullptr },
	{ VK_0,       IDM_SEARCH_GONEXTMARKER_DEF,                  true,  false, false, nullptr },

	{ VK_F2,      IDM_SEARCH_TOGGLE_BOOKMARK,                   true,  false, false, nullptr },
	{ VK_F2,      IDM_SEARCH_NEXT_BOOKMARK,                     false, false, false, nullptr },
	{ VK_F2,      IDM_SEARCH_PREV_BOOKMARK,                     false, false, true, nullptr  },
	{ VK_NULL,    IDM_SEARCH_CLEAR_BOOKMARKS,                   false, false, false, nullptr },
	{ VK_NULL,    IDM_SEARCH_CUTMARKEDLINES,                    false, false, false, nullptr },
	{ VK_NULL,    IDM_SEARCH_COPYMARKEDLINES,                   false, false, false, nullptr },
	{ VK_NULL,    IDM_SEARCH_PASTEMARKEDLINES,                  false, false, false, nullptr },
	{ VK_NULL,    IDM_SEARCH_DELETEMARKEDLINES,                 false, false, false, nullptr },
	{ VK_NULL,    IDM_SEARCH_DELETEUNMARKEDLINES,               false, false, false, nullptr },
	{ VK_NULL,    IDM_SEARCH_INVERSEMARKS,                      false, false, false, nullptr },
	{ VK_NULL,    IDM_SEARCH_FINDCHARINRANGE,                   false, false, false, nullptr },
				 
	{ VK_NULL,    IDM_VIEW_ALWAYSONTOP,                         false, false, false, nullptr },
	{VK_F11,     IDM_VIEW_FULLSCREENTOGGLE,                    false, false, false, nullptr},
	{VK_F12,     IDM_VIEW_POSTIT,                              false, false, false, nullptr},
	{VK_NULL,    IDM_VIEW_TAB_SPACE,                           false, false, false, nullptr},
	{VK_NULL,    IDM_VIEW_EOL,                                 false, false, false, nullptr},
	{VK_NULL,    IDM_VIEW_ALL_CHARACTERS,                      false, false, false, nullptr},
	{VK_NULL,    IDM_VIEW_INDENT_GUIDE,                        false, false, false, nullptr},
	{VK_NULL,    IDM_VIEW_WRAP_SYMBOL,                         false, false, false, nullptr},
    // {VK_NULL,    IDM_VIEW_ZOOMIN,                           false, false, false, nullptr},
    // {VK_NULL,    IDM_VIEW_ZOOMOUT,                          false, false, false, nullptr},
    // {VK_NULL,    IDM_VIEW_ZOOMRESTORE,                      false, false, false, nullptr},
	{ VK_NULL,    IDM_VIEW_GOTO_ANOTHER_VIEW,                   false, false, false, nullptr },
	{ VK_NULL,    IDM_VIEW_CLONE_TO_ANOTHER_VIEW,               false, false, false, nullptr },
	{ VK_NULL,    IDM_VIEW_GOTO_NEW_INSTANCE,                   false, false, false, nullptr },
	{ VK_NULL,    IDM_VIEW_LOAD_IN_NEW_INSTANCE,                false, false, false, nullptr },

	{ VK_NUMPAD1, IDM_VIEW_TAB1,                                true,  false, false, nullptr },
	{ VK_NUMPAD2, IDM_VIEW_TAB2,                                true,  false, false, nullptr },
	{ VK_NUMPAD3, IDM_VIEW_TAB3,                                true,  false, false, nullptr },
	{ VK_NUMPAD4, IDM_VIEW_TAB4,                                true,  false, false, nullptr },
	{ VK_NUMPAD5, IDM_VIEW_TAB5,                                true,  false, false, nullptr },
	{ VK_NUMPAD6, IDM_VIEW_TAB6,                                true,  false, false, nullptr },
	{ VK_NUMPAD7, IDM_VIEW_TAB7,                                true,  false, false, nullptr },
	{ VK_NUMPAD8, IDM_VIEW_TAB8,                                true,  false, false, nullptr },
	{ VK_NUMPAD9, IDM_VIEW_TAB9,                                true,  false, false, nullptr },
	{ VK_NEXT,    IDM_VIEW_TAB_NEXT,                            true,  false, false, nullptr },
	{ VK_PRIOR,   IDM_VIEW_TAB_PREV,                            true,  false, false, nullptr },
	{ VK_NEXT,    IDM_VIEW_TAB_MOVEFORWARD,                     true,  false, true,  nullptr },
	{ VK_PRIOR,   IDM_VIEW_TAB_MOVEBACKWARD,                    true,  false, true,  nullptr },
//	{ VK_TAB,     IDC_PREV_DOC,                                 true,  false, true,  TEXT("Switch to previous document") },  // OwnerDrawnTemplate: 'IDC_PREV_DOC' is no longer defined in menuCmdID.h
//	{ VK_TAB,     IDC_NEXT_DOC,                                 true,  false, false, TEXT("Switch to next document") },  // OwnerDrawnTemplate: 'IDC_NEXT_DOC' is no longer defined in menuCmdID.h
	{ VK_NULL,    IDM_VIEW_WRAP,                                false, false, false, nullptr },
	{ VK_H,       IDM_VIEW_HIDELINES,                           false, true,  false, nullptr },
//	{ VK_F8,      IDM_VIEW_SWITCHTO_OTHER_VIEW,                 false, false, false, nullptr },  // OwnerDrawnTemplate: Requires special processing for FOCUS

	{VK_0,       IDM_VIEW_TOGGLE_FOLDALL,                      false, true,  false, nullptr},
	{ VK_0,       IDM_VIEW_TOGGLE_UNFOLDALL,                    false, true,  true,  nullptr },
	{VK_F,       IDM_VIEW_FOLD_CURRENT,                        true,  true,  false, nullptr},
	{ VK_F,       IDM_VIEW_UNFOLD_CURRENT,                      true,  true,  true,  nullptr },
	{VK_1,       IDM_VIEW_FOLD_1,                              false, true,  false, nullptr},
	{VK_2,       IDM_VIEW_FOLD_2,                              false, true,  false, nullptr},
	{VK_3,       IDM_VIEW_FOLD_3,                              false, true,  false, nullptr},
	{VK_4,       IDM_VIEW_FOLD_4,                              false, true,  false, nullptr},
	{VK_5,       IDM_VIEW_FOLD_5,                              false, true,  false, nullptr},
	{VK_6,       IDM_VIEW_FOLD_6,                              false, true,  false, nullptr},
	{VK_7,       IDM_VIEW_FOLD_7,                              false, true,  false, nullptr},
	{VK_8,       IDM_VIEW_FOLD_8,                              false, true,  false, nullptr},

	{VK_1,       IDM_VIEW_UNFOLD_1,                            false, true,  true,  nullptr},
	{VK_2,       IDM_VIEW_UNFOLD_2,                            false, true,  true,  nullptr},
	{VK_3,       IDM_VIEW_UNFOLD_3,                            false, true,  true,  nullptr},
	{VK_4,       IDM_VIEW_UNFOLD_4,                            false, true,  true,  nullptr},
	{VK_5,       IDM_VIEW_UNFOLD_5,                            false, true,  true,  nullptr},
	{VK_6,       IDM_VIEW_UNFOLD_6,                            false, true,  true,  nullptr},
	{VK_7,       IDM_VIEW_UNFOLD_7,                            false, true,  true,  nullptr},
	{VK_8,       IDM_VIEW_UNFOLD_8,                            false, true,  true,  nullptr},
	{ VK_NULL,    IDM_VIEW_SUMMARY,                             false, false, false, nullptr },
	{ VK_NULL,    IDM_VIEW_PROJECT_PANEL_1,                     false, false, false, nullptr },
	{ VK_NULL,    IDM_VIEW_PROJECT_PANEL_2,                     false, false, false, nullptr },
	{ VK_NULL,    IDM_VIEW_PROJECT_PANEL_3,                     false, false, false, nullptr },
	{ VK_NULL,    IDM_VIEW_FILEBROWSER,                         false, false, false, nullptr },
	{ VK_NULL,    IDM_VIEW_DOC_MAP,                             false, false, false, nullptr },
	{ VK_NULL,    IDM_VIEW_FUNC_LIST,                           false, false, false, nullptr },
	{VK_NULL,    IDM_VIEW_SYNSCROLLV,                          false, false, false, nullptr},
	{VK_NULL,    IDM_VIEW_SYNSCROLLH,                          false, false, false, nullptr},
	{ VK_R,       IDM_EDIT_RTL,                                 true,  true,  false, nullptr },
	{ VK_L,       IDM_EDIT_LTR,                                 true,  true,  false, nullptr },
	{ VK_NULL,    IDM_VIEW_MONITORING,                          false, false, false, nullptr },

	{VK_NULL,    IDM_FORMAT_ANSI,                              false, false, false, nullptr},
	{ VK_NULL,    IDM_FORMAT_AS_UTF_8,                          false, false, false, nullptr },
	{VK_NULL,    IDM_FORMAT_UTF_8,                             false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_UCS_2BE,                           false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_UCS_2LE,                           false, false, false, nullptr},

	{VK_NULL,    IDM_FORMAT_ISO_8859_6,                        false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_WIN_1256,                          false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_ISO_8859_13,                       false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_WIN_1257,                          false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_ISO_8859_14,                       false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_ISO_8859_5,                        false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_MAC_CYRILLIC,                      false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_KOI8R_CYRILLIC,                    false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_KOI8U_CYRILLIC,                    false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_WIN_1251,                          false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_WIN_1250,                          false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_DOS_437,                           false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_DOS_720,                           false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_DOS_737,                           false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_DOS_775,                           false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_DOS_850,                           false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_DOS_852,                           false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_DOS_855,                           false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_DOS_857,                           false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_DOS_858,                           false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_DOS_860,                           false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_DOS_861,                           false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_DOS_862,                           false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_DOS_863,                           false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_DOS_865,                           false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_DOS_866,                           false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_DOS_869,                           false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_BIG5,                              false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_GB2312,                            false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_ISO_8859_2,                        false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_ISO_8859_7,                        false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_WIN_1253,                          false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_ISO_8859_8,                        false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_WIN_1255,                          false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_SHIFT_JIS,                         false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_EUC_KR,                            false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_ISO_8859_10,                       false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_ISO_8859_15,                       false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_ISO_8859_4,                        false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_ISO_8859_16,                       false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_ISO_8859_3,                        false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_ISO_8859_11,                       false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_TIS_620,                           false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_ISO_8859_9,                        false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_WIN_1254,                          false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_WIN_1252,                          false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_ISO_8859_1,                        false, false, false, nullptr},
	{VK_NULL,    IDM_FORMAT_WIN_1258,                          false, false, false, nullptr},
	{ VK_NULL,    IDM_FORMAT_CONV2_ANSI,                        false, false, false, nullptr },
	{ VK_NULL,    IDM_FORMAT_CONV2_AS_UTF_8,                    false, false, false, nullptr },
	{ VK_NULL,    IDM_FORMAT_CONV2_UTF_8,                       false, false, false, nullptr },
	{ VK_NULL,    IDM_FORMAT_CONV2_UCS_2BE,                     false, false, false, nullptr },
	{ VK_NULL,    IDM_FORMAT_CONV2_UCS_2LE,                     false, false, false, nullptr },

	{ VK_NULL,    IDM_LANG_USER_DLG,                            false, false, false, nullptr },
	{ VK_NULL,    IDM_LANG_USER,                                false, false, false, nullptr },

	{VK_NULL,    IDM_SETTING_PREFERECE,                        false, false, false, nullptr},
	{VK_NULL,    IDM_LANGSTYLE_CONFIG_DLG,                     false, false, false, nullptr},
	{VK_NULL,    IDM_SETTING_SHORTCUT_MAPPER,                  false, false, false, nullptr},
	{ VK_NULL,    IDM_SETTING_IMPORTPLUGIN,                     false, false, false, nullptr },
	{ VK_NULL,    IDM_SETTING_IMPORTSTYLETHEMS,                 false, false, false, nullptr },
	{ VK_NULL,    IDM_SETTING_EDITCONTEXTMENU,                  false, false, false, nullptr },

//	{ VK_R,       IDC_EDIT_TOGGLEMACRORECORDING,                true,  false, true,  TEXT("Toggle macro record")},  // OwnerDrawnTemplate: 'IDC_EDIT_TOGGLEMACRORECORDING' is no longer defined in menuCmdID.h
	{ VK_NULL,    IDM_MACRO_STARTRECORDINGMACRO,                false, false, false, nullptr },
	{ VK_NULL,    IDM_MACRO_STOPRECORDINGMACRO,                 false, false, false, nullptr },
	{VK_P,       IDM_MACRO_PLAYBACKRECORDEDMACRO,              true,  false, true,  nullptr},
	{VK_NULL,    IDM_MACRO_SAVECURRENTMACRO,                   false, false, false, nullptr},
	{VK_NULL,    IDM_MACRO_RUNMULTIMACRODLG,                   false, false, false, nullptr},

	{VK_F5,      IDM_EXECUTE,                                  false, false, false, nullptr},

	{ VK_NULL,    IDM_CMDLINEARGUMENTS,                         false, false, false, nullptr },
	{VK_NULL,    IDM_HOMESWEETHOME,                            false, false, false, nullptr},
	{VK_NULL,    IDM_PROJECTPAGE,                              false, false, false, nullptr},
//  { VK_NULL,    IDM_ONLINEHELP,                               false, false, false, nullptr },
	{VK_NULL,    IDM_FORUM,                                    false, false, false, nullptr},
	{ VK_NULL,    IDM_ONLINESUPPORT,                            false, false, false, nullptr },
	{VK_NULL,    IDM_PLUGINSHOME,                              false, false, false, nullptr},
	{ VK_NULL,    IDM_UPDATE_NPP,                               false, false, false, nullptr },
	{ VK_NULL,    IDM_CONFUPDATERPROXY,                         false, false, false, nullptr },
	{ VK_NULL,    IDM_DEBUGINFO,                                false, false, false, nullptr },
	{ VK_F1,      IDM_ABOUT,                                    false, false, false, nullptr }
//  { VK_F1,      IDM_HELP,                                     false, false, true,  nullptr }
};




/*!
** \brief array of accelerator keys for all possible scintilla functions
**
** values can be 0 for vKey, which means its unused
*/
static const ScintillaKeyDefinition scintKeyDefs[] =
{
	{TEXT("SCI_CUT"),                     SCI_CUT,                     true,  false, false, VK_X,        IDM_EDIT_CUT},
	{TEXT(""),                            SCI_CUT,                     false, false, true,  VK_DELETE,   0},
	{TEXT("SCI_COPY"),                    SCI_COPY,                    true,  false, false, VK_C,        IDM_EDIT_COPY},
	{TEXT(""),                            SCI_COPY,                    true,  false, false, VK_INSERT,   0},
	{TEXT("SCI_PASTE"),                   SCI_PASTE,                   true,  false, false, VK_V,        IDM_EDIT_PASTE},
	{TEXT(""),                            SCI_PASTE,                   false, false, true,  VK_INSERT,   0},
	{TEXT("SCI_SELECTALL"),               SCI_SELECTALL,               true,  false, false, VK_A,        IDM_EDIT_SELECTALL},
	{TEXT("SCI_CLEAR"),                   SCI_CLEAR,                   false, false, false, VK_DELETE,   IDM_EDIT_DELETE},
	{TEXT("SCI_CLEARALL"),                SCI_CLEARALL,                false, false, false, 0,           0},
	{TEXT("SCI_UNDO"),                    SCI_UNDO,                    true,  false, false, VK_Z,        IDM_EDIT_UNDO},
	{TEXT(""),                            SCI_UNDO,                    false, true,  false, VK_BACK,     0},
	{TEXT("SCI_REDO"),                    SCI_REDO,                    true,  false, false, VK_Y,        IDM_EDIT_REDO},
	{TEXT(""),                            SCI_REDO,                    true,  false, true,  VK_Z,        0},
	{TEXT("SCI_NEWLINE"),                 SCI_NEWLINE,                 false, false, false, VK_RETURN,   0},
	{TEXT(""),                            SCI_NEWLINE,                 false, false, true,  VK_RETURN,   0},
	{TEXT("SCI_TAB"),                     SCI_TAB,                     false, false, false, VK_TAB,      IDM_EDIT_INS_TAB},
	{TEXT("SCI_BACKTAB"),                 SCI_BACKTAB,                 false, false, true,  VK_TAB,      IDM_EDIT_RMV_TAB},
	{TEXT("SCI_FORMFEED"),                SCI_FORMFEED,                false, false, false, 0,           0},
	{TEXT("SCI_ZOOMIN"),                  SCI_ZOOMIN,                  true,  false, false, VK_ADD,      IDM_VIEW_ZOOMIN},
	{TEXT("SCI_ZOOMOUT"),                 SCI_ZOOMOUT,                 true,  false, false, VK_SUBTRACT, IDM_VIEW_ZOOMOUT},
	{TEXT("SCI_SETZOOM"),                 SCI_SETZOOM,                 true,  false, false, VK_DIVIDE,   IDM_VIEW_ZOOMRESTORE},
	{TEXT("SCI_SELECTIONDUPLICATE"),      SCI_SELECTIONDUPLICATE,      true,  false, false, VK_D,        IDM_EDIT_DUP_LINE},
	{TEXT("SCI_LINESJOIN"),               SCI_LINESJOIN,               false, false, false, 0,           0},
	{TEXT("SCI_SCROLLCARET"),             SCI_SCROLLCARET,             false, false, false, 0,           0},
	{TEXT("SCI_EDITTOGGLEOVERTYPE"),      SCI_EDITTOGGLEOVERTYPE,      false, false, false, VK_INSERT,   0},
	{TEXT("SCI_MOVECARETINSIDEVIEW"),     SCI_MOVECARETINSIDEVIEW,     false, false, false, 0,           0},
	{TEXT("SCI_LINEDOWN"),                SCI_LINEDOWN,                false, false, false, VK_DOWN,     0},
	{TEXT("SCI_LINEDOWNEXTEND"),          SCI_LINEDOWNEXTEND,          false, false, true,  VK_DOWN,     0},
	{TEXT("SCI_LINEDOWNRECTEXTEND"),      SCI_LINEDOWNRECTEXTEND,      false, true,  true,  VK_DOWN,     0},
	{TEXT("SCI_LINESCROLLDOWN"),          SCI_LINESCROLLDOWN,          true,  false, false, VK_DOWN,     0},
	{TEXT("SCI_LINEUP"),                  SCI_LINEUP,                  false, false, false, VK_UP,       0},
	{TEXT("SCI_LINEUPEXTEND"),            SCI_LINEUPEXTEND,            false, false, true,  VK_UP,       0},
	{TEXT("SCI_LINEUPRECTEXTEND"),        SCI_LINEUPRECTEXTEND,        false, true,  true,  VK_UP,       0},
	{TEXT("SCI_LINESCROLLUP"),            SCI_LINESCROLLUP,            true,  false, false, VK_UP,       0},
	{TEXT("SCI_PARADOWN"),                SCI_PARADOWN,                true,  false, false, VK_OEM_6,    0},
	{TEXT("SCI_PARADOWNEXTEND"),          SCI_PARADOWNEXTEND,          true,  false, true,  VK_OEM_6,    0},
	{TEXT("SCI_PARAUP"),                  SCI_PARAUP,                  true,  false, false, VK_OEM_4,    0},
	{TEXT("SCI_PARAUPEXTEND"),            SCI_PARAUPEXTEND,            true,  false, true,  VK_OEM_4,    0},
	{TEXT("SCI_CHARLEFT"),                SCI_CHARLEFT,                false, false, false, VK_LEFT,     0},
	{TEXT("SCI_CHARLEFTEXTEND"),          SCI_CHARLEFTEXTEND,          false, false, true,  VK_LEFT,     0},
	{TEXT("SCI_CHARLEFTRECTEXTEND"),      SCI_CHARLEFTRECTEXTEND,      false, true,  true,  VK_LEFT,     0},
	{TEXT("SCI_CHARRIGHT"),               SCI_CHARRIGHT,               false, false, false, VK_RIGHT,    0},
	{TEXT("SCI_CHARRIGHTEXTEND"),         SCI_CHARRIGHTEXTEND,         false, false, true,  VK_RIGHT,    0},
	{TEXT("SCI_CHARRIGHTRECTEXTEND"),     SCI_CHARRIGHTRECTEXTEND,     false, true,  true,  VK_RIGHT,    0},
	{TEXT("SCI_WORDLEFT"),                SCI_WORDLEFT,                true,  false, false, VK_LEFT,     0},
	{TEXT("SCI_WORDLEFTEXTEND"),          SCI_WORDLEFTEXTEND,          true,  false, true,  VK_LEFT,     0},
	{TEXT("SCI_WORDRIGHT"),               SCI_WORDRIGHT,               true,  false, false, VK_RIGHT,    0},
	{TEXT("SCI_WORDRIGHTEXTEND"),         SCI_WORDRIGHTEXTEND,         false, false, false, 0,           0},
	{TEXT("SCI_WORDLEFTEND"),             SCI_WORDLEFTEND,             false, false, false, 0,           0},
	{TEXT("SCI_WORDLEFTENDEXTEND"),       SCI_WORDLEFTENDEXTEND,       false, false, false, 0,           0},
	{TEXT("SCI_WORDRIGHTEND"),            SCI_WORDRIGHTEND,            false, false, false, 0,           0},
	{TEXT("SCI_WORDRIGHTENDEXTEND"),      SCI_WORDRIGHTENDEXTEND,      true,  false, true,  VK_RIGHT,    0},
	{TEXT("SCI_WORDPARTLEFT"),            SCI_WORDPARTLEFT,            true,  false, false, VK_OEM_2,    0},
	{TEXT("SCI_WORDPARTLEFTEXTEND"),      SCI_WORDPARTLEFTEXTEND,      true,  false, true,  VK_OEM_2,    0},
	{TEXT("SCI_WORDPARTRIGHT"),           SCI_WORDPARTRIGHT,           true,  false, false, VK_OEM_5,    0},
	{TEXT("SCI_WORDPARTRIGHTEXTEND"),     SCI_WORDPARTRIGHTEXTEND,     true,  false, true,  VK_OEM_5,    0},
	{TEXT("SCI_HOME"),                    SCI_HOME,                    false, false, false, 0,           0},
	{TEXT("SCI_HOMEEXTEND"),              SCI_HOMEEXTEND,              false, false, false, 0,           0},
	{TEXT("SCI_HOMERECTEXTEND"),          SCI_HOMERECTEXTEND,          false, false, false, 0,           0},
	{TEXT("SCI_HOMEDISPLAY"),             SCI_HOMEDISPLAY,             false, true,  false, VK_HOME,     0},
	{TEXT("SCI_HOMEDISPLAYEXTEND"),       SCI_HOMEDISPLAYEXTEND,       false, false, false, 0,           0},
	{TEXT("SCI_HOMEWRAP"),                SCI_HOMEWRAP,                false, false, false, 0,           0},
	{TEXT("SCI_HOMEWRAPEXTEND"),          SCI_HOMEWRAPEXTEND,          false, false, false, 0,           0},
	{TEXT("SCI_VCHOME"),                  SCI_VCHOME,                  false, false, false, 0,           0},
	{TEXT("SCI_VCHOMEWRAPEXTEND"),        SCI_VCHOMEWRAPEXTEND,        false, false, true,  VK_HOME,     0},
	{TEXT("SCI_VCHOMERECTEXTEND"),        SCI_VCHOMERECTEXTEND,        false, true,  true,  VK_HOME,     0},
	{TEXT("SCI_VCHOMEWRAP"),              SCI_VCHOMEWRAP,              false, false, false, VK_HOME,     0},
	{TEXT("SCI_VCHOMEWRAPEXTEND"),        SCI_VCHOMEWRAPEXTEND,        false, false, false, 0,           0},
	{TEXT("SCI_LINEEND"),                 SCI_LINEEND,                 false, false, false, 0,           0},
	{TEXT("SCI_LINEENDWRAPEXTEND"),       SCI_LINEENDWRAPEXTEND,       false, false, true,  VK_END,      0},
	{TEXT("SCI_LINEENDRECTEXTEND"),       SCI_LINEENDRECTEXTEND,       false, true,  true,  VK_END,      0},
	{TEXT("SCI_LINEENDDISPLAY"),          SCI_LINEENDDISPLAY,          false, true,  false, VK_END,      0},
	{TEXT("SCI_LINEENDDISPLAYEXTEND"),    SCI_LINEENDDISPLAYEXTEND,    false, false, false, 0,           0},
	{TEXT("SCI_LINEENDWRAP"),             SCI_LINEENDWRAP,             false, false, false, VK_END,      0},
	{TEXT("SCI_LINEENDEXTEND"),           SCI_LINEENDEXTEND,           false, false, false, 0,           0},
	{TEXT("SCI_DOCUMENTSTART"),           SCI_DOCUMENTSTART,           true,  false, false, VK_HOME,     0},
	{TEXT("SCI_DOCUMENTSTARTEXTEND"),     SCI_DOCUMENTSTARTEXTEND,     true,  false, true,  VK_HOME,     0},
	{TEXT("SCI_DOCUMENTEND"),             SCI_DOCUMENTEND,             true,  false, false, VK_END,      0},
	{TEXT("SCI_DOCUMENTENDEXTEND"),       SCI_DOCUMENTENDEXTEND,       true,  false, true,  VK_END,      0},
	{TEXT("SCI_PAGEUP"),                  SCI_PAGEUP,                  false, false, false, VK_PRIOR,    0},
	{TEXT("SCI_PAGEUPEXTEND"),            SCI_PAGEUPEXTEND,            false, false, true,  VK_PRIOR,    0},
	{TEXT("SCI_PAGEUPRECTEXTEND"),        SCI_PAGEUPRECTEXTEND,        false, true,  true,  VK_PRIOR,    0},
	{TEXT("SCI_PAGEDOWN"),                SCI_PAGEDOWN,                false, false, false, VK_NEXT,     0},
	{TEXT("SCI_PAGEDOWNEXTEND"),          SCI_PAGEDOWNEXTEND,          false, false, true,  VK_NEXT,     0},
	{TEXT("SCI_PAGEDOWNRECTEXTEND"),      SCI_PAGEDOWNRECTEXTEND,      false, true,  true,  VK_NEXT,     0},
	{TEXT("SCI_STUTTEREDPAGEUP"),         SCI_STUTTEREDPAGEUP,         false, false, false, 0,           0},
	{TEXT("SCI_STUTTEREDPAGEUPEXTEND"),   SCI_STUTTEREDPAGEUPEXTEND,   false, false, false, 0,           0},
	{TEXT("SCI_STUTTEREDPAGEDOWN"),       SCI_STUTTEREDPAGEDOWN,       false, false, false, 0,           0},
	{TEXT("SCI_STUTTEREDPAGEDOWNEXTEND"), SCI_STUTTEREDPAGEDOWNEXTEND, false, false, false, 0,           0},
	{TEXT("SCI_DELETEBACK"),              SCI_DELETEBACK,              false, false, false, VK_BACK,     0},
	{TEXT(""),                            SCI_DELETEBACK,              false, false, true,  VK_BACK,     0},
	{TEXT("SCI_DELETEBACKNOTLINE"),       SCI_DELETEBACKNOTLINE,       false, false, false, 0,           0},
	{TEXT("SCI_DELWORDLEFT"),             SCI_DELWORDLEFT,             true,  false, false, VK_BACK,     0},
	{TEXT("SCI_DELWORDRIGHT"),            SCI_DELWORDRIGHT,            true,  false, false, VK_DELETE,   0},
	{TEXT("SCI_DELLINELEFT"),             SCI_DELLINELEFT,             true,  false, true,  VK_BACK,     0},
	{TEXT("SCI_DELLINERIGHT"),            SCI_DELLINERIGHT,            true,  false, true,  VK_DELETE,   0},
	{TEXT("SCI_LINEDELETE"),              SCI_LINEDELETE,              true,  false, true,  VK_L,        0},
	{TEXT("SCI_LINECUT"),                 SCI_LINECUT,                 true,  false, false, VK_L,        0},
	{TEXT("SCI_LINECOPY"),                SCI_LINECOPY,                true,  false, true,  VK_X,        0},
	{TEXT("SCI_LINETRANSPOSE"),           SCI_LINETRANSPOSE,           true,  false, false, VK_T,        0},
	{TEXT("SCI_LINEDUPLICATE"),           SCI_LINEDUPLICATE,           false, false, false, 0,           0},
	{TEXT("SCI_CANCEL"),                  SCI_CANCEL,                  false, false, false, VK_ESCAPE,   0},
	{TEXT("SCI_SWAPMAINANCHORCARET"),     SCI_SWAPMAINANCHORCARET,     false, false, false, 0,           0},
	{TEXT("SCI_ROTATESELECTION"),         SCI_ROTATESELECTION,         false, false, false, 0,           0}
};

