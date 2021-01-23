# pragma once

#ifndef OBJECT_H
#define OBJECT_H

#include <fstream>
#include <strstream>
#include <vector>
#include "vec.h"

#include "screen.h"

class SCREEN;


struct triangle {
    int Pid[3];
    int brightid;
};

class OBJECT {

  private:

    vec position, rotation, scale;
    bool light = false;
    mat trmat;
    std::vector<vec> vertexes;
    std::vector<triangle> triangles;
    std::vector<vec> normals;
    const float speed = 2;
    const float scspeed = 0.01;

  public:

    OBJECT(const vec& pos = vec(0,0,4), const vec& rot = vec(0,0,0), const vec& sc  = vec(1,1,1));
    bool load(const char * file);
    void UPD(SCREEN& scr, float dt = 0);
    friend class SCREEN;
};

# endif // OBJECT_H
