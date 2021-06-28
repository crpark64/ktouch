// KTouch.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include "PathUtilFn.h"
#include "StringUtil.h"

#pragma warning(disable : 4996)

int wmain( int argc, wchar_t *argv[ ], wchar_t *envp[ ] )
{
    LPCWSTR lpszCommandLine = GetCommandLineW();
    wprintf(L"[INFO] Command Line: %s \r\n", lpszCommandLine);

    CString msg;
    CString output;

    do
    {
		BOOL bParsed = CStringUtil::CommandLineExcludeFirstArg( output );
		if ( FALSE == bParsed )
		{
			wprintf( L"[ERROR] Command Line Parse Failed. \r\n" );
            break;
		}

        wprintf(L"[INFO] Parsed Result: %s \r\n", output);
        wprintf(L"[INFO] Try Create File: %s \r\n", output);

        BOOL bExist = PathFileExists(output);
        if ( TRUE == bExist )
        {
            wprintf(L"[ERROR] File Already Exists. (FileName: %s) \r\n", output);
            break;
        }

        FILE *fp = _wfopen(output, L"at+");
        if ( NULL == fp )
        {
            wprintf(L"[ERROR] File Create Failed. (FileName: %s, ErrorNo: %d, ErrorText: %s) \r\n", output, errno, _wcserror(errno));
            break;
        }
        fclose(fp);

        wprintf(L"[ERROR] File Create Ok. (FileName: %s) \r\n", output);

    } while ( FALSE );

    return 0;
}
