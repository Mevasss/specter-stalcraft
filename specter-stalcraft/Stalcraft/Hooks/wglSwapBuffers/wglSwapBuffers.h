#pragma once
#define WIN32_LEAN_AND_MEAN
#include <glfw3.h>
#include <cstdint>
#include <windows.h>

class wglSwapBuffers
{
public:
    static auto __stdcall hk_wglSwapBuffers(HDC hDc) -> void;
    static inline std::uintptr_t original_wglSwapBuffers;
};