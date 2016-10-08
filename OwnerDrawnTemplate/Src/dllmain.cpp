
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
#include <stdio.h>
#include <stdarg.h>

#include "PluginInterface.h"

#include "OwnerDrawnTemplate.h"


extern NppData nppData;

HANDLE g_hModule = NULL;
bool bIsNppReady = false;

const TCHAR NPP_PLUGIN_NAME[] = TEXT("OwnerDrawnTemplate");

FuncItem funcItem[] = {
	{TEXT("Toggle"), ToggleDlg, 0, false, NULL},
	{TEXT("About"), AboutDlg, 0, false, NULL},
};

/* for subclassing */
WNDPROC	wndProcNotepad = NULL;

void pluginInit(HANDLE hModule);
void pluginCleanUp();
void commandMenuCleanUp();


void DebugLog(const char* format, ... )  // output goes to Debugger 'Output' window
{
	static char Buffer[4096];

	// use this like printf() with char* format strings (not WCHAR* format strings)

	va_list args;
	va_start(args, format);
	vsnprintf_s(Buffer, sizeof(Buffer), sizeof(Buffer)-1, format, args);
	strcat_s(Buffer, "\n");
	OutputDebugStringA(Buffer);
	va_end (args);
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	g_hModule = hModule;

	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			//DebugLog("DLL_PROCESS_ATTACH");
	        pluginInit(hModule);
			break;

		case DLL_PROCESS_DETACH:
			//DebugLog("DLL_PROCESS_DETACH");
	        pluginCleanUp();
			break;
	}
	return TRUE;
}


extern "C" __declspec(dllexport) BOOL isUnicode()
{
    return TRUE;
}

extern "C" __declspec(dllexport) void setInfo(NppData notpadPlusData)
{
	nppData = notpadPlusData;

	OwnerDrawnTemplate_MAIN.init(MAIN_VIEW);
	OwnerDrawnTemplate_SUB.init(SUB_VIEW);

	/* Subclassing for Notepad */
	wndProcNotepad = (WNDPROC)SetWindowLongPtr(nppData._nppHandle, GWLP_WNDPROC, (LPARAM)SubWndProcNotepad);
}

extern "C" __declspec(dllexport) const TCHAR * getName()
{
	return NPP_PLUGIN_NAME;
}

extern "C" __declspec(dllexport) FuncItem * getFuncsArray(int *nbF)
{
	*nbF = _countof(funcItem);
	return funcItem;
}

extern "C" __declspec(dllexport) void beNotified(SCNotification *notifyCode)
{
	if( notifyCode->nmhdr.code == NPPN_DOCORDERCHANGED )
	{
		UpdateDocs();
	}
	else if (notifyCode->nmhdr.hwndFrom == nppData._nppHandle)
	{
		switch (notifyCode->nmhdr.code) 
		{
			case NPPN_READY:  // To notify plugins that all the procedures of launchment of notepad++ are done.
			{
				bIsNppReady = true;
				UpdateDocs();
				break;
			}

			case NPPN_TBMODIFICATION:  // To notify plugins that toolbar icons can be registered
			{
				break;
			}

			case NPPN_BUFFERACTIVATED:  // To notify plugins that a buffer was activated (put to foreground)
			{
				UpdateDocs();
				break;
			}

			case NPPN_SHUTDOWN:  // To notify plugins that Notepad++ is about to be shutdowned.
			{
				commandMenuCleanUp();
				break;
			}

			default:
				break;
		}
	}
}

extern "C" __declspec(dllexport) LRESULT messageProc(UINT /*Message*/, WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	return TRUE;
}


void pluginInit(HANDLE hModule)
{
	g_hModule = hModule;
}

void pluginCleanUp()
{
}

void commandMenuCleanUp()
{
	// Don't forget to deallocate your shortcut(s) here
}
