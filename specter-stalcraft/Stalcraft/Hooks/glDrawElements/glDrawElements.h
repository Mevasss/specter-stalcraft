#pragma once
#define WIN32_LEAN_AND_MEAN
#include <glfw3.h>
#include <cstdint>
#include <windows.h>
#include <vector>

class glDrawElements
{
public:
    static auto __stdcall hk_glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices) -> void;
    static inline std::uintptr_t original_glDrawElements;
};