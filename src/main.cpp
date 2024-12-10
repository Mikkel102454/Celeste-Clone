#include "engine_lib.h"

// Platform Golbals
static bool isRunning = true;

// Platform Functions
bool platform_create_window(int width, int height, const char* title);
void platform_update_window();

// Window Platform
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINAX
#include <windows.h>
#endif

// Windows Globals
static HWND window;

// Platform Implementations

LRESULT CALLBACK windows_windows_callback(HWND window, UINT msg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    switch (msg)
    {
    case WM_CLOSE: {
        isRunning = false;
        break;
    }
    
    default:
        result = DefWindowProcA(window, msg, wParam, lParam);
        break;
    }

    return result;
}
bool platform_create_window(int width, int height, const char* title) {
    HINSTANCE instance = GetModuleHandleA(0);

    WNDCLASSA wc = {};
    wc.hInstance = instance;
    wc.hIcon = LoadIcon(instance, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = title; // This is not tile. this is unique id of window
    wc.lpfnWndProc = windows_windows_callback;

    if(!RegisterClassA(&wc)) {
        return false;
    }
    int dwStyle = WS_OVERLAPPEDWINDOW;
    window = CreateWindowExA(0, title, 
                                title, 
                                dwStyle, 
                                100, 100, 
                                width, height, 
                                NULL, 
                                NULL, 
                                instance, 
                                NULL);
    if(window == NULL){
        return false;
    }
    ShowWindow(window, SW_SHOW);
    return true;
}

void platform_update_window(){
    MSG msg;

    while(PeekMessageA(&msg, window, 0, 0, PM_REMOVE)){
        TranslateMessage(&msg);
        DispatchMessageA(&msg); // send message to callback of the window
    }
}

int main(){

    platform_create_window(1200, 720, "Window name");
    while (isRunning)
    {
        // Update
        platform_update_window();
    }
    return 0;
}