#include "screen.h"


SCREEN::SCREEN(int w, int h){

    scrWIDTH = w;
    scrHEIGHT = h;
    scr = new wchar_t[scrWIDTH*scrHEIGHT];

    Console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(Console);
    dwBytesWritten = 0;

    scr[scrWIDTH*scrHEIGHT - 1] = '\0';
    VH = 1;
    VW = w/h;
    d = 1;


};

SCREEN::~SCREEN(){
    delete[] scr;
};

int SCREEN::Width(){
    return scrWIDTH;
};

int SCREEN::Height(){
    return scrHEIGHT;
};

void SCREEN::PutChar(int x, int y, wchar_t chr){
    int nX = scrWIDTH/2 + x;
    int nY = scrHEIGHT/2 - y;

    if (0 <= nX && nX<scrWIDTH && 0<=nY && nY <scrHEIGHT){
        int pos = nY*scrWIDTH + nX;
        scr[pos] = chr;
    }
    return;
};

void SCREEN::PutChar(vec P, wchar_t chr){
    PutChar(P.x,P.y, chr);
    return ;
};

void SCREEN::Write(int pos, wchar_t chr){
    if(pos < scrWIDTH*scrHEIGHT){
    scr[pos] = chr;
    }
    return;
};

vec SCREEN::ViewportToCanvas(float x, float y){
    vec p{scrWIDTH*x/VW,scrHEIGHT*y/VH};
    return p;
};

vec SCREEN::ProjectVert(float x, float y,float z){
    //  проекция на viewport x * d/z, y * d/z
    return ViewportToCanvas(x * d/z, y * d/z);

};

vec SCREEN::ProjectVert(vec P){
    return ViewportToCanvas(P.x * d/P.z, P.y * d/P.z);
};

vec SCREEN::ProjectVert(float p[3]){
    return ViewportToCanvas(p[0] * d/p[2], p[1] * d/p[0]);
};

void SCREEN::UPD(float dt){
    WriteConsoleOutputCharacterW(Console,scr,scrWIDTH*scrHEIGHT,{0, 0}, &dwBytesWritten);
    for(int i=0; i<scrWIDTH*scrHEIGHT-1;i++){
        Write(i,' ');
    }
    return ;
};


std::vector<int> SCREEN::Interpolate(int i0,int d0,int i1,int d1){
    if (i0 == i1) {
       return std::vector<int> {d0};
    }
    std::vector<int> values;
    float a = float((d1 - d0)) / (i1 - i0);
    float d = d0;
    for(int i = i0; i<=i1;i++){
        values.push_back(round(d));
        d += a;
    }
    return values;
};

void SCREEN::DrawLine(int x0, int y0, int x1, int y1, wchar_t chr){
        if (abs(x1 - x0) > abs(y1 - y0)) {
        //Прямая ближе к горизонтальной
        //Проверяем, что x0 < x1
        if (x0 > x1) {
            std::swap(x0, x1);
            std::swap(y0,y1);
        }
        std::vector<int> ys = Interpolate(x0, y0, x1, y1);
        for (int x = x0; x<=x1; x++){
            PutChar(x, ys[x - x0],chr);
        }
    }
    else {
        //Прямая ближе к вертикальной
        //Проверяем, что y0 < y1
        if (y0 > y1) {
            std::swap(x0, x1);
            std::swap(y0,y1);
        }
        std::vector<int> xs = Interpolate(y0, x0, y1, x1);
        for(int y=y0; y<=y1; y++){
            PutChar(xs[y - y0], y, chr);
        }
    }
    return ;
};

void SCREEN::DrawLine(vec P1, vec P2, wchar_t chr){
    DrawLine(P1.x, P1.y, P2.x, P2.y, chr);
    return;
}

void SCREEN::DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, wchar_t chr){
    DrawLine(x0,y0,x1,y1, chr);
    DrawLine(x1,y1,x2,y2, chr);
    DrawLine(x0,y0,x2,y2, chr);
    return;
};


void SCREEN::DrawTriangle(vec P1, vec P2, vec P3, wchar_t chr){
    DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, chr);
    return;
};


void SCREEN::DrawFilledTriangle(int x0, int y0, int x1, int y1, int x2, int y2, wchar_t chr){

    // сортировка точек y0<=y1<=y2
    if(y1 < y0){
        std::swap(x1,x0);
        std::swap(y1,y0);
    }
    if(y2 < y0){
        std::swap(x2,x0);
        std::swap(y2,y0);
    }
    if (y2 < y1){
        std::swap(x2,x1);
        std::swap(y2,y1);
    }

    //вычисление координат x треугольника
    std::vector<int> x01 = Interpolate(y0,x0,y1,x1);
    std::vector<int> x12 = Interpolate(y1,x1,y2,x2);
    std::vector<int> x02 = Interpolate(y0,x0,y2,x2);


    //соединение двух сторон
    x01.pop_back();
    //log << "x01 ";
    //print(x01);
    x01.insert(x01.end(),x12.begin(),x12.end());
    std::vector<int>& x012 = x01;


    // определяем левую сторону
    std::vector<int> x_left, x_right;

    int m = x012.size() / 2;
    if (x02[m] < x012[m]){
        x_left = x02;
        x_right = x012;
    }
    else{
        x_left = x012;
        x_right = x02;
    }

    // отрисовка

   for(int y = y0; y <= y2; y++){
        for(int x = x_left[y - y0]; x <= x_right[y - y0]; x++){
            PutChar(x, y, chr);
        }
    }

    return ;
};


void SCREEN::DrawFilledTriangle(vec P1, vec P2, vec P3, wchar_t chr){
    DrawFilledTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, chr);
    return;
}


void SCREEN::RenderObject(OBJECT& obj){
    std::vector<vec> projected;
    std::vector<vec> translated;
    for(const auto& v: obj.vertexes){
        vec v1 = obj.trmat*mat(v);
        translated.push_back(v1);
        projected.push_back(ProjectVert(v1));
    }
    // алгоритм художника (сортируем треугольнике по z)
    std::sort(obj.triangles.begin(), obj.triangles.end(), [&translated](triangle &t1, triangle &t2){
                float z1 = (translated[t1.Pid[0]].z + translated[t1.Pid[1]].z + translated[t1.Pid[2]].z)/3;
                float z2 = (translated[t2.Pid[0]].z + translated[t2.Pid[1]].z + translated[t2.Pid[2]].z)/3;
                return z1 > z2;
              });

    for(auto T: obj.triangles){
        vec line1 = translated[T.Pid[1]];
        vec line2 = translated[T.Pid[2]];
        vec normal = cross(line1, line2).norm();
        // если объект перед экраном, и нормаль смотрит в камеру
        if ((normal*translated[T.Pid[0]].norm() < 0) && (obj.position.z >= d)){
            float z = normal.z;
            //расчет освещенности, опираясь на ориентированность к экрану
            z += 1;
            T.brightid = 11 - round(11*z/2);
            RenderTriangle(T, projected, obj.light);
        }
    }
    return ;

};

void SCREEN::RenderTriangle(const triangle& T,const std::vector<vec>& prjct, bool light){
    if(light)
        DrawTriangle(prjct[T.Pid[0]],prjct[T.Pid[1]], prjct[T.Pid[2]], bright[0]);
    else
        DrawFilledTriangle(prjct[T.Pid[0]],prjct[T.Pid[1]], prjct[T.Pid[2]], bright[T.brightid]);

}
