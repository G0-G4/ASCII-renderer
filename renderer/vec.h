
#pragma once

#ifndef VEC_H
#define VEC_H
#include <cmath>
#include <stdexcept>

class mat;

class vec{

private:
    float eps = 0.001;
public:

    float x,y,z;

    explicit vec(float x = 0,float y = 0, float z = 0);
    vec(const vec& v);
    vec(const mat& m);
    float len();
    vec norm();

    void normalize();
    vec& operator+=(const vec& v);
    vec& operator-=(const vec& v);
    vec& operator*=(float n);
    vec& operator/=(float n);
    friend vec operator+(const vec& v1, const vec& v2);
    friend vec operator-(const vec& v1, const vec& v2);
    friend float operator*(const vec& v1, const vec& v2);
    friend vec operator*(float n, const vec& v);
    friend vec operator*(const vec& v, float n);
    friend vec operator/(const vec& v, float n);
    friend bool operator==(const vec& v1, const vec& v2);
    friend bool operator!=(const vec& v1, const vec& v2);
    friend vec cross(const vec& v1, const vec& v2);
};

class mat{

private:
    float matrix[4][4] = {0};
    int rows = 0;
    int cols = 0;
public:

    mat();
    mat(const vec& v);
    void Translation(const vec& v);
    void Rotation(const vec& v);
    void Scale(vec v);
    friend mat operator*(const mat& m1, const mat& m2);
    friend class vec;

};


#endif // VEC_H
