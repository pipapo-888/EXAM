#ifndef VECT2_HPP
#define VECT2_HPP

#include <ostream>

class vect2
{
private:
	int _num[2];

public:
	vect2();
	vect2(int a, int b);
	vect2(const vect2 &obj);

	vect2 &operator=(const vect2 &obj);

	vect2 &operator+=(const vect2 &obj);
	vect2 &operator-=(const vect2 &obj);
	vect2 &operator*=(const vect2 &obj);
	vect2 &operator*=(const int n);

	vect2 operator+(const vect2 &obj) const;
	vect2 operator-(const vect2 &obj) const;
	vect2 operator*(const vect2 &obj) const; 
	vect2 operator*(const int n) const; 
	vect2 operator-() const;

	bool operator==(const vect2 &obj) const;
	bool operator!=(const vect2 &obj) const;
	
	int &operator[](const int n);
	const int &operator[](const int n) const;

	vect2 operator++(int);
	vect2 &operator++();
	vect2 operator--(int);
	vect2 &operator--();


	~vect2();
};

std::ostream &operator<<(std::ostream &out, const vect2 &obj);
vect2 operator*(int n, vect2 &obj);

#endif