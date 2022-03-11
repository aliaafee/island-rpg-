#ifndef __MATRIX4_H__
#define __MATRIX4_H__

#include <iostream>
#include "Vector.hpp"

class Matrix4
{
    friend std::ostream &operator<<(std::ostream &os, Matrix4 &matrix);

public:
    Matrix4();
    Matrix4(float a00, float a01, float a02, float a03,
            float a04, float a05, float a06, float a07,
            float a08, float a09, float a10, float a11,
            float a12, float a13, float a14, float a15);
    float value[4][4];

    Matrix4 operator*(Matrix4 B);
    Matrix4 operator*(float factor);

    float (&operator[](size_t i))[4]
    {
        return value[i];
    }

    Matrix4 getInverse();
    void getInverse(Matrix4 &output);

protected:
private:
    float MINOR(float *m, int r0, int r1, int r2, int c0, int c1, int c2);
    void adjoint(float *m, float adjOut[16]);
    float det(float *m);
    void invertRowMajor(float *m, float *invOut);
};

inline Vector3f matMultipy(const Matrix4 &matrix, const Vector3f &v, const float &w)
{
    return Vector3f(
        v.x * matrix.value[0][0] +
            v.y * matrix.value[0][1] +
            v.z * matrix.value[0][2] +
            w * matrix.value[0][3],

        v.x * matrix.value[1][0] +
            v.y * matrix.value[1][1] +
            v.z * matrix.value[1][2] +
            w * matrix.value[1][3],

        v.x * matrix.value[2][0] +
            v.y * matrix.value[2][1] +
            v.z * matrix.value[2][2] +
            w * matrix.value[2][3]);
}

inline Vector3f matMultipy(const Matrix4 &matrix, const Vector3f &v)
{
    return Vector3f(
        v.x * matrix.value[0][0] +
            v.y * matrix.value[0][1] +
            v.z * matrix.value[0][2] +
            1 * matrix.value[0][3],

        v.x * matrix.value[1][0] +
            v.y * matrix.value[1][1] +
            v.z * matrix.value[1][2] +
            1 * matrix.value[1][3],

        v.x * matrix.value[2][0] +
            v.y * matrix.value[2][1] +
            v.z * matrix.value[2][2] +
            1 * matrix.value[2][3]);
}

inline std::ostream &operator<<(std::ostream &os, Matrix4 &matrix)
{
    os << std::endl;
    int i, j;
    for (i = 0; i < 4; i++)
    {
        os << "|";
        for (j = 0; j < 3; j++)
        {
            os << matrix.value[i][j] << ",\t";
        }
        os << matrix.value[i][3] << "\t|" << std::endl;
    }
    os << std::endl;
    return os;
}

#endif // __MATRIX4_H__