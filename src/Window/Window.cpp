#include "Window.h"

#include <windows.h>
#include <tchar.h>

#include <iostream>
#include <chrono>

#include <assert.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

    switch(msg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
            break;
        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);

                HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
                SelectObject(hdc, hBrush);
                Rectangle(hdc, 0, 0, 200, 200);
                DeleteObject(hBrush);

                EndPaint(hwnd, &ps);
            }
            break;
        case WM_SIZE: 
        {
            UINT width = LOWORD(lParam);
            UINT height = HIWORD(lParam);
            break;
        }
        case WM_KEYDOWN:
        {
            if (wParam == VK_ESCAPE) {
                PostQuitMessage(0);
            }
            break;
        }
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

Window::Window(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    LPCTSTR szClassName = _T("Window Class");
    WNDCLASSEX wc;

    //Step 1: Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    assert(RegisterClassEx(&wc));
   

    // Step 2: Creating the Window
    this->hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        szClassName,
        _T("Window"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,
        NULL, NULL, hInstance, NULL
    );

    SetWindowLongPtr(this->hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

    ShowWindow(this->hwnd, nCmdShow);
    UpdateWindow(this->hwnd);
}

long CurrTime()
{
    using namespace std::chrono;
    auto now = system_clock::now();
    auto nowEpoch = time_point_cast<milliseconds>(now).time_since_epoch();
    return nowEpoch.count();
}

void Window::Run()
{
    this->isRunning = true;
    float frameTime = 1000 / this->frameRate;

    long before = CurrTime();
    long now = before;
    long delta = now - before;

    while (this->isRunning)
    {
        now = CurrTime();
        delta += now - before;
        before = now;

        // Process frame if delta exceeds frameTime
        while (delta >= frameTime)
        {
            std::cout << "FrameTime: " << frameTime << std::endl;
            this->Update(frameTime);
            this->Draw();
            delta -= frameTime;
        }

        while (PeekMessage(&this->msg, NULL, 0, 0, PM_REMOVE))
        {
            if (this->msg.message == WM_QUIT)
            {
                this->isRunning = false;
                break;
            }
            TranslateMessage(&this->msg);
            DispatchMessage(&this->msg);
        }



    }
}

void Window::Update(long delta)
{

}

void Window::Draw()
{

}