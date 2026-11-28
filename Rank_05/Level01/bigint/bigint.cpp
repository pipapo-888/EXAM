#include "bigint.hpp"

#include <iostream>

bigint::bigint() : _num("0")
{
}

bigint::bigint(unsigned int num)
{
	if (num == 0)
		_num = "0";
	while (num)
	{
		char c = num % 10 + '0';
		_num = c + _num;
		num /= 10;
	}
}

bigint::bigint(const bigint &obj) : _num(obj._num) {}

std::string bigint::getNum() const
{
	return _num;
}


bigint::~bigint() {}

std::ostream &operator<<(std::ostream &out, const bigint &obj)
{
	out << obj.getNum();
	return out;
}