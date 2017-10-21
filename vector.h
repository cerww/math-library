#pragma once
#include <array>
#include <type_traits>

namespace mathy{
template<typename vectorType>
decltype(auto) dot(const vectorType l, const vectorType r);

template<typename T,int rows,int columns>
struct matrix;

template<typename _T,size_t N>
struct vector{
public:
	using type = _T;
	static constexpr size_t size = N;
	vector() = default;
	template<typename ...args>
	vector(args... Args):m_items{{std::forward<args>(Args)...}}{	}
	_T& operator[](size_t i){
		return m_items[i];
	}
	const _T& operator[](size_t i) const{
		return m_items[i];
	}vector& operator+(vector<_T,N> other){
		for (size_t i = o; i < N; ++i) 
			m_items[i] += other.m_items[i];
		return *this;
	}vector& operator-(vector<_T, N> other) {
		for (size_t i = o; i < N; ++i) 
			m_items[i] -= other.m_items[i];
		return *this;
	}vector& operator*(int64_t m) {
		for (size_t i = o; i < N; ++i) 
			m_items[i] *= m;
		return *this;
	}vector& operator/(int64_t m) {
		for (size_t i = o; i < N; ++i) 
			m_items[i] /= m;
		return *this;
	}vector& fill(_T item){
		for (size_t i = 0; i < N; ++i)
			m_items[i] = item;
		return *this;
	}
	template<typename T2>
	operator vector<T2,N>(){
		vector<T2, n> retVal;
		for (int i = 0; i < N; ++i)
			retVal[i] = m_items[i];
		return retVal;
	}
	decltype(auto) magnitude()const{
		return sqrt(dot(*this, *this));
	}
	//template<typename T,size_t rows,size_t columns>
	
	
private:
	std::array<_T, N> m_items;
};
namespace detail{
	template<typename vectorType,size_t... i>
	decltype(auto) dot_impl(const vectorType l, const vectorType r,std::index_sequence<i...>){
		//size_t retVal = 0;
		decltype(l[i] * r[i]) retVal = {};
		(void)(std::initializer_list<int>{(retVal += l[i] * r[i], 0)...});
		return retVal;
	}
};//detail
template<typename vectorType>
decltype(auto) dot(const vectorType l,const vectorType r){
	return detail::dot_impl(l, r, std::make_index_sequence<vectorType::size>);
};
template<typename T>
vector<T,3> cross(vector<T,3> first,vector<T,3> second){
	return { {first[1] * second[2] - first[2] * second[1],
			  first[2] * second[0] - first[0] * second[2],
			  first[0] * second[1] - first[1] * second[0]} };
}

};