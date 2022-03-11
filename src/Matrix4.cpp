#include "Matrix4.hpp"

Matrix4::Matrix4()
{
    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            value[i][j] = 0;
}

Matrix4::Matrix4(float a00, float a01, float a02, float a03,
                 float a10, float a11, float a12, float a13,
                 float a20, float a21, float a22, float a23,
                 float a30, float a31, float a32, float a33)
{
    value[0][0] = a00;
    value[0][1] = a01;
    value[0][2] = a02;
    value[0][3] = a03;

    value[1][0] = a10;
    value[1][1] = a11;
    value[1][2] = a12;
    value[1][3] = a13;

    value[2][0] = a20;
    value[2][1] = a21;
    value[2][2] = a22;
    value[2][3] = a23;

    value[3][0] = a30;
    value[3][1] = a31;
    value[3][2] = a32;
    value[3][3] = a33;
}

Matrix4 Matrix4::operator*(Matrix4 B)
{
    int i, j, k;
    Matrix4 result;

    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            for (k = 0, result.value[i][j] = 0; k < 4; k++)
                result.value[i][j] += value[i][k] * B.value[k][j];
    return result;
}

Matrix4 Matrix4::operator*(float factor)
{
    int i, j;
    Matrix4 result;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            result.value[i][j] = value[i][j] * factor;
    return result;
}

Matrix4 Matrix4::getInverse()
{

    Matrix4 result;

    invertRowMajor(&value[0][0], &result.value[0][0]);

    return result;
}

void Matrix4::getInverse(Matrix4 &output)
{
    invertRowMajor(&value[0][0], &output.value[0][0]);
}

float Matrix4::MINOR(float m[16], int r0, int r1, int r2, int c0, int c1, int c2)
{
    return m[4 * r0 + c0] * (m[4 * r1 + c1] * m[4 * r2 + c2] - m[4 * r2 + c1] * m[4 * r1 + c2]) -
           m[4 * r0 + c1] * (m[4 * r1 + c0] * m[4 * r2 + c2] - m[4 * r2 + c0] * m[4 * r1 + c2]) +
           m[4 * r0 + c2] * (m[4 * r1 + c0] * m[4 * r2 + c1] - m[4 * r2 + c0] * m[4 * r1 + c1]);
}

void Matrix4::adjoint(float *m, float adjOut[16])
{
    adjOut[0] = MINOR(m, 1, 2, 3, 1, 2, 3);
    adjOut[1] = -MINOR(m, 0, 2, 3, 1, 2, 3);
    adjOut[2] = MINOR(m, 0, 1, 3, 1, 2, 3);
    adjOut[3] = -MINOR(m, 0, 1, 2, 1, 2, 3);
    adjOut[4] = -MINOR(m, 1, 2, 3, 0, 2, 3);
    adjOut[5] = MINOR(m, 0, 2, 3, 0, 2, 3);
    adjOut[6] = -MINOR(m, 0, 1, 3, 0, 2, 3);
    adjOut[7] = MINOR(m, 0, 1, 2, 0, 2, 3);
    adjOut[8] = MINOR(m, 1, 2, 3, 0, 1, 3);
    adjOut[9] = -MINOR(m, 0, 2, 3, 0, 1, 3);
    adjOut[10] = MINOR(m, 0, 1, 3, 0, 1, 3);
    adjOut[11] = -MINOR(m, 0, 1, 2, 0, 1, 3);
    adjOut[12] = -MINOR(m, 1, 2, 3, 0, 1, 2);
    adjOut[13] = MINOR(m, 0, 2, 3, 0, 1, 2);
    adjOut[14] = -MINOR(m, 0, 1, 3, 0, 1, 2);
    adjOut[15] = MINOR(m, 0, 1, 2, 0, 1, 2);
}

float Matrix4::det(float *m)
{
    return m[0] * MINOR(m, 1, 2, 3, 1, 2, 3) -
           m[1] * MINOR(m, 1, 2, 3, 0, 2, 3) +
           m[2] * MINOR(m, 1, 2, 3, 0, 1, 3) -
           m[3] * MINOR(m, 1, 2, 3, 0, 1, 2);
}

void Matrix4::invertRowMajor(float *m, float *invOut)
{
    adjoint(m, invOut);

    float inv_det = 1.0f / det(m);

    for (int i = 0; i < 16; ++i)
        invOut[i] = invOut[i] * inv_det;
}