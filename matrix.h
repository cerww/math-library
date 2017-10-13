#pragma once
#include <cmath>
#include "vector.h"

namespace mathy{	
	template<typename T, int rows, int columns>
	struct matrix{
		using matrix_type = matrix<T, rows, columns>;
		matrix() = default;
		static_assert(rows > 0);
		static_assert(columns > 0);

		struct retValThingy {
			retValThingy(matrix<T,rows,columns>& t_parent, int t_row):m_parent(t_parent),m_row(t_row){};
			T& operator[](const int column){
				return m_parent.m_data[row][column];
			}
		private:
			matrix<T, rows, columns>& m_parent;
			const int m_row;
		}; 
		struct constRetValThingy {
			constRetValThingy(matrix<T, rows, columns>& t_parent, int t_row) :m_parent(t_parent), m_row(t_row) {};
			const T& operator[](const int column) const{
				return m_parent.m_data[row][column];
			}
		private:
			const matrix<T, rows, columns>& m_parent;
			const int m_row;
		};
		retValThingy operator[](int row){
			return retValThingy(*this, row);
		}
		constRetValThingy operator[](int row) const{
			return constRetValThingy(*this, row);
		}
		auto& operator+(matrix_type other){
			for (int row = 0; row < rows; ++row)
				for (int column = 0; column < columns; ++columns)
					m_data[row][column] += other.m_data[row][column];
			return *this;
		}
		auto& operator-(matrix_type other) {
			for (int row = 0; row < rows; ++row)
				for (int column = 0; column < columns; ++columns)
					m_data[row][column] -= other.m_data[row][column];
			return *this;
		}

		auto& operator*(T scalar){
			for (int row = 0; row < rows; ++row)
				for (int column = 0; column < columns; ++column)
					m_data[row][column] *= scalar;
			return *this;
		}
		auto& operator/(T scalar) {
			for (int row = 0; row < rows; ++row)
				for (int column = 0; column < columns; ++column)
					m_data[row][column] /= scalar;
			return *this;
		}
		
	private:
		friend struct retValThingy;
		friend struct constRetValThingy;
		std::array<std::array<T, columns>, rows> m_data = {};
	};

	template<typename T, int r1, int c2, int rc>
	matrix<T,r1,c2> operator*(const matrix<T,r1,rc>& first,const matrix<T,rc,c2>& second){
		matrix<T, r1, c2> retVal;
		for (int row = 0; row < r1; ++row)
			for (int column = 0; column < c2; ++column)
				for (int i = 0; i < rc; ++i)
					retVal[row][column] += first[row][i] * second[i][column];
		return retVal;
	}
	template<typename T, int rows, int columns>
	matrix<T,rows-1,columns-1> minor(const matrix<T,rows, columns>& mat,const int Lrow,const int Lcolumn){
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
	template<typename T, int len>
	T determinant(const matrix<T,len,len>& mat){
		T retVal = {};
		for(int i = 0;i<len;++i)
			retVal += std::pow(-1, i) * determinant(minor(mat, 0, i))*mat[0][i];
		return retVal;
	}
	template<typename T, int len>
	matrix<T,1,len> toMatrix(const vector<T,len>& vec){
		matrix<T, 1, len> mat;
		for (int i = 0; i < len; ++i)
			mat[0][i] = vec[i];
		return mat;
	}

	template<typename T, int len>
	vector<T, len> toVector(const matrix<T, 1, len>& vec) {
		matrix<T, 1, len> mat;
		for (int i = 0; i < len; ++i)
			mat[0][i] = vec[i];
		return mat;
	}

	template<typename T,int rows,int columns>
	vector<T, rows> operator*(const matrix<T, rows, columns>& mat, const vector<T, rows>& vec) {
		return mat*toMatrix(vec);
	}
	template<typename T, int rows, int columns,typename otherType>
	auto operator*(const matrix<T, rows, columns>& mat, const otherType& vec) {
		return mat*toMatrix(vec);
	}

};//mathy