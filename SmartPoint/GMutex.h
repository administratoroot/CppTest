/*!
*@file GMutex.h
*@brief 互斥锁与同步对象类
*/

#pragma once

#include "GNonCopyable.h"

namespace ggp {

#define GLOCK(a) CLock _tmpLock(a)

/*!
* @class CMutex
* @brief 互斥锁同步对象，用于简化线程同步代码。
*/
class CMutex : public CNonCopyable
{
public:
    CMutex();
    ~CMutex();

    //! @brief 锁定，支持嵌套调用
    void Lock();

    //! @brief 解锁
    void Unlock();

private:
    void * hMutex;
};

/*!
* @class CLock
* @brief 锁对象，利用C++对象生命周期特性简化加锁/解锁过程。
*/
class  CLock : public CNonCopyable
{
public:
    explicit CLock(CMutex& mutex);
    ~CLock();

private:
    CMutex& m_mutex;
};

}