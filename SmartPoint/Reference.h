/*!
*@file Reference.h
*@brief ���ü���ʵ����
*/

#pragma once

#include <cassert>
#include <set>

namespace ggp
{

    /*!
    *@class CReferenced
    *@brief �������ü�����ʵ���࣬��Ҫ���ü������࣬��Ҫ�Ӵ���̳�

    * �ýӿ���ҪΪ��ͳһ��������ü���������������Ĭ�ϵ�ʵ�֡�
    */
    class  CReferenced
    {
    public:
        /*!
        *@brief Ĭ�Ϲ��캯��
        */
        CReferenced()
            : m_RefCount(0)//, m_pWeakPtrCounter(nullptr)
        {
        }

        /*!
        *@brief �������캯��
        */
        CReferenced(const CReferenced&)
            : m_RefCount(0)//, m_pWeakPtrCounter(nullptr)
        {
        }

        /*!
        *@brief ���ظ�ֵ����
        *@return ��ǰ���������
        */
        CReferenced& operator = (const CReferenced&) { return *this; }

        /*!
        *@brief �������ü������������øö�������ü�����
        *@see void Unref()
        */
        virtual void Ref()
        {
            _InterlockedIncrement(&m_RefCount);
        }

        /*!
        *@brief �������ü����������ü�������ĿΪ��ʱ�����ö��󽫱��Զ�ɾ����
        *@see void Ref()
        */
        virtual void Unref()
        {
            //bool needDelete = (--m_RefCount == 0);
            bool needDelete = _InterlockedDecrement(&m_RefCount) == 0;

            if (needDelete)
            {
                SignalAndDelete(true, true);
            }
        }

        void SignalAndDelete(bool bSignalDelete, bool bDoDelete);

        /*!
        *@brief ���ٶ�������ü���������ִ��ɾ������
        *@remark ��������Ҫ�����֪��˭��������ö����ɾ�������������ڴ�й¶��
        */
        void UnrefNoDelete() const { --m_RefCount; }

        /*!
        *@brief ��ö������õ���Ŀ��
        *@return ���ü�������
        */
        int ReferenceCount() const { return m_RefCount; }

        //CWeakPtrCounter* GetOrCreateWeakPtrCounter() const;

        // IntrusivePtrAddRef and intrusive_ptr_release allow
        // use of osg Referenced classes with boost::intrusive_ptr
        void IntrusivePtrAddRef(CReferenced* p) { p->Ref(); }
        void IntrusivePtrRelease(CReferenced* p) { p->Unref(); }

    protected:
        virtual ~CReferenced();

        mutable long             m_RefCount;
        //mutable void*           m_pWeakPtrCounter;
    };
}

