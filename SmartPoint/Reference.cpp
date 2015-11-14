#include "Reference.h"

using namespace ggp;

//CWeakPtrCounter* ggp::CReferenced::GetOrCreateWeakPtrCounter() const
//{
//    if (!m_pWeakPtrCounter)
//    {
//        m_pWeakPtrCounter = new CWeakPtrCounter(this);
//        static_cast<CWeakPtrCounter*>(m_pWeakPtrCounter)->Ref();
//    }
//    return static_cast<CWeakPtrCounter*>(m_pWeakPtrCounter);
//}

ggp::CReferenced::~CReferenced()
{
    assert(m_RefCount==0); 

    SignalAndDelete(true, false);

    //if (m_pWeakPtrCounter != nullptr) 
    //{
    //    static_cast<CWeakPtrCounter*>(m_pWeakPtrCounter)->Unref();
    //}
}

void ggp::CReferenced::SignalAndDelete( bool bSignalDelete, bool bDoDelete )
{
    //CWeakPtrCounter* pWeakPtrCounter = static_cast<CWeakPtrCounter*>(m_pWeakPtrCounter);

    //if (pWeakPtrCounter && bSignalDelete)
    //{
    //    pWeakPtrCounter->SignalObjectDeleted(const_cast<CReferenced*>(this));
    //}

    if (bDoDelete)
    {
        delete this;
    }
}

//void ggp::CWeakPtrCounter::SignalObjectDeleted( void* ptr )
//{
//    CLock lock(m_mutex);
//    m_pObservedObject = nullptr;
//}
