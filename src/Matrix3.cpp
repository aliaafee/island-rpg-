#include "Matrix3.h"

Matrix3::Matrix3()
{
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            value_[i][j] = 0;
}

Matrix3::Matrix3(float a00, float a01, float a02,
                 float a03, float a04, float a05,
                 float a06, float a07, float a08)
{
    value_[0][0] = a00;
    value_[0][1] = a01;
    value_[0][2] = a02;

    value_[1][0] = a03;
    value_[1][1] = a04;
    value_[1][2] = a05;

    value_[2][0] = a06;
    value_[2][1] = a07;
    value_[2][2] = a08;
}

sf::Vector3f Matrix3::operator*(const sf::Vector3f &vector) const
{
    return sf::Vector3f(
        value_[0][0] * vector.x + value_[0][1] * vector.y + value_[0][2] * vector.z,
        value_[1][0] * vector.x + value_[1][1] * vector.y + value_[1][2] * vector.z,
        value_[2][0] * vector.x + value_[2][1] * vector.y + value_[2][2] * vector.z);
}

Matrix3 Matrix3::getInverse() const
{
    /* Thanks Alok Aryan on stackoverflow" */
    float det_ = value_[0][0] * ((value_[1][1] * value_[2][2]) - (value_[1][2] * value_[2][1])) -
                 value_[0][1] * ((value_[1][0] * value_[2][2]) - (value_[1][2] * value_[2][0])) +
                 value_[0][2] * ((value_[1][0] * value_[2][1]) - (value_[1][1] * value_[2][0]));

    float co_fctr_1[3];
    float co_fctr_2[3];
    float co_fctr_3[3];

    co_fctr_1[0] = (value_[1][1] * value_[2][2]) - (value_[1][2] * value_[2][1]);
    co_fctr_1[1] = -((value_[1][0] * value_[2][2]) - (value_[1][2] * value_[2][0]));
    co_fctr_1[2] = (value_[1][0] * value_[2][1]) - (value_[1][1] * value_[2][0]);

    co_fctr_2[0] = -((value_[0][1] * value_[2][2]) - (value_[0][2] * value_[2][1]));
    co_fctr_2[1] = (value_[0][0] * value_[2][2]) - (value_[0][2] * value_[2][0]);
    co_fctr_2[2] = -((value_[0][0] * value_[2][1]) - (value_[0][1] * value_[2][0]));

    co_fctr_3[0] = (value_[0][1] * value_[1][2]) - (value_[0][2] * value_[1][1]);
    co_fctr_3[1] = -((value_[0][0] * value_[1][2]) - (value_[0][2] * value_[1][0]));
    co_fctr_3[2] = (value_[0][0] * value_[1][1]) - (value_[0][1] * value_[1][0]);

    return Matrix3(1 / det_ * (co_fctr_1[0]), 1 / det_ * (co_fctr_2[0]), 1 / det_ * (co_fctr_3[0]),
                   1 / det_ * (co_fctr_1[1]), 1 / det_ * (co_fctr_2[1]), 1 / det_ * (co_fctr_3[1]),
                   1 / det_ * (co_fctr_1[2]), 1 / det_ * (co_fctr_2[2]), 1 / det_ * (co_fctr_3[2]));
}
