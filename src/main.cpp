// Win32
#include <windows.h>

// C++ std
#include <iostream>

// Game
#include "Window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Window window = Window(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
    window.Run();

    return 0;
}