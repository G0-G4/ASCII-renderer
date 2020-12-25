#pragma once

# ifndef MAT_H
# define MAT_H


class mat{

private:
    float matrix[4][4] = {0};
    // всегда 1  в однородных координаиах
    int rows = 0;
    int cols = 0;
public:

    //mat(int rows, int cols){
        //this->rows = rows;
        //this->cols = cols;
    //}
/*
0 0 0 0   0
0 0 0 0   1
0 0 0 0   2
0 0 0 0   3

*/
    mat(){};
    mat(const vec& v){
        rows = 4;
        cols = 1;
        matrix[0][0] = v.x;
        matrix[1][0] = v.y;
        matrix[2][0] = v.z;
        matrix[3][0] = 1;
    }
    void Translation(const vec& v){
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

    void Rotation(const vec& v){
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


    void Scale(vec v){

        matrix[0][0] = v.x;
        matrix[1][1] = v.y;
        matrix[2][2] = v.z;
        matrix[3][3] = 1;
        return;
    }

    friend mat operator*(const mat& m1, const mat& m2);

    friend class vec;

};


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

# endif // MAT_H
