#pragma once
#define WIN32_LEAN_AND_MEAN
#include <glfw3.h>
#include <cstdint>
#include <windows.h>
#include <vector>

class glGetFloatv
{
public:
    static auto __stdcall hk_glGetFloatv(GLenum pname, GLfloat* params) -> void;
    static inline std::uintptr_t original_glGetFloatv;
};