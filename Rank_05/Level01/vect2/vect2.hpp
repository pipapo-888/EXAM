#ifndef VECT2_HPP
#define VECT2_HPP

class vect2 {
private:
	int _num[2];

public:
	vect2();
	vect2(int a, int b);
	vect2(const vect2 &obj);
	vect2& operator=(const vect2 &obj);
	~vect2();
};


#endif