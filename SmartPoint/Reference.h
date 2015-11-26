/*!
*@file Reference.h
*@brief 引用计数实现类
*/

#pragma once

#include <cassert>
#include <set>

namespace ggp
{

    /*!
    *@class CReferenced
    *@brief 具有引用计数的实现类，需要引用计数的类，需要从此类继承

    * 该接口主要为了统一对象的引用计数操作，给出了默认的实现。
    */
    class  CReferenced
    {
    public:
        /*!
        *@brief 默认构造函数
        */
        CReferenced()
            : m_RefCount(0)//, m_pWeakPtrCounter(nullptr)
        {
        }

        /*!
        *@brief 拷贝构造函数
        */
        CReferenced(const CReferenced&)
            : m_RefCount(0)//, m_pWeakPtrCounter(nullptr)
        {
        }

        /*!
        *@brief 重载赋值符号
        *@return 当前对象的引用
        */
        CReferenced& operator = (const CReferenced&) { return *this; }

        /*!
        *@brief 增加引用计数，增加引用该对象的引用计数。
        *@see void Unref()
        */
        virtual void Ref()
        {
            _InterlockedIncrement(&m_RefCount);
        }

        /*!
        *@brief 减少引用计数，当引用计数的数目为零时，引用对象将被自动删除。
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
        *@brief 减少对象的引用计数，但不执行删除操作
        *@remark 调用者需要清除的知道谁负责该引用对象的删除，否则会造成内存泄露。
        */
        void UnrefNoDelete() const { --m_RefCount; }

        /*!
        *@brief 获得对象被引用的数目。
        *@return 引用计数个数
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

