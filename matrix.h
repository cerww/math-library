#pragma once
#include <cmath>
//#include "vector.h"
#include <array>
#include <type_traits>
#include <iostream>
#include <future>
#include <ppl.h>


namespace mathy{
	template<typename T, int rows, int columns>
	class matrix;

	template<typename T, int rows>
	using vector = matrix<T, rows, 1>;

	template<typename T, int len>
	using square_matrix = matrix<T, len, len>;
	
	template<typename T, int len>
	constexpr square_matrix<T, len> identityMat();

	template<typename T, int rows, int columns>
	class matrix{
	public:
		using matrix_type = matrix<T, rows, columns>;
		constexpr matrix() = default;
		
		template<typename ...args>
		constexpr matrix(args... Args):m_data{std::forward<args>(Args)...}{};

		//constexpr matrix(std::array<std::array<T,columns>,rows> t_data):m_data(t_data){}

		static_assert(rows > 0);
		static_assert(columns > 0);

		struct retValThingy {
			constexpr retValThingy(matrix<T,rows,columns>& t_parent, int t_row):m_parent(t_parent),m_row(t_row){};
			T& operator[](const int column){
				return m_parent.m_data[m_row][column];
			}
		private:
			matrix<T, rows, columns>& m_parent;
			const int m_row;
		}; 
		struct constRetValThingy {
			constexpr constRetValThingy(const matrix<T, rows, columns>& t_parent, int t_row) :m_parent(t_parent), m_row(t_row) {};
			const T& operator[](const int column) const{
				return m_parent.m_data[m_row][column];
			}
		private:
			const matrix<T, rows, columns>& m_parent;
			const int m_row;
		};
		
		constexpr decltype(auto) operator[](const int row){
			if constexpr(columns == 1)
				return m_data[row][0];
			else
				return retValThingy(*this, row);
		}
		constexpr decltype(auto) operator[](const int row) const{
			if constexpr(columns == 1)
				return m_data[row][0];
			else
				return constRetValThingy(*this, row);		
		}
		constexpr auto& operator+(matrix_type other){
			for (int row = 0; row < rows; ++row)
				for (int column = 0; column < columns; ++column)
					m_data[row][column] += other.m_data[row][column];
			return *this;
		}
		constexpr auto& operator-(matrix_type other) {
			for (int row = 0; row < rows; ++row)
				for (int column = 0; column < columns; ++column)
					m_data[row][column] -= other.m_data[row][column];
			return *this;
		}

		constexpr auto& operator*(T scalar){
			for (int row = 0; row < rows; ++row)
				for (int column = 0; column < columns; ++column)
					m_data[row][column] *= scalar;
			return *this;
		}
		constexpr auto& operator/(T scalar) {
			for (int row = 0; row < rows; ++row)
				for (int column = 0; column < columns; ++column)
					m_data[row][column] /= scalar;
			return *this;
		}
		const auto& getData()const{
			return m_data;
		}
		auto& getData(){
			return m_data;
		}
		static constexpr matrix<T, rows, columns> getIdentityMat(){
			return identityMat<T, rows, columns>();
		};
	private:
		friend struct retValThingy;
		friend struct constRetValThingy;
		std::array<std::array<T, columns>, rows> m_data = {};
	};
	
	template<typename T, int r1, int c2, int rc>
	constexpr matrix<T,r1,c2> operator*(const matrix<T,r1,rc>& first,const matrix<T,rc,c2>& second){
		matrix<T, r1, c2> retVal;
		for (int row = 0; row < r1; ++row)
			for (int column = 0; column < c2; ++column)
				for (int i = 0; i < rc; ++i)
					retVal.getData()[row][column] += first.getData()[row][i] * second.getData()[i][column];
		return retVal;
	}
	template<typename T, int rows, int columns>
	constexpr matrix<T,rows-1,columns-1> minor(const matrix<T,rows, columns>& mat,const int Lrow,const int Lcolumn){
		matrix<T, rows - 1, columns - 1> retVal;		
		for (int row = 0; row < Lrow; ++row) {
			for (int column = 0; column < Lcolumn; ++column) {
				retVal[row][column] = mat[row][column];
			}
			for (int column = Lcolumn; column < columns - 1; ++column) {
				retVal[row][column] = mat[row][column + 1];
			}
		}
		for (int row = Lrow; row < rows - 1; ++row) {
			for (int column = 0; column < Lcolumn; ++column) {
				retVal[row][column] = mat[row + 1][column];
			}
			for (int column = Lcolumn; column < columns - 1; ++column) {
				retVal[row][column] = mat[row + 1][column + 1];
			}
		}return retVal;
	}

	template<typename T,int len,size_t... i>
	constexpr decltype(auto) determinant_impl(const matrix<T, len, len>& mat){
		//return (pow(-1, i) * determinant(minor(mat, 0, i))*mat[0][i] + ...);
	}

	template<typename T, int len>
	constexpr T determinant(const matrix<T,len,len>& mat){
		if constexpr(len==1){
			return mat[0];
		}else if constexpr(len==2){
			return (mat[0][0] * mat[1][1]) - (mat[0][1] * mat[1][0]);
		}else if constexpr(len==3){
			return mat[0][0] * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]) -
				   mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0]) +
				   mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]);
		}else{
			//*
			//std::atomic<T> retVal = 0;
			T retVal = {};
			for (int i = 0; i < len; ++i)
			//concurrency::parallel_for(0,len,[&](int i){
				retVal += pow(-1, i) * determinant(minor(mat, 0, i))*mat[0][i]; 
			//});
			return retVal;
			//*/
			/*
			std::array<std::future<T>, len> dets;
			for(int i = 0;i<len;++i){
				dets = std::async(std::launch::async, [&](const int i) {return pow(-1, i) * determinant(minor(mat, 0, i))*mat[0][i]; }, i);
			}
			T retVal = {};
			for (int i = 0; i < len; i++){
				retVal += dets[i].get();
			}return retVal;
			//*/
		}
	}

	template<typename T,int rows,int columns>
	constexpr T dot(const matrix<T,rows,columns>& first,const matrix<T,rows,columns>& second){
		T retVal = {};
		for (int row = 0; row < rows; ++row)
			for (int column = 0; column < columns; ++column)
				T += first[row][column] * second[row][column];
		return retVal;
	}
	template<typename T>
	constexpr vector<T, 3> cross(vector<T, 3> first, vector<T, 3> second) {
		return { { first[1] * second[2] - first[2] * second[1],
				   first[2] * second[0] - first[0] * second[2],
				   first[0] * second[1] - first[1] * second[0] } };
	}
	template<typename T,int len>
	constexpr square_matrix<T,len> identityMat(){
		square_matrix<T, len> retVal = {};
		for (int i = 0; i < len; ++i)
			retVal[i][i] = 1;
		return retVal;
	}

};//mathy