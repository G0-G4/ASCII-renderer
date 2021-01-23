#pragma once

#ifndef SCREEN_H
#define SCREEN_H
#include <Windows.h>
#include <algorithm>
#include "object.h"

struct triangle;

class OBJECT;

class SCREEN {

  private:

    HANDLE Console;
    DWORD dwBytesWritten;
    const int scrWIDTH, scrHEIGHT;
    const int VH,VW,d; // ширина, высота, смещение плоскости проекции
    wchar_t *scr;

    const char* bright = ".,-~:;=!*#$@";
    vec ViewportToCanvas(float x, float y);
    void Write(int pos,wchar_t chr = '.');
    void PutChar(int x, int y, wchar_t chr = '.');
    void PutChar(vec P, wchar_t chr = '.');
    vec ProjectVert(float x, float y,float z);
    vec ProjectVert(float p[3]);
    vec ProjectVert(vec P);
    std::vector<int> Interpolate(int i0,int d0,int i1,int d1);
    void DrawLine(int x0, int y0, int x1, int y1, wchar_t chr = '.');
    void DrawLine(vec P1, vec P2, wchar_t chr = '.');
    void DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, wchar_t chr = '.');
    void DrawTriangle(vec P1, vec P2, vec P3, wchar_t chr = '.');
    void DrawFilledTriangle(int x0, int y0, int x1, int y1, int x2, int y2, wchar_t chr = '.');
    void DrawFilledTriangle(vec P1, vec P2, vec P3, wchar_t chr = '.');
    void RenderTriangle(const triangle& T, const std::vector<vec>& prjct, bool light);

  public:

    SCREEN(int w = 120, int h = 40);
    ~SCREEN();
    int Width();
    int Height();
    void UPD(float dt);
    void RenderObject(OBJECT& obj);
    friend class OBJECT;
};
#endif // SCREEN_H
