#pragma once
#include "mathStuff.h"

namespace mathy {
	template<typename T>
	struct complex_;

	complex_<double> unitNum(radians);

	template<typename T>
	struct complex_{
		constexpr complex_() = default;
		T rl;
		T im;
		radians angle()const{
			return atan2(im, rl);
		}complex_<T>& operator*(complex_<T> other){
			rl = other.rl*rl - im*other.im;
			im = rl*other.im + im*other.rl;
			return *this;
		}
	};
	inline complex_<double> unitNum(radians angle) {
		return complex_<double>{cos(angle), sin(angle)};
	}
};
