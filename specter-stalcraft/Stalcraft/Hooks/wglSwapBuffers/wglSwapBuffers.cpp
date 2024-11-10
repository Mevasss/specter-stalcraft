#include "wglSwapBuffers.h"
#include "Render/Render.h"
#include "Esp/Esp.h"

auto __stdcall wglSwapBuffers::hk_wglSwapBuffers(HDC hDc) -> void
{
	Render::render(hDc);
	Esp::draw();

   reinterpret_cast<decltype(&hk_wglSwapBuffers)>(original_wglSwapBuffers)(hDc);
}
