#pragma once
#define WIN32_LEAN_AND_MEAN
#include <glfw3.h>
#include <cstdint>
#include <windows.h>

class Render
{
public:
	static auto render(HDC hDc) -> void;
	static inline bool inited = false;
	static inline HWND hwnd;
	static inline float window_width;
	static inline float window_height;
	static inline WNDPROC original_wndproc;
	static inline HGLRC h_wgl_context;
	static inline bool menu_opened = true;
};