#include "vec.h"



vec::vec(float x,float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

vec::vec(const vec& v){
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
}

vec::vec(const mat& m){
    if(m.rows == 4 && m.cols == 1){
        x = m.matrix[0][0];
        y = m.matrix[1][0];
        z = m.matrix[2][0];
    }
    else{
        throw std::domain_error("only 4x1 matrix could be inverted into vec");
    }
}

float vec::len(){
    return sqrt(pow(x,2) + pow(y,2) + pow(z,2));
}

vec vec::norm(){
    float l = len();
    vec N(x/l, y/l, z/l);
    return N;
}


vec& vec::operator+=(const vec& v){
    x += v.x;
    y += v.y;
    z += v.z;
}

vec& vec::operator-=(const vec& v){
    x -= v.x;
    y -= v.y;
    z -= v.z;
}



vec operator+(const vec& v1, const vec& v2){
return vec(v1.x+v2.x, v1.y+v2.y,v1.z+v2.z);
}

vec operator-(const vec& v1, const vec& v2){
return vec(v1.x-v2.x, v1.y-v2.y,v1.z-v2.z);
}

vec operator*(const vec& v1, const vec& v2){
return vec(v1.x*v2.x, v1.y*v2.y,v1.z*v2.z);;
};

vec operator*(float n, const vec& v){
return vec(n*v.x, n*v.y, n*v.z);
};

vec operator*(const vec& v, float n){
return vec(n*v.x, n*v.y, n*v.z);
};


mat::mat(){};

mat::mat(const vec& v){
    rows = 4;
    cols = 1;
    matrix[0][0] = v.x;
    matrix[1][0] = v.y;
    matrix[2][0] = v.z;
    matrix[3][0] = 1;
}
void mat::Translation(const vec& v){
    matrix[0][0] = 1;
    matrix[1][1] = 1;
    matrix[2][2] = 1;
    matrix[0][3] = v.x;
    matrix[1][3] = v.y;
    matrix[2][3] = v.z;

    matrix[3][3] = 1;
    rows = 4;
    cols = 4;
}

void mat::Rotation(const vec& v){
    float x = v.x;
    float y = v.y;
    float z = v.z;

    matrix[0][0] = (cos(y+z)+cos(y-z))/2;
    matrix[0][1] = (-cos(x+y+z)+cos(x-y+z)-cos(x+y-z)+cos(x-y-z)-2*sin(x+z)+2*sin(x-z))/4;
    matrix[0][2] = (-2*cos(x+z)+2*cos(x-z)+sin(x+y+z)-sin(x-y+z)+sin(x+y-z)-sin(x-y-z))/4;

    matrix[1][0] = (sin(y+z)-sin(y-z))/2;
    matrix[1][1] = (2*cos(x+z)+2*cos(x-z)-sin(x+y+z)+sin(x-y+z)+sin(x+y-z)-sin(x-y-z))/4;
    matrix[1][2] = (-cos(x+y+z)+cos(x-y+z)+cos(x+y-z)-cos(x-y-z)-2*sin(x+z)-2*sin(x-z))/4;

    matrix[2][0] = -sin(y);
    matrix[2][1] = (sin(x+y)+sin(x-y))/2;
    matrix[2][2] = (cos(x+y)+cos(x-y))/2;

    matrix[3][3] = 1;

    rows = 4;
    cols = 4;

    return;
}


void mat::Scale(vec v){

    matrix[0][0] = v.x;
    matrix[1][1] = v.y;
    matrix[2][2] = v.z;
    matrix[3][3] = 1;
    return;
}



mat operator*(const mat& m1, const mat& m2){
if(m1.cols != m2.rows){
    throw std::domain_error("shape error");
}
mat m;
m.rows = m1.rows;
m.cols = m2.cols;
for(int i = 0; i < m1.rows; i++){
    for(int j = 0; j < m2.cols; j++){
        m.matrix[i][j] = 0;
        for(int k = 0; k < m2.rows; k++){
            m.matrix[i][j] += m1.matrix[i][k] * m2.matrix[k][j];
        }
    }
}
return m;
};

