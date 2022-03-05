#include "matrix3.h"

Matrix3::Matrix3()
{
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            _value[i][j] = 0;
}

Matrix3::Matrix3(float a00, float a01, float a02,
                 float a03, float a04, float a05,
                 float a06, float a07, float a08)
{
    _value[0][0] = a00;
    _value[0][1] = a01;
    _value[0][2] = a02;

    _value[1][0] = a03;
    _value[1][1] = a04;
    _value[1][2] = a05;

    _value[2][0] = a06;
    _value[2][1] = a07;
    _value[2][2] = a08;
}

const sf::Vector3f Matrix3::operator*(const sf::Vector3f &vector)
{
    return sf::Vector3f(
        _value[0][0] * vector.x + _value[0][1] * vector.y + _value[0][2] * vector.z,
        _value[1][0] * vector.x + _value[1][1] * vector.y + _value[1][2] * vector.z,
        _value[2][0] * vector.x + _value[2][1] * vector.y + _value[2][2] * vector.z);
}

Matrix3 Matrix3::getInverse()
{
    /* Thanks Alok Aryan on stackoverflow" */
    float det_ = _value[0][0] * ((_value[1][1] * _value[2][2]) - (_value[1][2] * _value[2][1])) -
                 _value[0][1] * ((_value[1][0] * _value[2][2]) - (_value[1][2] * _value[2][0])) +
                 _value[0][2] * ((_value[1][0] * _value[2][1]) - (_value[1][1] * _value[2][0]));

    float co_fctr_1[3];
    float co_fctr_2[3];
    float co_fctr_3[3];

    co_fctr_1[0] = (_value[1][1] * _value[2][2]) - (_value[1][2] * _value[2][1]);
    co_fctr_1[1] = -((_value[1][0] * _value[2][2]) - (_value[1][2] * _value[2][0]));
    co_fctr_1[2] = (_value[1][0] * _value[2][1]) - (_value[1][1] * _value[2][0]);

    co_fctr_2[0] = -((_value[0][1] * _value[2][2]) - (_value[0][2] * _value[2][1]));
    co_fctr_2[1] = (_value[0][0] * _value[2][2]) - (_value[0][2] * _value[2][0]);
    co_fctr_2[2] = -((_value[0][0] * _value[2][1]) - (_value[0][1] * _value[2][0]));

    co_fctr_3[0] = (_value[0][1] * _value[1][2]) - (_value[0][2] * _value[1][1]);
    co_fctr_3[1] = -((_value[0][0] * _value[1][2]) - (_value[0][2] * _value[1][0]));
    co_fctr_3[2] = (_value[0][0] * _value[1][1]) - (_value[0][1] * _value[1][0]);

    return Matrix3(1 / det_ * (co_fctr_1[0]), 1 / det_ * (co_fctr_2[0]), 1 / det_ * (co_fctr_3[0]),
                   1 / det_ * (co_fctr_1[1]), 1 / det_ * (co_fctr_2[1]), 1 / det_ * (co_fctr_3[1]),
                   1 / det_ * (co_fctr_1[2]), 1 / det_ * (co_fctr_2[2]), 1 / det_ * (co_fctr_3[2]));
}
