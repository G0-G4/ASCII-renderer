#include "object.h"


OBJECT::OBJECT(const vec& pos,const vec& rot, const vec& sc){
    position = pos;
    rotation = rot;
    scale = sc;
    scale.x *= 2;
}


void OBJECT::UPD(SCREEN& scr, float dt){


    if(GetKeyState('W') & 0x8000){
        position.z += speed*dt;
    }
    if(GetKeyState('S') & 0x8000){
        position.z -= speed*dt;
    }

    if(GetKeyState('A') & 0x8000){
        position.x -= speed*dt;
    }
    if(GetKeyState('D') & 0x8000){
        position.x += speed*dt;
    }

    if(GetKeyState('Q') & 0x8000){
        position.y -= speed*dt;
    }

    if(GetKeyState('E') & 0x8000){
        position.y += speed*dt;
    }

    if(GetKeyState(VK_LEFT) & 0x8000){
        rotation.y += speed*dt;
    }

    if(GetKeyState(VK_RIGHT) & 0x8000){
        rotation.y -= speed*dt;
    }

    if(GetKeyState(VK_UP) & 0x8000){
        rotation.x += speed*dt;
    }

    if(GetKeyState(VK_DOWN) & 0x8000){
        rotation.x -= speed*dt;
    }


    if(GetKeyState('Z') & 0x8000){
        rotation.z += speed*dt;
    }

    if(GetKeyState('X') & 0x8000){
        rotation.z -= speed*dt;
    }

    if(GetKeyState('C') & 0x8000){
        scale *= (1 + scspeed);
    }

    if(GetKeyState('V') & 0x8000){
        scale *= (1 - scspeed);
    }

    if(GetKeyState('R') & 0x8000){
        light = !light;
    }

    if((rotation.y >= 2*M_PI) || (rotation.y <= -2*M_PI)){
        rotation.y = 0.0;
    }
    if((rotation.x >= 2*M_PI) || (rotation.x <= -2*M_PI)){
        rotation.x = 0.0;
    }

    if((rotation.z >= 2*M_PI) || (rotation.z <= -2*M_PI)){
        rotation.z = 0.0;
    }

    mat s,t,r;

    t.Translation(position);
    r.Rotation(rotation);
    s.Scale(scale);
    trmat = t*s*r;
}

bool OBJECT::load(const char* file){

    std::ifstream f(file);

    if(!f.is_open()){
        return false;
    }

    while(!f.eof()){
        char line[128];
        f.getline(line, 128);
        std::strstream s;
        s << line;

        char c;
        if(line[0] == 'v'){
            vec v;
            s >> c >> v.x >> v.y >> v.z;
            vertexes.push_back(v);
        }

        else if(line[0] == 'f'){
            triangle t;
            s >> c >> t.Pid[0] >> t.Pid[1] >> t.Pid[2];
            t.Pid[0] -= 1;
            t.Pid[1] -= 1;
            t.Pid[2] -= 1;
            triangles.push_back(t);
        }
    }
    f.close();
    return true;
};
