#pragma once
#include <cmath>

namespace mathy {

	template<uint64_t num, uint64_t den = 1>
	struct angleMesurement {
		constexpr angleMesurement() = default;
		constexpr angleMesurement(const long double d) :angle(d) {}
		long double angle;

		template<uint64_t num2, uint64_t den2>
		constexpr explicit operator angleMesurement<num2, den2>() const{
			return angleMesurement<num2, den2>((angle*static_cast<double>(den*num2)) / static_cast<double>(num*den2));
		}
		constexpr uint64_t getFullRotations() const{
			return (uint64_t)angle*den / num;
		}
		constexpr angleMesurement<num, den> getTerminalAngle()const {
			return { angle - (getFullRotations()*(double)num / (double)den) };
		}
	};

	template<uint64_t num, uint64_t den>
	constexpr angleMesurement<num, den>&& operator+(const angleMesurement<num, den>& a, const angleMesurement<num, den>& b) {
		return angleMesurement<num, den>(a.angle + b.angle);
	}
	
	template<uint64_t num, uint64_t den, uint64_t num2, uint64_t den2>
	constexpr angleMesurement<num, den>&& operator+(const angleMesurement<num, den>& a, const angleMesurement<num2, den2>& b) {
		return angleMesurement<num, den>(a.angle + angleMesurement<num, den>(b).angle);
	}

	template<uint64_t num, uint64_t den>
	constexpr angleMesurement<num, den>&& operator-(const angleMesurement<num, den>& a, const angleMesurement<num, den>& b) {
		return angleMesurement<num, den>(a.angle - b.angle);
	}

	template<uint64_t num, uint64_t den, uint64_t num2, uint64_t den2>
	constexpr angleMesurement<num, den>&& operator-(const angleMesurement<num, den>& a, const angleMesurement<num2, den2>& b) {
		return angleMesurement<num, den>(a.angle - angleMesurement<num, den>(b).angle);
	}


	using degrees = angleMesurement<360>;
	using radians = angleMesurement<31415926535 * 2,10000000000>;

	constexpr degrees operator"" _deg(const long double a) {
		return degrees(a);
	}

	constexpr degrees operator"" _deg(const unsigned long long a) {
		return degrees((long double)a);
	}

	constexpr radians operator"" _rad(const long double a) {
		return radians(a);
	}

	constexpr radians operator"" _rad(const unsigned long long a) {
		return radians((long double)a);
	}

	//template<uint64_t num,uint64_t den>
	inline double cos(const radians angle) {
		return std::cos(angle.angle);
	}

	inline double sin(const radians angle) {
		return std::sin(angle.angle);
	}

	inline double tan(const radians angle) {
		return std::tan(angle.angle);
	}

	inline radians acos(const double d) {
		return radians(std::acos(d));
	}

	inline radians asin(const double d) {
		return radians(std::asin(d));
	}

	inline radians atan(const double d) {
		return radians(std::atan(d));
	}
	
	inline radians atan2(const double d1, const double d2) {
		return radians(std::atan2(d1, d2));
	}
	
	inline constexpr double ncos(const radians r) {
		const auto d = r.getTerminalAngle().angle;
		return 1 - (d*d / 2) + (d*d*d*d / 24) - (d*d*d*d*d*d / 720) + (d*d*d*d*d*d*d*d / 40320);
	}

	inline constexpr double nsin(const radians r) {
		const auto d = r.getTerminalAngle().angle;
		return d - (d*d*d / 6) + (d*d*d*d*d / 120) - (d*d*d*d*d*d*d / 5040) + (d*d*d*d*d*d*d*d*d / 362880);
	}
	inline constexpr double ntan(const radians r) {
		return nsin(r) / ncos(r);
	}

};