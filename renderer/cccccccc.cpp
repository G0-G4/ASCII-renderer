#include "vec.h"


vec::vec(float x, float y, float z,float k, int inf, int Nid){
    this->x = x;
    this->y = y;
    this->z = z;
    this->k = k;
    this->inf = inf;
    this->Nid = Nid;
};

vec::vec(const vec& v){
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    this->k = v.k;
    this->inf = v.inf;
    this->Nid = v.Nid;
}


 float vec::Z() const{
    return z;
 }
vec& vec::operator+=(const vec& v){
    x += v.x;
    y += v.y;
    z += v.y;
    k += v.k;
    return *this;
};

vec& vec::operator-=(const vec& v){
    x -= v.x;
    y -= v.y;
    z -= v.y;
    k -= v.k;
    return *this;
};

vec vec::norm(){
    vec n;
    float len = sqrt(pow(x,2) + pow(y,2) + pow(z,2));
    n.x = x/len;
    n.y = y/len;
    n.z = z/len;
    return n;

};

vec::vec(HomogMatrix M):vec(M.matrix[0][0],M.matrix[1][0],M.matrix[2][0],M.matrix[3][0]){};

vec operator+(const vec& v1, const vec& v2){
    return vec(v1.x+v2.x,v1.y+v2.y,v1.z+v2.z,v1.inf, v1.Nid);
};

float operator*(const vec& v1, const vec& v2){
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
};

vec operator*(const vec& v1, const float& n){
    return vec(v1.x*n, v1.y*n, v1.z*n,v1.k*n,v1.inf, v1.Nid);
};


void HomogMatrix::init(int rows, int cols){
    for(int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            matrix[i][j] = 0;
        }
    };
    return;
}
HomogMatrix::HomogMatrix(int rows,int cols){
    this->rows = rows;
    this->cols = cols;
    init(rows, cols);
    return;
};

HomogMatrix::HomogMatrix(vec V){
    this->rows = 4;
    this->cols = 1;
    init();
    matrix[0][0] = V.x;
    matrix[1][0] = V.y;
    matrix[2][0] = V.z;
    matrix[3][0] = V.k;

};

void HomogMatrix::Rotation(vec V){
    // углы эйлера
    float x = V.x;
    float y = V.y;
    float z = V.z;
    /*
    float cosa, cosb, cosc, sina, sinb, sinc;
    cosa = cos(x); cosb = cos(y); cosc = cos(z);
    sina = sin(x); sinb = sin(y); sinc = sin(z);
    matrix[0][0] = cosa*cosc - sina*cosb*sinc;
    matrix[0][1] = -cosa*sinc - sina*cosb*cosc;
    matrix[0][2] = sina*sinb;

    matrix[1][0] = sina*cosc + cosa*cosb*sinc;
    matrix[1][1] = -sina*sinc + cosa*cosb*cosc;
    matrix[1][2] = -cosa*sinb;

    matrix[2][0] = sinb*sinc;
    matrix[2][1] = sinb*cosc;
    matrix[2][2] = cosb;

    matrix[3][3] = 1;
*/

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


    return;
}

void HomogMatrix::Rx(vec V){
    float a = V.x;
    float sina = sin(a), cosa = cos(a);
    matrix[0][0] = 1;
    matrix[0][1] = 0;
    matrix[0][2] = 0;

    matrix[1][0] = 0;
    matrix[1][1] = cosa;
    matrix[1][2] = -sina;

    matrix[2][0] = 0;
    matrix[2][1] = sina;
    matrix[2][2] = cosa;

    matrix[3][3] = 1;
}

void HomogMatrix::Ry(vec V){
    float a = V.y;
    float sina = sin(a), cosa = cos(a);
    matrix[0][0] = cosa;
    matrix[0][1] = 0;
    matrix[0][2] = sina;

    matrix[1][0] = 0;
    matrix[1][1] = 1;
    matrix[1][2] = 0;

    matrix[2][0] = -sina;
    matrix[2][1] = 0;
    matrix[2][2] = cosa;

    matrix[3][3] = 1;
}

void HomogMatrix::Rz(vec V){
    float a = V.z;
    float sina = sin(a), cosa = cos(a);
    matrix[0][0] = cosa;
    matrix[0][1] = -sina;
    matrix[0][2] = 0;

    matrix[1][0] = sina;
    matrix[1][1] = cosa;
    matrix[1][2] = 0;

    matrix[2][0] = 0;
    matrix[2][1] = 0;
    matrix[2][2] = 1;

    matrix[3][3] = 1;
}

void HomogMatrix::Scale(vec V){

    matrix[0][0] = V.x;
    matrix[1][1] = V.y;
    matrix[2][2] = V.z;
    matrix[3][3] = 1;
    return;
};


void HomogMatrix::Translation(vec V){
    matrix[0][0] = 1;
    matrix[1][1] = 1;
    matrix[2][2] = 1;
    matrix[3][3] = 1;
    matrix[0][3] = V.x;
    matrix[1][3] = V.y;
    matrix[2][3] = V.z;

    return;
};


void HomogMatrix::Transpose(){
    float tmp;
    for(int i = 0; i<rows;i++){
        for(int j = 0; j<i;j++){
            tmp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = tmp;
        }
    }
    tmp = rows;
    rows = cols;
    cols = tmp;

    return;
};

HomogMatrix operator*(const HomogMatrix& M1, const HomogMatrix& M2){
    HomogMatrix M(M1.rows,M2.cols);
    //последн€€ строка всегда 0 0 0 1
    for(int i = 0; i < M1.rows; i++){
        for(int j = 0; j < M2.cols; j++){
            M.matrix[i][j] = 0;
            for(int k = 0; k < M2.rows; k++){
                M.matrix[i][j] += M1.matrix[i][k] * M2.matrix[k][j]; // можно перегрузить [][]
            }
        }
    }
    return M;
};




vec::vec(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}
