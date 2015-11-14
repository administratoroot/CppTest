/*!
*@file Refptr.h
*@brief ͼ��ƽ̨�ڲ��ṩ������ָ���࣬��Ҫʹ�ø�����ָ��Ķ��󣬱����CReferenced�м̳�

* ������ָ�����OSG�е�����ָ����Ϊ��ͬ��
*/
#pragma once

namespace ggp {
	/*!
	* @class CRefPtr
	* @brief �������ü������������ָ��
	*/
	template<class T>
	class CRefPtr
	{
	public:
		typedef T element_type;

		/*!
		*@brief Ĭ�Ϲ��캯��
		*/
		CRefPtr() : _ptr(0) {}

		/*!
		*@brief ����Ϊ��ָ��Ĺ��캯��
		*@param[in] ptr �������ü����������ָ��
		*/
		CRefPtr(T* ptr) : _ptr(ptr) { if (_ptr) _ptr->Ref(); }

		/*!
		*@brief �������캯��
		*@param[in] rp ���ö�������
		*/
		CRefPtr(const CRefPtr& rp) : _ptr(rp._ptr) { if (_ptr) _ptr->Ref(); }

		/*!
		*@brief ��ģ��Ŀ������캯��
		*/
		template<class Other> CRefPtr(const CRefPtr<Other>& rp) : _ptr(rp._ptr) { if (_ptr) _ptr->Ref(); }

		/*!
		*@brief ��������
		*/
		~CRefPtr() { if (_ptr) _ptr->Unref();  _ptr = 0; }

		/*!
		*@brief ���ظ�ֵ����
		*/
		CRefPtr& operator = (const CRefPtr& rp)
		{
			assign(rp);
			return *this;
		}

		/*!
		*@brief ���ظ�ֵ���ţ���ģ�棩
		*/
		template<class Other> CRefPtr& operator = (const CRefPtr<Other>& rp)
		{
			assign(rp);
			return *this;
		}

		/*!
		*@brief ���ظ�ֵ���ţ���ָ�븳��CRefPtr��
		*/
		inline CRefPtr& operator = (T* ptr)
		{
			if (_ptr == ptr) return *this;
			T* tmp_ptr = _ptr;
			_ptr = ptr;
			if (_ptr) _ptr->Ref();
			// Unref second to prevent any deletion of any object which might
			// be referenced by the other object. i.e rp is child of the
			// original _ptr.
			if (tmp_ptr) tmp_ptr->Unref();
			return *this;
		}

		/*!
		*@brief ������ȱȽϷ���
		*/
		bool operator == (const CRefPtr& rp) const { return (_ptr == rp._ptr); }
		bool operator == (const T* ptr) const { return (_ptr == ptr); }
		friend bool operator == (const T* ptr, const CRefPtr& rp) { return (ptr == rp._ptr); }

		/*!
		*@brief ���ز��ȱȽϷ���
		*/
		bool operator != (const CRefPtr& rp) const { return (_ptr != rp._ptr); }
		bool operator != (const T* ptr) const { return (_ptr != ptr); }
		friend bool operator != (const T* ptr, const CRefPtr& rp) { return (ptr != rp._ptr); }

		/*!
		*@brief ����С�ڱȽϷ���
		*/
		bool operator < (const CRefPtr& rp) const { return (_ptr<rp._ptr); }


		// follows is an implmentation of the "safe bool idiom", details can be found at:
		//   http://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Safe_bool
		//   http://lists.boost.org/Archives/boost/2003/09/52856.php

	private:
		typedef T* CRefPtr::*unspecified_bool_type;

	public:
		// safe bool conversion
		operator unspecified_bool_type() const { return valid() ? &CRefPtr::_ptr : 0; }

		/*!
		*@brief ����ȡ���ݷ���
		*/
		T& operator*() const { return *_ptr; }

		/*!
		*@brief ���ط��ʷ���
		*/
		T* operator->() const { return _ptr; }

		/*!
		*@brief �����ָ��
		*/
		T* get() const { return _ptr; }

		/*!
		*@brief ����ת������
		*/
		//operator T* () { return _ptr; }

		/*!
		*@brief ����ȡ������
		*/
		bool operator!() const { return _ptr == 0; } // not required

													 /*!
													 *@brief �ж�ָ���Ƿ���Ч
													 */
		bool valid() const { return _ptr != 0; }

		/*!
		*@brief �ͷŶ�������
		*/
		T* release() { T* tmp = _ptr; if (_ptr) _ptr->UnrefNoDelete(); _ptr = 0; return tmp; }

		/*!
		*@brief ��������
		*/
		void swap(CRefPtr& rp) { T* tmp = _ptr; _ptr = rp._ptr; rp._ptr = tmp; }

	private:

		template<class Other> void assign(const CRefPtr<Other>& rp)
		{
			if (_ptr == rp._ptr) return;
			T* tmp_ptr = _ptr;
			_ptr = rp._ptr;
			if (_ptr) _ptr->Ref();
			// Unref second to prevent any deletion of any object which might
			// be referenced by the other object. i.e rp is child of the
			// original _ptr.
			if (tmp_ptr) tmp_ptr->Unref();
		}

		template<class Other> friend class CRefPtr;

		T* _ptr;
	};


	template<class T> inline
		void swap(CRefPtr<T>& rp1, CRefPtr<T>& rp2) { rp1.swap(rp2); }

	template<class T> inline
		T* get_pointer(const CRefPtr<T>& rp) { return rp.get(); }

	template<class T, class Y> inline
		CRefPtr<T> static_pointer_cast(const CRefPtr<Y>& rp) { return static_cast<T*>(rp.get()); }

	template<class T, class Y> inline
		CRefPtr<T> dynamic_pointer_cast(const CRefPtr<Y>& rp) { return dynamic_cast<T*>(rp.get()); }

	template<class T, class Y> inline
		CRefPtr<T> const_pointer_cast(const CRefPtr<Y>& rp) { return const_cast<T*>(rp.get()); }
}

