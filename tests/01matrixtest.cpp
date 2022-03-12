#include "../include/Matrix4.hpp"
#include "../include/Matrix3.hpp"

#include <cmath>

int Matrix3Test(const Vector3f &test)
{
    std::cout << "# Testing Matrix3" << std::endl;

    Vector2f tileSize_(64, 32);
    float gridSize_(10.f);
    Vector3f position_(10,20,30);
    Vector3f origin_(400, 300, 0);

    float w_h = tileSize_.x / 2.0;
    float h_h = tileSize_.y / 2.0;
    float l = w_h / cos((45.0 / 180.0) * M_PI);
    Vector3f s = Vector3f(gridSize_, gridSize_, gridSize_);

    Matrix3 displaceMatrix_(
        w_h / s.x, -1 * w_h / s.y, 0,
        h_h / s.x, h_h / s.y, -1 * l / s.z,
        w_h * tan((45.0 / 180.0) * M_PI) / s.x, w_h * tan((45.0 / 180.0) * M_PI) / s.y, 0
    );

    Vector3f translation_ = origin_ - (displaceMatrix_ * position_);

    Matrix3 transformMatrix_ = displaceMatrix_;

    Matrix3 inverseTransform = transformMatrix_.getInverse();
    Matrix3 inverseDisplace = displaceMatrix_.getInverse();

    std::cout << "              Using Vector: " << test << std::endl;

    Vector3f transformed = (displaceMatrix_ * test) + translation_;
    std::cout << "                Transfomed: " << transformed << std::endl;

    std::cout << "    Inverse of Transformed: " << inverseDisplace * (transformed - translation_) << std::endl;

    transformed = (displaceMatrix_ * test) ;
    std::cout << "                Transfomed: " << transformed << std::endl;

    std::cout << "    Inverse of Transformed: " << inverseDisplace * (transformed ) << std::endl;

    return 0;
}

int Matrix4Test(const Vector3f &test)
{
    std::cout << "# Testing Matrix4" << std::endl;

    Vector2f tileSize_(64, 32);
    float gridSize_(10.f);
    Vector3f position_(10,20,300);
    Vector3f origin_(400, 300, 0);

    float w_h = tileSize_.x / 2.0;
    float h_h = tileSize_.y / 2.0;
    float l = w_h / cos((45.0 / 180.0) * M_PI);
    Vector3f s = Vector3f(gridSize_, gridSize_, gridSize_);

    Matrix4 displaceMatrix_(
        w_h / s.x, -1 * w_h / s.y, 0, 0,
        h_h / s.x, h_h / s.y, -1 * l / s.z, 0,
        w_h * tan((45.0 / 180.0) * M_PI) / s.x, w_h * tan((45.0 / 180.0) * M_PI) / s.y, 0, 0,
        0,0,0,1
    );

    Vector3f translation_ = origin_ - matMultipy(displaceMatrix_, position_);

    Matrix4 transformMatrix_ = displaceMatrix_;

    transformMatrix_[0][3] = translation_.x;
    transformMatrix_[1][3] = translation_.y;
    transformMatrix_[2][3] = translation_.z;
    transformMatrix_[3][3] = 1;

    Matrix4 inverseTransform = transformMatrix_.getInverse();
    Matrix4 inverseDisplace = displaceMatrix_.getInverse();

    std::cout << "              Using Vector: " << test << std::endl;

    Vector3f transformed = matMultipy(transformMatrix_, test);
    std::cout << "                Transfomed: " << transformed << std::endl;

    std::cout << "    Inverse of Transformed: " << matMultipy(inverseTransform, transformed) << std::endl;

    transformed = matMultipy(transformMatrix_, test, 0);
    std::cout << "                Transfomed: " << transformed << std::endl;

    std::cout << "    Inverse of Transformed: " << matMultipy(inverseTransform, transformed, 0) << std::endl;

    return 0;
}

int main()
{
    Matrix3Test(Vector3f(10, 100, 20));

    Matrix4Test(Vector3f(10, 100, 20));

    return 0;
}