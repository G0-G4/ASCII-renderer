#include "renderer/screen.h"
#include "renderer/object.h"
#include <chrono>
#include <iostream>

// есть проблема с загрузкой объекта, если он не повернут, желательно дать ему начальные повороты



int main(int argc, char* argv[])
{
    SCREEN s(120,40);
    float t = 0.0;
    float x,y;
    auto tp1 = std::chrono::system_clock::now();
    auto tp2 = std::chrono::system_clock::now();
    const char* file = argv[1];
    OBJECT obj(vec(0,0,4));
    bool l = obj.load(file);

    while(l){
        tp2 = std::chrono::system_clock::now();
        std::chrono::duration<float> dt = tp2 - tp1;
        tp1 = tp2;
        float fdt = dt.count();

        s.RenderObject(obj);
        s.UPD(fdt);
        obj.UPD(s, fdt);
        t+= 1.5*fdt;
        Sleep(10);
        if(GetKeyState(VK_ESCAPE) & 0x8000){
            break;
        }
    }
    if(!l){
        std::cout << "impossible to load the model from " << argv[1];
    }
    return 0 ;
}
