//
// TM & (c) 2017 Lucasfilm Entertainment Company Ltd. and Lucasfilm Ltd.
// All rights reserved.  See LICENSE.txt for license.
//

#include <MaterialXCore/Types.h>

#include <cmath>

namespace MaterialX
{

const string DEFAULT_TYPE_STRING = "color3";
const string FILENAME_TYPE_STRING = "filename";
const string GEOMNAME_TYPE_STRING = "geomname";
const string SURFACE_SHADER_TYPE_STRING = "surfaceshader";
const string DISPLACEMENT_SHADER_TYPE_STRING = "displacementshader";
const string VOLUME_SHADER_TYPE_STRING = "volumeshader";
const string LIGHT_SHADER_TYPE_STRING = "lightshader";
const string MULTI_OUTPUT_TYPE_STRING = "multioutput";
const string NONE_TYPE_STRING = "none";
const string VALUE_STRING_TRUE = "true";
const string VALUE_STRING_FALSE = "false";
const string NAME_PREFIX_SEPARATOR = ":";
const string NAME_PATH_SEPARATOR = "/";
const string ARRAY_VALID_SEPARATORS = ", ";
const string ARRAY_PREFERRED_SEPARATOR = ", ";

const Matrix33 Matrix33::IDENTITY(1, 0, 0,
                                  0, 1, 0,
                                  0, 0, 1);

const Matrix44 Matrix44::IDENTITY(1, 0, 0, 0,
                                  0, 1, 0, 0,
                                  0, 0, 1, 0,
                                  0, 0, 0, 1);


//
// Vector methods
//
template <> float VectorN<Vector2, float, 2>::getMagnitude() const
{
    return std::sqrt(_arr[0]*_arr[0] + _arr[1]*_arr[1]);
}

template <> float VectorN<Vector3, float, 3>::getMagnitude() const
{
    return std::sqrt(_arr[0]*_arr[0] + _arr[1]*_arr[1] + _arr[2]*_arr[2]);
}

template <> float VectorN<Vector4, float, 4>::getMagnitude() const
{
    return std::sqrt(_arr[0]*_arr[0] + _arr[1]*_arr[1] +
                     _arr[2]*_arr[2] + _arr[3]*_arr[3]);
}

//
// Matrix33 methods
//

template <> Matrix33 MatrixN<Matrix33, float, 3>::getTranspose() const
{
    return Matrix33(_arr[0][0], _arr[1][0], _arr[2][0],
                    _arr[0][1], _arr[1][1], _arr[2][1],
                    _arr[0][2], _arr[1][2], _arr[2][2]);
}

template <> float MatrixN<Matrix33, float, 3>::getDeterminant() const
{
    return _arr[0][0] * (_arr[1][1]*_arr[2][2] - _arr[2][1]*_arr[1][2]) +
           _arr[0][1] * (_arr[1][2]*_arr[2][0] - _arr[2][2]*_arr[1][0]) +
           _arr[0][2] * (_arr[1][0]*_arr[2][1] - _arr[2][0]*_arr[1][1]);
}

template <> Matrix33 MatrixN<Matrix33, float, 3>::getAdjugate() const
{
    return Matrix33(
        _arr[1][1]*_arr[2][2] - _arr[2][1]*_arr[1][2],
        _arr[2][1]*_arr[0][2] - _arr[0][1]*_arr[2][2],
        _arr[0][1]*_arr[1][2] - _arr[1][1]*_arr[0][2],
        _arr[1][2]*_arr[2][0] - _arr[2][2]*_arr[1][0],
        _arr[2][2]*_arr[0][0] - _arr[0][2]*_arr[2][0],
        _arr[0][2]*_arr[1][0] - _arr[1][2]*_arr[0][0],
        _arr[1][0]*_arr[2][1] - _arr[2][0]*_arr[1][1],
        _arr[2][0]*_arr[0][1] - _arr[0][0]*_arr[2][1],
        _arr[0][0]*_arr[1][1] - _arr[1][0]*_arr[0][1]);
}

Vector3 Matrix33::multiply(const Vector3& rhs) const
{
    return Vector3(
      _arr[0][0] * rhs[0] + _arr[0][1] * rhs[1] + _arr[0][2] * rhs[2],
      _arr[1][0] * rhs[0] + _arr[1][1] * rhs[1] + _arr[1][2] * rhs[2],
      _arr[2][0] * rhs[0] + _arr[2][1] * rhs[1] + _arr[2][2] * rhs[2]
    );
}

Vector2 Matrix33::transformPoint(const Vector2& rhs) const
{
    Vector3 rhs3(rhs[0], rhs[1], 1.0f);
    rhs3 = multiply(rhs3);
    return Vector2(rhs3[0], rhs3[1]);
}

Vector2 Matrix33::transformVector(const Vector2& rhs) const
{
    Vector3 rhs3(rhs[0], rhs[1], 0.0f);
    rhs3 = multiply(rhs3);
    return Vector2(rhs3[0], rhs3[1]);
}

Vector3 Matrix33::transformNormal(const Vector3& rhs) const
{
    return getInverse().getTranspose().multiply(rhs);
}

Matrix33 Matrix33::createTranslation(const Vector2& v)
{
    return Matrix33(1.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
                    v[0], v[1], 1.0f);
}

Matrix33 Matrix33::createScale(const Vector2& v)
{
    return Matrix33(v[0], 0.0f, 0.0f,
                    0.0f, v[1], 0.0f,
                    0.0f, 0.0f, 1.0f);
}

Matrix33 Matrix33::createRotation(float angle)
{
    float sine = std::sin(angle);
    float cosine = std::cos(angle);

    return Matrix33(cosine, -sine, 0.0f,
                    sine, cosine, 0.0f,
                    0.0f, 0.0f, 1.0f);
}

//
// Matrix44 methods
//

template <> Matrix44 MatrixN<Matrix44, float, 4>::getTranspose() const
{
    return Matrix44(_arr[0][0], _arr[1][0], _arr[2][0], _arr[3][0],
                    _arr[0][1], _arr[1][1], _arr[2][1], _arr[3][1],
                    _arr[0][2], _arr[1][2], _arr[2][2], _arr[3][2],
                    _arr[0][3], _arr[1][3], _arr[2][3], _arr[3][3]);
}

template <> float MatrixN<Matrix44, float, 4>::getDeterminant() const
{
    return _arr[0][0] * (_arr[1][1]*_arr[2][2]*_arr[3][3] + _arr[3][1]*_arr[1][2]*_arr[2][3] + _arr[2][1]*_arr[3][2]*_arr[1][3] -
                         _arr[1][1]*_arr[3][2]*_arr[2][3] - _arr[2][1]*_arr[1][2]*_arr[3][3] - _arr[3][1]*_arr[2][2]*_arr[1][3]) +
           _arr[0][1] * (_arr[1][2]*_arr[3][3]*_arr[2][0] + _arr[2][2]*_arr[1][3]*_arr[3][0] + _arr[3][2]*_arr[2][3]*_arr[1][0] -
                         _arr[1][2]*_arr[2][3]*_arr[3][0] - _arr[3][2]*_arr[1][3]*_arr[2][0] - _arr[2][2]*_arr[3][3]*_arr[1][0]) +
           _arr[0][2] * (_arr[1][3]*_arr[2][0]*_arr[3][1] + _arr[3][3]*_arr[1][0]*_arr[2][1] + _arr[2][3]*_arr[3][0]*_arr[1][1] -
                         _arr[1][3]*_arr[3][0]*_arr[2][1] - _arr[2][3]*_arr[1][0]*_arr[3][1] - _arr[3][3]*_arr[2][0]*_arr[1][1]) +
           _arr[0][3] * (_arr[1][0]*_arr[3][1]*_arr[2][2] + _arr[2][0]*_arr[1][1]*_arr[3][2] + _arr[3][0]*_arr[2][1]*_arr[1][2] -
                         _arr[1][0]*_arr[2][1]*_arr[3][2] - _arr[3][0]*_arr[1][1]*_arr[2][2] - _arr[2][0]*_arr[3][1]*_arr[1][2]);
}

template <> Matrix44 MatrixN<Matrix44, float, 4>::getAdjugate() const
{
    return Matrix44(
        _arr[1][1]*_arr[2][2]*_arr[3][3] + _arr[3][1]*_arr[1][2]*_arr[2][3] + _arr[2][1]*_arr[3][2]*_arr[1][3] -
        _arr[1][1]*_arr[3][2]*_arr[2][3] - _arr[2][1]*_arr[1][2]*_arr[3][3] - _arr[3][1]*_arr[2][2]*_arr[1][3],

        _arr[0][1]*_arr[3][2]*_arr[2][3] + _arr[2][1]*_arr[0][2]*_arr[3][3] + _arr[3][1]*_arr[2][2]*_arr[0][3] -
        _arr[3][1]*_arr[0][2]*_arr[2][3] - _arr[2][1]*_arr[3][2]*_arr[0][3] - _arr[0][1]*_arr[2][2]*_arr[3][3],

        _arr[0][1]*_arr[1][2]*_arr[3][3] + _arr[3][1]*_arr[0][2]*_arr[1][3] + _arr[1][1]*_arr[3][2]*_arr[0][3] -
        _arr[0][1]*_arr[3][2]*_arr[1][3] - _arr[1][1]*_arr[0][2]*_arr[3][3] - _arr[3][1]*_arr[1][2]*_arr[0][3],

        _arr[0][1]*_arr[2][2]*_arr[1][3] + _arr[1][1]*_arr[0][2]*_arr[2][3] + _arr[2][1]*_arr[1][2]*_arr[0][3] -
        _arr[0][1]*_arr[1][2]*_arr[2][3] - _arr[2][1]*_arr[0][2]*_arr[1][3] - _arr[1][1]*_arr[2][2]*_arr[0][3],

        _arr[1][2]*_arr[3][3]*_arr[2][0] + _arr[2][2]*_arr[1][3]*_arr[3][0] + _arr[3][2]*_arr[2][3]*_arr[1][0] -
        _arr[1][2]*_arr[2][3]*_arr[3][0] - _arr[3][2]*_arr[1][3]*_arr[2][0] - _arr[2][2]*_arr[3][3]*_arr[1][0],

        _arr[0][2]*_arr[2][3]*_arr[3][0] + _arr[3][2]*_arr[0][3]*_arr[2][0] + _arr[2][2]*_arr[3][3]*_arr[0][0] -
        _arr[0][2]*_arr[3][3]*_arr[2][0] - _arr[2][2]*_arr[0][3]*_arr[3][0] - _arr[3][2]*_arr[2][3]*_arr[0][0],

        _arr[0][2]*_arr[3][3]*_arr[1][0] + _arr[1][2]*_arr[0][3]*_arr[3][0] + _arr[3][2]*_arr[1][3]*_arr[0][0] -
        _arr[0][2]*_arr[1][3]*_arr[3][0] - _arr[3][2]*_arr[0][3]*_arr[1][0] - _arr[1][2]*_arr[3][3]*_arr[0][0],

        _arr[0][2]*_arr[1][3]*_arr[2][0] + _arr[2][2]*_arr[0][3]*_arr[1][0] + _arr[1][2]*_arr[2][3]*_arr[0][0] -
        _arr[0][2]*_arr[2][3]*_arr[1][0] - _arr[1][2]*_arr[0][3]*_arr[2][0] - _arr[2][2]*_arr[1][3]*_arr[0][0],

        _arr[1][3]*_arr[2][0]*_arr[3][1] + _arr[3][3]*_arr[1][0]*_arr[2][1] + _arr[2][3]*_arr[3][0]*_arr[1][1] -
        _arr[1][3]*_arr[3][0]*_arr[2][1] - _arr[2][3]*_arr[1][0]*_arr[3][1] - _arr[3][3]*_arr[2][0]*_arr[1][1],

        _arr[0][3]*_arr[3][0]*_arr[2][1] + _arr[2][3]*_arr[0][0]*_arr[3][1] + _arr[3][3]*_arr[2][0]*_arr[0][1] -
        _arr[0][3]*_arr[2][0]*_arr[3][1] - _arr[3][3]*_arr[0][0]*_arr[2][1] - _arr[2][3]*_arr[3][0]*_arr[0][1],

        _arr[0][3]*_arr[1][0]*_arr[3][1] + _arr[3][3]*_arr[0][0]*_arr[1][1] + _arr[1][3]*_arr[3][0]*_arr[0][1] -
        _arr[0][3]*_arr[3][0]*_arr[1][1] - _arr[1][3]*_arr[0][0]*_arr[3][1] - _arr[3][3]*_arr[1][0]*_arr[0][1],

        _arr[0][3]*_arr[2][0]*_arr[1][1] + _arr[1][3]*_arr[0][0]*_arr[2][1] + _arr[2][3]*_arr[1][0]*_arr[0][1] -
        _arr[0][3]*_arr[1][0]*_arr[2][1] - _arr[2][3]*_arr[0][0]*_arr[1][1] - _arr[1][3]*_arr[2][0]*_arr[0][1],

        _arr[1][0]*_arr[3][1]*_arr[2][2] + _arr[2][0]*_arr[1][1]*_arr[3][2] + _arr[3][0]*_arr[2][1]*_arr[1][2] -
        _arr[1][0]*_arr[2][1]*_arr[3][2] - _arr[3][0]*_arr[1][1]*_arr[2][2] - _arr[2][0]*_arr[3][1]*_arr[1][2],

        _arr[0][0]*_arr[2][1]*_arr[3][2] + _arr[3][0]*_arr[0][1]*_arr[2][2] + _arr[2][0]*_arr[3][1]*_arr[0][2] -
        _arr[0][0]*_arr[3][1]*_arr[2][2] - _arr[2][0]*_arr[0][1]*_arr[3][2] - _arr[3][0]*_arr[2][1]*_arr[0][2],

        _arr[0][0]*_arr[3][1]*_arr[1][2] + _arr[1][0]*_arr[0][1]*_arr[3][2] + _arr[3][0]*_arr[1][1]*_arr[0][2] -
        _arr[0][0]*_arr[1][1]*_arr[3][2] - _arr[3][0]*_arr[0][1]*_arr[1][2] - _arr[1][0]*_arr[3][1]*_arr[0][2],

        _arr[0][0]*_arr[1][1]*_arr[2][2] + _arr[2][0]*_arr[0][1]*_arr[1][2] + _arr[1][0]*_arr[2][1]*_arr[0][2] -
        _arr[0][0]*_arr[2][1]*_arr[1][2] - _arr[1][0]*_arr[0][1]*_arr[2][2] - _arr[2][0]*_arr[1][1]*_arr[0][2]);
}


Vector4 Matrix44::multiply(const Vector4& rhs) const
{
    return Vector4(
      _arr[0][0] * rhs[0] + _arr[0][1] * rhs[1] + _arr[0][2] * rhs[2] + _arr[0][3] * rhs[3],
      _arr[1][0] * rhs[0] + _arr[1][1] * rhs[1] + _arr[1][2] * rhs[2] + _arr[1][3] * rhs[3],
      _arr[2][0] * rhs[0] + _arr[2][1] * rhs[1] + _arr[2][2] * rhs[2] + _arr[2][3] * rhs[3],
      _arr[3][0] * rhs[0] + _arr[3][1] * rhs[1] + _arr[3][2] * rhs[2] + _arr[3][3] * rhs[3]
    );
}

Vector3 Matrix44::transformPoint(const Vector3& rhs) const
{
    Vector4 rhs4(rhs[0], rhs[1], rhs[2], 1.0f);
    rhs4 = multiply(rhs4);
    return Vector3(rhs4[0], rhs4[1], rhs4[2]);
}

Vector3 Matrix44::transformVector(const Vector3& rhs) const
{
    Vector4 rhs4(rhs[0], rhs[1], rhs[2], 0.0f);
    rhs4 = multiply(rhs4);
    return Vector3(rhs4[0], rhs4[1], rhs4[2]);
}

Vector3 Matrix44::transformNormal(const Vector3& rhs) const
{
    Vector4 rhs4(rhs[0], rhs[1], rhs[2], 0.0f);
    rhs4 = getInverse().getTranspose().multiply(rhs4);
    return Vector3(rhs4[0], rhs4[1], rhs4[2]);
}

Matrix44 Matrix44::createTranslation(const Vector3& v)
{
    return Matrix44(1.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f,
                    v[0], v[1], v[2], 1.0f);
}

Matrix44 Matrix44::createScale(const Vector3& v)
{
    return Matrix44(v[0], 0.0f, 0.0f, 0.0f,
                    0.0f, v[1], 0.0f, 0.0f,
                    0.0f, 0.0f, v[2], 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix44 Matrix44::createRotationX(float angle)
{
    float sine = std::sin(angle);
    float cosine = std::cos(angle);

    return Matrix44(1.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, cosine, -sine, 0.0f,
                    0.0f, sine, cosine, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix44 Matrix44::createRotationY(float angle)
{
    float sine = std::sin(angle);
    float cosine = std::cos(angle);

    return Matrix44(cosine, 0.0f, sine, 0.0f,
                    0.0f, 1.0f, 0.0f, 0.0f,
                    -sine, 0.0f, cosine, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix44 Matrix44::createRotationZ(float angle)
{
    float sine = std::sin(angle);
    float cosine = std::cos(angle);

    return Matrix44(cosine, -sine, 0.0f, 0.0f,
                    sine, cosine, 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);
}

} // namespace MaterialX
