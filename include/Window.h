#pragma once

#include <windows.h>

class Window
{
private:
    HWND hwnd;
    MSG msg;
    bool isRunning = false;
    int frameRate = 144;

public:
    Window(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

    void Run();
    void Update(long delta);
    void Draw();
};