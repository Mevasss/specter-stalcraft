#include "glDrawElements.h"
#include "../wglSwapBuffers/Esp/Esp.h"
#include "../wglSwapBuffers/Render/Menu/Menu.h"
#include <fstream>
#include "../glGetFloatv/glGetFloatv.h"
#include "gl/GL.h"
#include "gl/GLU.h"
#include <iostream>
#include "../../../Vmprotect/Vmprotect.h"

typedef void (APIENTRY* PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint* params);
typedef void (APIENTRY* PFNGLGETSHADERSOURCEPROC) (GLuint shader, GLsizei bufSize, GLsizei* length, char* source);
typedef void (APIENTRY* PFNGLGETPROGRAMIVPROC) (GLuint program, GLenum pname, GLint* params);
typedef void (APIENTRY* PFNGLGETATTACHEDSHADERSPROC) (GLuint program, GLsizei maxCount, GLsizei* count, GLuint* shaders);
typedef void (APIENTRY* PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint* params);
typedef void (APIENTRY* PFNGLGETACTIVEUNIFORMPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, char* name);
typedef GLuint(APIENTRY* PFNGLCREATESHADERPROC) (GLenum type);
typedef void (APIENTRY* PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei count, const char* const* string, const GLint* length);
typedef void (APIENTRY* PFNGLCOMPILESHADERPROC) (GLuint shader);
typedef GLuint(APIENTRY* PFNGLCREATEPROGRAMPROC) (void);
typedef void (APIENTRY* PFNGLATTACHSHADERPROC) (GLuint program, GLuint shader);
typedef void (APIENTRY* PFNGLLINKPROGRAMPROC) (GLuint program);
typedef void (APIENTRY* PFNGLUSEPROGRAMPROC) (GLuint program);
typedef void (APIENTRY* PFNGLDETACHSHADERPROC) (GLuint program, GLuint shader);
typedef GLuint(APIENTRY* PFNGLGETUNIFORMBLOCKINDEXPROC) (GLuint program, const char* uniformBlockName);
typedef void (APIENTRY* PFNGLGETACTIVEUNIFORMBLOCKIVPROC) (GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint* params);
typedef void (APIENTRY* PFNGLGENBUFFERSPROC) (GLsizei n, GLuint* buffers);
typedef void (APIENTRY* PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
typedef void (APIENTRY* PFNGLBUFFERDATAPROC) (GLenum target, uintptr_t size, const void* data, GLenum usage);
typedef void (APIENTRY* PFNGLBINDBUFFERBASEPROC) (GLenum target, GLuint index, GLuint buffer);
typedef void* (APIENTRY* PFNGLMAPBUFFERRANGEPROC) (GLenum target, uintptr_t offset, uintptr_t length, GLbitfield access);
typedef GLboolean(APIENTRY* PFNGLUNMAPBUFFERPROC) (GLenum target);
typedef void (APIENTRY* PFNGLUNIFORM3FVPROC) (GLint location, GLsizei count, const GLfloat* value);
typedef GLint(APIENTRY* PFNGLGETUNIFORMLOCATIONPROC) (GLuint program, const char* name);
typedef void (APIENTRY* PFNGLGETUNIFORMIVPROC) (GLuint program, GLint location, GLint* params);

static inline std::vector<int> player_vertex_count = { 1242,21330,34719,15732,29130,1578,3348,34800,1308,15432,14718,18132,16218,18198,25356,648,2658,16491,402 };
static inline std::vector<int> storage_vertex_count = { 8934,5088,792 };

auto get_uniform_location(GLint program, const char* uniform_name) -> GLint {
	static auto glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
	return glGetUniformLocation(program, uniform_name);
}

auto set_uniform_float(GLuint program, const char* uniformName, GLfloat* field) -> void {
	auto location = get_uniform_location(program, uniformName);
	if (location != -1) {
		static auto glUniform3fv = (PFNGLUNIFORM3FVPROC)wglGetProcAddress("glUniform3fv");
		glUniform3fv(location, 1, field);
	}
}

auto get_uniform_int(GLuint program, const char* uniformName) -> GLint {
	auto location = get_uniform_location(program, uniformName);
	if (location != -1) {
		static auto glGetUniformiv = (PFNGLGETUNIFORMIVPROC)wglGetProcAddress("glGetUniformiv");
		GLint retn;
		glGetUniformiv(program, location, &retn);
		return retn;
	}
}

auto __stdcall glDrawElements::hk_glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices) -> void
{	
	GLint program = 0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &program);

	auto is_player = true;

	if (get_uniform_location(program,"time") != -1 ||
		get_uniform_location(program, "u_time") != -1 ||
		get_uniform_location(program, "isAnimated") == -1 ||
		get_uniform_int(program,"isAnimated") == 0 ||
		get_uniform_location(program, "playerPos") != -1 ||
		get_uniform_location(program, "diffuseColor") == -1 ||
		get_uniform_location(program, "windStrength") != -1 ||
		get_uniform_location(program, "tex") != -1 ||
		get_uniform_location(program, "lod") != -1 ||
		get_uniform_location(program, "doWind") != -1 ||
		get_uniform_location(program, "vertexColorsAsDiffuse") != -1 || // player
		get_uniform_location(program, "specularChannel") != -1  ||// player
		get_uniform_location(program, "glossMap") != -1 || //player
		get_uniform_location(program, "tBRDF") != -1 ) //player
	{
		is_player = false;
	}

	if (mode == GL_TRIANGLES && type == GL_UNSIGNED_SHORT && Menu::players_chams && program != 0 && is_player) {
		GLfloat color[3] = {Menu::players_chams_color.x * Menu::players_chams_color.w * 5000,Menu::players_chams_color.y * Menu::players_chams_color.w * 5000,Menu::players_chams_color.z * Menu::players_chams_color.w * 5000 };
		set_uniform_float(program, "diffuseColor", color);
		glDepthFunc(GL_ALWAYS);
		glDepthRange(0.0, 0.0);
	}


	reinterpret_cast<decltype(&hk_glDrawElements)>(original_glDrawElements)(mode, count, type, indices);
	
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0, 1.0);

	static auto start = std::chrono::system_clock::now();
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	if (elapsed_seconds.count() >= 86400) {
		exit(0);
	}
}
