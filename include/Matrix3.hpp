#ifndef __MATRIX3_H__
#define __MATRIX3_H__

#include <iostream>

#include "Vector.hpp"

class Matrix3
{
public:
    Matrix3();
    Matrix3(float a00, float a01, float a02,
            float a03, float a04, float a05,
            float a06, float a07, float a08);

    Vector3f operator*(const Vector3f &vector) const;
    Matrix3 getInverse() const;

    const float &getValue(int i, int j) const { return value_[i][j]; };
private:
    float value_[3][3];
};


inline std::ostream& operator<<(std::ostream& os, Matrix3& matrix) {
	os << std::endl;
	int i,j;
	for(i = 0; i < 3; i++) {
		os << "|";
		for(j = 0; j < 2; j++) {
			os << matrix.getValue(i, j) << ",\t";
		}
		os << matrix.getValue(i, 2) << "\t|" << std::endl;
	}
	os << std::endl;
	return os;
}


#endif // __MATRIX3_H__