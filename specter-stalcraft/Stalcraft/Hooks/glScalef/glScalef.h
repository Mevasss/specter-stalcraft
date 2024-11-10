#pragma once
#define WIN32_LEAN_AND_MEAN
#include <glfw3.h>
#include <cstdint>
#include <windows.h>
#include <vector>

class glScalef
{
public:
    static auto __stdcall hk_glScalef(GLfloat x,GLfloat y,GLfloat z) -> void;
    static inline std::uintptr_t original_glScalef;
};