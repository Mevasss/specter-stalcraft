#include "glUniformMatrix4fv.h"
#include "../wglSwapBuffers/Esp/Esp.h"
#include "../wglSwapBuffers/Render/Render.h"

auto __stdcall glUniformMatrix4fv::hk_glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, GLfloat* value) -> void
{
	reinterpret_cast<decltype(&hk_glUniformMatrix4fv)>(original_glUniformMatrix4fv)(location,count,transpose, value);
}
