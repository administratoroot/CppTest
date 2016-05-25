#pragma once
#include <Windows.h>
#include <vector>

class CRedirect
{
public:
    CRedirect(FARPROC pSrc, FARPROC pDest);
    ~CRedirect();
    static void findProcAddress(HANDLE hProcess, LPCSTR lpProcName, std::vector<std::pair<HMODULE, FARPROC> >& oResult);
    static bool toDebugLevel(HANDLE hProcess);
    static void redirect(LPCSTR lpSrcProcName, LPCSTR lpDestProcName);
private:
    FARPROC m_pSrc;
    char m_szOldCode[8];
    HANDLE m_hProcess;
};