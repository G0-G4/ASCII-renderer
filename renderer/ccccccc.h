#pragma once

#ifndef VEC_H
#define VEC_H
#include <cmath>


//class HomogMatrix;

// k = 1 point k = 0 vector


class vec{
private:
public:
    float x,y,z;
    vec(float x, float y, float z);


};

class vec {
public:
    float x,y,z,k;
    int inf, Nid;
    vec(float x=0, float y=0, float z=0,float k = 1, int inf=0, int Nid = 0);
    vec(HomogMatrix M);
    vec (const vec& v);
    vec norm();
    float Z() const;
    friend vec operator+(const vec& v1, const vec& v2);
    vec& operator+=(const vec& v);
    vec& operator-=(const vec& v);
    friend float operator*(const vec& v1, const vec& v2);
    friend vec operator*(const vec& v1, const float& n);

};


class HomogMatrix{

private:

public:
    int rows, cols;
    void init(int rows = 4,int cols = 4);
    float matrix[4][4];
    HomogMatrix(int rows = 4,int cols = 4);
    HomogMatrix(vec V);
    void Rotation(vec V);
    void Rx(vec V);
    void Ry(vec V);
    void Rz(vec V);
    void Translation(vec V);
    void Scale(vec V);
    void Transpose();

    friend HomogMatrix operator*(const HomogMatrix& M1, const HomogMatrix& M2);
};

#endif // VEC_H
