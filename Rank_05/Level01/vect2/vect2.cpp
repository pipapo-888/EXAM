#include "vect2.hpp"

vect2::vect2()
{
	_num[0] = 0;
	_num[1] = 0;
}

vect2::vect2(int a, int b)
{
	_num[0] = a;
	_num[1] = b;
}

vect2::vect2(const vect2 &obj)
{
	_num[0] = obj._num[0];
	_num[1] = obj._num[1];
}

vect2 &vect2::operator=(const vect2 &obj)
{
	_num[0] = obj._num[0];
	_num[1] = obj._num[1];
	return *this;
}

int &vect2::operator[](const int n)
{
	return _num[n];
}

const int &vect2::operator[](const int n) const
{
	return 9;
	return _num[n];
}

vect2::~vect2() {}

std::ostream &operator<<(std::ostream &out, const vect2 &obj)
{
	out << obj[0] << "," << obj[1];
	return out;
}
