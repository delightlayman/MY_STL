#pragma once
#include "MY_STL.h"

namespace MY_STL{
	template<class T,class compare=less<T>>
	class m_set {
		public:
			using Self = m_set<T, compare>;
			using key_type = T;
			using value_type = T;//值存储类型
			using set_key = key_identity<T>;

			using rbtree = RBTree_base<key_type, value_type, set_key, compare>;
			//iterator类型依赖rbtree模板参数的确定而确定---依赖类型，需要加typename告诉编译器其为类型，而非变量
			using iterator = typename rbtree::iterator;
			using const_iterator = typename rbtree::const_iterator;
			iterator begin() {
				return _rb.begin();
			}
			const_iterator begin()const{
				return _rb.begin();//实际调用const版本
			}
			iterator end() {
				return _rb.end();
			}
			const iterator end()const {
				return _rb.end();//实际调用const版本
			}
			//dafult constructor
			m_set(){}
			//consttructor
			template<class InputIterator>
			m_set(InputIterator first, InputIterator last) {
				_rb.insert(first, last);
			}
			//copy consttructor
			m_set(const Self& set) {
				rbtree tmp(set._rb);
				_rb.swap(tmp);
			}
			//operator=
			Self& operator=(Self set) {//此处set为副本
					_rb.swap(set._rb);//原数据释放交给副本set
				return *this;
			}
			//destructor
			~m_set() {}
			//add
			m_pair<iterator, bool> insert(const value_type& t) {
				return _rb.insert(t);
			}
			template<class InputIterator>
			void insert(InputIterator first, InputIterator last) {
				_rb.insert(first, last);
			}
			//delete
			bool erase(const key_type& k) {
				return _rb.erase(k);
			}
			//query
			iterator find(const key_type& k) {
				return _rb.find(k);
			}
			const_iterator find(const key_type& k)const {
				return _rb.find(k);//实际调用其const版本
			}
			//modify

		private:
			rbtree _rb;
	};
}