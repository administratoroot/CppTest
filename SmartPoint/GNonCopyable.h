#ifndef G_NON_COPYABLE_H
#define G_NON_COPYABLE_H

#ifdef _MSC_VER
#pragma warning(disable: 4275)
#endif

namespace ggp
{

/*!
* @class CNonCopyable
* @brief ���ɸ��ƶ������ڽ�ֹ����Ŀ��������븳ֵ������ɴӸ���̳м����Զ�������ϱ�֤��
*/
class CNonCopyable
{
protected:
    CNonCopyable(void) {}
    ~CNonCopyable(void) {}

private:
    CNonCopyable(const CNonCopyable&);
    CNonCopyable& operator=(const CNonCopyable&);
};

}

#endif