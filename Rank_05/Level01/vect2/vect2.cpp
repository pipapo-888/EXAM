#include "vect2.hpp"

vect2::vect2() {
	_num[0] = 0;
	_num[1] = 0;
}

vect2::vect2(int a, int b) {
	_num[0] = a;
	_num[1] = b;
}

vect2::vect2(const vect2 &obj) {
	_num[0] = obj._num[0];
	_num[1] = obj._num[1];
}

vect2 &vect2::operator=(const vect2 &obj) {
	_num[0] = obj._num[0];
	_num[1] = obj._num[1];
	return *this;
}

vect2 &vect2::operator+=(const vect2 &obj) {
	_num[0] += obj._num[0];
	_num[1] += obj._num[1];
	return *this;
}

vect2 &vect2::operator-=(const vect2 &obj) {
	_num[0] -= obj._num[0];
	_num[1] -= obj._num[1];
	return *this;
}

vect2 &vect2::operator*=(const vect2 &obj) {
	_num[0] *= obj._num[0];
	_num[1] *= obj._num[1];
	return *this;
}

vect2 &vect2::operator*=(const int n) {
	_num[0] *= n;
	_num[1] *= n;
	return *this;
}

vect2 vect2::operator+(const vect2 &obj) const {
	vect2 tmp(*this);
	tmp += obj;
	return tmp;
}

vect2 vect2::operator-(const vect2 &obj) const {
	vect2 tmp(*this);
	tmp -= obj;
	return tmp;
}

vect2 vect2::operator*(const vect2 &obj) const {
	vect2 tmp(*this);
	tmp *= obj;
	return tmp;
}

vect2 vect2::operator*(const int n) const {
	vect2 tmp(*this);
	tmp *= n;
	return tmp;
}

vect2 vect2::operator-() const {
	vect2 tmp(*this);
	tmp[0] = -tmp[0];
	tmp[1] = -tmp[1];
	return tmp;
}

bool vect2::operator==(const vect2 &obj) const {
	if (_num[0] == obj._num[0] && _num[1] == obj._num[1])
		return true;
	return false;
}

bool vect2::operator!=(const vect2 &obj) const { return !(*this == obj); }

int &vect2::operator[](const int n) { return _num[n]; }

const int &vect2::operator[](const int n) const { return _num[n]; }

vect2 vect2::operator++(int) {
	vect2 tmp(*this);
	_num[0]++;
	_num[1]++;
	return tmp;
}

vect2 &vect2::operator++() {
	_num[0]++;
	_num[1]++;
	return *this;
}

vect2 vect2::operator--(int) {
	vect2 tmp(*this);
	_num[0]--;
	_num[1]--;
	return tmp;
}

vect2 &vect2::operator--() {
	_num[0]--;
	_num[1]--;
	return *this;
}

vect2::~vect2() {}

std::ostream &operator<<(std::ostream &out, const vect2 &obj) {
	out <<  "{" <<obj[0] << ", " << obj[1] << "}";
	return out;
}

vect2 operator*(int n, const vect2 &obj) {
	vect2 tmp(obj);
	tmp *= n;
	return tmp;
}
