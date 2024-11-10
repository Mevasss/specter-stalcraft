#pragma once
#define WIN32_LEAN_AND_MEAN
#include <glfw3.h>
#include <cstdint>
#include <windows.h>
#include <vector>

class glUniformMatrix4fv
{
public:
    static auto __stdcall hk_glUniformMatrix4fv(GLint location,GLsizei count,GLboolean transpose, GLfloat* value) -> void;
    static inline std::uintptr_t original_glUniformMatrix4fv;
};