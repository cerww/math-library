#pragma once
namespace mathy{
template<int mass=0,int time=0,int moles=0,int displacement=0,int temperature=0, int current=0,int candela=0>
class si_unit {
public:
	double n = 0;
};
template<
int mass1, int time1, int moles1, int displacement1, int temperature1, int current1, int candela1,
int mass2, int time2, int moles2, int displacement2, int temperature2, int current2, int candela2>
constexpr inline si_unit<mass1 + mass2, time1 + time2, moles1 + moles2, displacement1 + displacement2, temperature1 + temperature2, current1 + current2, candela1 + candela2>
operator*(
	si_unit<mass1, time1, moles1, displacement1, temperature1, current1, candela1> first,
	si_unit<mass2, time2, moles2, displacement2, temperature2, current2, candela2> second
	){
	return { first.n*second.n };
}

template<
int mass1, int time1, int moles1, int displacement1, int temperature1, int current1, int candela1,
int mass2, int time2, int moles2, int displacement2, int temperature2, int current2, int candela2>
constexpr inline si_unit<mass1 + mass2, time1 + time2, moles1 + moles2, displacement1 + displacement2, temperature1 + temperature2, current1 + current2, candela1 + candela2>
operator/(
	si_unit<mass1, time1, moles1, displacement1, temperature1, current1, candela1> first,
	si_unit<mass2, time2, moles2, displacement2, temperature2, current2, candela2> second
	) {
return { first.n/second.n };
}
template<int mass1, int time1, int moles1, int displacement1, int temperature1, int current1, int candela1>
constexpr inline si_unit<mass1, time1, moles1, displacement1, temperature1, current1, candela1> operator+(
	si_unit<mass1, time1, moles1, displacement1, temperature1, current1, candela1> first, 
	si_unit<mass1, time1, moles1, displacement1, temperature1, current1, candela1> second){
	return { first.n + second.n };
}
template<int mass1, int time1, int moles1, int displacement1, int temperature1, int current1, int candela1>
constexpr inline si_unit<mass1, time1, moles1, displacement1, temperature1, current1, candela1> operator-(
	si_unit<mass1, time1, moles1, displacement1, temperature1, current1, candela1> first,
	si_unit<mass1, time1, moles1, displacement1, temperature1, current1, candela1> second) {
	return { first.n - second.n };
}
using newton = si_unit<1, -2, 0, 1, 0, 0, 0>;
using momentum = si_unit<1, -1, 0, 1, 0, 0, 0>;
using joule = si_unit<1, -2, 0, 2, 0, 0, 0>;
using watt = si_unit<1, -3, 0, 2, 0, 0, 0>;

};//mathy