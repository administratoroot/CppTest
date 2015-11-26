#include "GMutex.h"
#include <windows.h>

namespace ggp
{

// CMutex

CMutex::CMutex()
{
    hMutex = ::CreateMutex(NULL, FALSE, NULL);
}

CMutex::~CMutex()
{
    ::CloseHandle(hMutex);
}

void CMutex::Lock()
{
    ::WaitForSingleObject(hMutex, INFINITE);
}

void CMutex::Unlock()
{
    ::ReleaseMutex(hMutex);
}

// CLock

CLock::CLock(CMutex& mutex) : m_mutex(mutex)
{
    m_mutex.Lock();
}

CLock::~CLock()
{
    m_mutex.Unlock();
}

}