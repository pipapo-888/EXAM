#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <string>
#include <ostream>

class bigint
{
private:
	std::string _num;

public:
	bigint();
	bigint(unsigned int num);
	bigint(const bigint &obj);

	std::string getNum() const;


	~bigint();
};

std::ostream &operator<<(std::ostream &out, const bigint &obj);

#endif