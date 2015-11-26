/*!
*@file GMutex.h
*@brief ��������ͬ��������
*/

#pragma once

#include "GNonCopyable.h"

namespace ggp {

#define GLOCK(a) CLock _tmpLock(a)

/*!
* @class CMutex
* @brief ������ͬ���������ڼ��߳�ͬ�����롣
*/
class CMutex : public CNonCopyable
{
public:
    CMutex();
    ~CMutex();

    //! @brief ������֧��Ƕ�׵���
    void Lock();

    //! @brief ����
    void Unlock();

private:
    void * hMutex;
};

/*!
* @class CLock
* @brief ����������C++���������������Լ򻯼���/�������̡�
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