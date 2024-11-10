#include "glScalef.h"
#include "../wglSwapBuffers/Esp/Esp.h"
#include <fstream>
#include <string>


auto __stdcall glScalef::hk_glScalef(GLfloat x, GLfloat y, GLfloat z) -> void
{
	if (x <= 1 && y <= 1 && z <= 1) {
		Esp::add_drawing_model(Esp::items, { 0,0,0 });
	}

	return reinterpret_cast<decltype(&hk_glScalef)>(original_glScalef)(x, y, z);
}
