#include "Redirect.h"
#include <TlHelp32.h>
/*!
 * @author           zhangyc-c
 * @brief            ��pSrc��ָ��ĺ����ض�����pDest
 * @param[in]        FARPROC pSrc
 * @param[in]        FARPROC pDest
 * @return           
 */
CRedirect::CRedirect(FARPROC pSrc, FARPROC pDest)
    : m_pSrc(pSrc)
{
    char szOldCode[8], szNewCode[8];
    //����ԭ������ڵľɴ���
    _asm   
    {   
        lea edi,szOldCode   
        mov esi,pSrc   
        cld   
        movsd   
        movsb   
    }
    szNewCode[0] = 0xE9;    //�൱��jmpָ��  
    //��ȡpSrc()����Ե�ַ  
    _asm   
    {   
        lea eax,pDest  
        mov ebx,pSrc   
        sub eax,ebx   
        sub eax,5   
        mov dword ptr [szNewCode+1],eax   
    }
    memcpy(m_szOldCode, szOldCode, sizeof(szOldCode));

    DWORD dwTemp=0;  
    DWORD dwOldProtect;  
    m_hProcess = GetCurrentProcess();
    //���ڴ汣��ģʽ��Ϊ��д,��ģʽ������dwOldProtect  
    VirtualProtectEx(m_hProcess, pSrc, 5, PAGE_READWRITE, &dwOldProtect);   
    //������������pSrc()��ǰ5���ֽڸ�ΪJmp pDest() 
    WriteProcessMemory(m_hProcess, pSrc, szNewCode, 5, 0);  
    //���ڴ汣��ģʽ�Ļ�ΪdwOldProtect  
    VirtualProtectEx(m_hProcess, pSrc, 5, dwOldProtect, &dwTemp);
}

CRedirect::~CRedirect()
{
    DWORD dwTemp = 0;  
    DWORD dwOldProtect;
    VirtualProtectEx(m_hProcess, m_pSrc, 5, PAGE_READWRITE, &dwOldProtect);   
    WriteProcessMemory(m_hProcess, m_pSrc, m_szOldCode, 5, 0);   
    VirtualProtectEx(m_hProcess, m_pSrc, 5, dwOldProtect, &dwTemp);   
}

/*!
 * @author           zhangyc-c
 * @brief            ���Һ�����ַ
 * @param[in]        HANDLE hProcess
 * @param[in]        LPCTSTR lpProcName
 * @param[in]        vector<pair<HMODULE, FARPROC> >
 * @param[in]        FARPROC> > & oResult
 * @return           void
 */
void CRedirect::findProcAddress(HANDLE hProcess, LPCSTR lpProcName, std::vector<std::pair<HMODULE, FARPROC> >& oResult)
{
    toDebugLevel(hProcess);
    DWORD dwPID = GetProcessId(hProcess);
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE32, dwPID);
    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        return;
    }
    MODULEENTRY32 me32;
    me32.dwSize = sizeof( MODULEENTRY32 );
    if (Module32First(hSnapshot, &me32))
    {
        do 
        {
            FARPROC pFunc = GetProcAddress(me32.hModule, lpProcName);
            if (pFunc)
            {
                oResult.push_back(std::pair<HMODULE, FARPROC>(me32.hModule, pFunc));
            }
        } while (Module32Next(hSnapshot, &me32));
    }
    CloseHandle(hSnapshot);
}

/*!
 * @author           zhangyc-c
 * @brief            �������̷���Ȩ��
 * @param[in]        HANDLE hProcess
 * @return           bool
 */
bool CRedirect::toDebugLevel(HANDLE hProcess)
{
    bool bResult = false;
    HANDLE hToken;
    TOKEN_PRIVILEGES oTP;
    if (OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken) &&
        LookupPrivilegeValue(NULL, L"SeDebugPrivilege", &oTP.Privileges[0].Luid))
    {
        oTP.PrivilegeCount = 1;
        oTP.Privileges[0].Attributes = SE_PRIVILEGE_USED_FOR_ACCESS | SE_PRIVILEGE_ENABLED;
        bResult = AdjustTokenPrivileges(hToken, false, &oTP, sizeof(oTP), NULL, NULL);
    }
    return bResult;
}

/*!
 * @author           zhangyc-c
 * @brief            ��һ���ӿ��ض�������һ���ӿ�
 * @param[in]        LPCTSTR lpSrcProcName      //����DLL����Ϊ����Ľӿڻᱻ�ض���
 * @param[in]        LPCTSTR lpDestProcName     //�ض��򵽵�ǰDLL������ӿ�
 * @return           void
 */
void CRedirect::redirect(LPCSTR lpSrcProcName, LPCSTR lpDestProcName)
{
    std::vector<std::pair<HMODULE, FARPROC> > oProcs;
    HANDLE hCurProcess = GetCurrentProcess();
    HMODULE hCurModule;
    if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (PCTSTR)&CRedirect::redirect, &hCurModule))
    {
        FARPROC pDestProc = GetProcAddress(hCurModule, lpDestProcName);
        findProcAddress(hCurProcess, lpSrcProcName, oProcs);
        for (size_t i = 0; i < oProcs.size(); ++i)
        {
            if (oProcs[i].first == hCurModule)
            {
                continue;
            }
            new CRedirect(oProcs[i].second, pDestProc); //newһ�����ͷžͲ��ỹԭ
        }
    }
}
