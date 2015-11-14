/*!
*@file Refptr.h
*@brief 图形平台内部提供的智能指针类，需要使用该智能指针的对象，必须从CReferenced中继承

* 该智能指针的与OSG中的智能指针行为相同。
*/
#pragma once

namespace ggp {
	/*!
	* @class CRefPtr
	* @brief 具有引用计数对象的智能指针
	*/
	template<class T>
	class CRefPtr
	{
	public:
		typedef T element_type;

		/*!
		*@brief 默认构造函数
		*/
		CRefPtr() : _ptr(0) {}

		/*!
		*@brief 输入为裸指针的构造函数
		*@param[in] ptr 具有引用技术对象的裸指针
		*/
		CRefPtr(T* ptr) : _ptr(ptr) { if (_ptr) _ptr->Ref(); }

		/*!
		*@brief 拷贝构造函数
		*@param[in] rp 引用对象引用
		*/
		CRefPtr(const CRefPtr& rp) : _ptr(rp._ptr) { if (_ptr) _ptr->Ref(); }

		/*!
		*@brief 带模版的拷贝构造函数
		*/
		template<class Other> CRefPtr(const CRefPtr<Other>& rp) : _ptr(rp._ptr) { if (_ptr) _ptr->Ref(); }

		/*!
		*@brief 析构函数
		*/
		~CRefPtr() { if (_ptr) _ptr->Unref();  _ptr = 0; }

		/*!
		*@brief 重载赋值符号
		*/
		CRefPtr& operator = (const CRefPtr& rp)
		{
			assign(rp);
			return *this;
		}

		/*!
		*@brief 重载赋值符号（带模版）
		*/
		template<class Other> CRefPtr& operator = (const CRefPtr<Other>& rp)
		{
			assign(rp);
			return *this;
		}

		/*!
		*@brief 重载赋值符号（裸指针赋给CRefPtr）
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
		*@brief 重载相等比较符号
		*/
		bool operator == (const CRefPtr& rp) const { return (_ptr == rp._ptr); }
		bool operator == (const T* ptr) const { return (_ptr == ptr); }
		friend bool operator == (const T* ptr, const CRefPtr& rp) { return (ptr == rp._ptr); }

		/*!
		*@brief 重载不等比较符号
		*/
		bool operator != (const CRefPtr& rp) const { return (_ptr != rp._ptr); }
		bool operator != (const T* ptr) const { return (_ptr != ptr); }
		friend bool operator != (const T* ptr, const CRefPtr& rp) { return (ptr != rp._ptr); }

		/*!
		*@brief 重载小于比较符号
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
		*@brief 重载取内容符号
		*/
		T& operator*() const { return *_ptr; }

		/*!
		*@brief 重载访问符号
		*/
		T* operator->() const { return _ptr; }

		/*!
		*@brief 获得裸指针
		*/
		T* get() const { return _ptr; }

		/*!
		*@brief 重载转换符号
		*/
		//operator T* () { return _ptr; }

		/*!
		*@brief 重载取反符号
		*/
		bool operator!() const { return _ptr == 0; } // not required

													 /*!
													 *@brief 判断指针是否有效
													 */
		bool valid() const { return _ptr != 0; }

		/*!
		*@brief 释放对象引用
		*/
		T* release() { T* tmp = _ptr; if (_ptr) _ptr->UnrefNoDelete(); _ptr = 0; return tmp; }

		/*!
		*@brief 交换内容
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

