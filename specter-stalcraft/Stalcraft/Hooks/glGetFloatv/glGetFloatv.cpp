#include "glGetFloatv.h"
#include "../wglSwapBuffers/Esp/Esp.h"

auto __stdcall glGetFloatv::hk_glGetFloatv(GLenum pname, GLfloat* params) -> void
{
	reinterpret_cast<decltype(&hk_glGetFloatv)>(original_glGetFloatv)(pname, params);
}
